#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int abs(int a) {
    return a > 0 ? a : -a;
}

struct TreeNode {
    int key, size, priority;
    bool type; // type: '0' - Прямая, '1' - Цикл;
    TreeNode *left, *right, *parent;

    TreeNode(int key, bool type = false) :
            key(key), size(1), priority(rand()), type(type), left(nullptr), right(nullptr),
            parent(nullptr) {}
};

inline void print(TreeNode *root, std::string offset) {
    if (root == nullptr) {
        std::cout << "\n";
        return;
    }
    print(root->right, offset + "   ");
    std::cout << offset << root->key + 1 << "(" << root->size << ")" << "\n";
    print(root->left, offset + "   ");
}

inline int getSize(TreeNode *root) {
    return root == nullptr ? 0 : root->size;
}

inline void update(TreeNode *root) {
    if (root == nullptr) return;
    root->size = getSize(root->left) + getSize(root->right) + 1;
}

inline void split(TreeNode *root, TreeNode *&left, TreeNode *&right, int key) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    int rootSize = getSize(root->left);
    if (rootSize < key) {
        split(root->right, root->right, right, key - rootSize - 1);
        left = root;
        if (root->left != nullptr)
            root->left->parent = left;
        if (root->right != nullptr)
            root->right->parent = left;
        if (right != nullptr)
            right->parent = nullptr;
    } else {
        split(root->left, left, root->left, key);
        right = root;
        if (root->left != nullptr)
            root->left->parent = right;
        if (root->right != nullptr)
            root->right->parent = right;
        if (left != nullptr)
            left->parent = nullptr;
    }
    update(root);
}

inline TreeNode *merge(TreeNode *left, TreeNode *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        left->right->parent = left;
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        right->left->parent = right;
        update(right);
        return right;
    }
}

inline TreeNode *getRoot(TreeNode *&root) {
    TreeNode *cur = root;
    while (cur->parent != nullptr)
        cur = cur->parent;
    return cur;
}

inline int getTown(TreeNode *&root, bool pos) { // pos '0' - Левое поддерево, '1' - Правое поддерево
    TreeNode *cur = root;
    while ((pos && cur->right != nullptr) || (!pos && cur->left != nullptr))
        cur = pos ? cur->right : cur->left;
    return cur->key;
}

inline int getInd(TreeNode *&root) {
    int ans = getSize(root->left);
    bool fromRight;
    TreeNode *cur = root;
    while (cur->parent != nullptr) {
        fromRight = (cur->parent->right == cur);
        cur = cur->parent;
        ans += fromRight ? 1 + getSize(cur->left) : 0;
    }
    return ans;
}

inline void inverse(TreeNode *&root) {
    if (root == nullptr) return;
    if (root->left != nullptr)
        inverse(root->left);
    if (root->right != nullptr)
        inverse(root->right);
    TreeNode *tmp = root->right;
    root->right = root->left;
    root->left = tmp;
}

inline void setType(TreeNode *&root, bool type) {
    if (root == nullptr)
        return;
    root->type = type;
    setType(root->left, type);
    setType(root->right, type);
}
inline void insert(std::vector<TreeNode *> &towns, int left, int right) {
    TreeNode *t1 = nullptr, *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    if (t1 == t2) {
        setType(t1, true);
        return;
    } else {
        int leftTown = getTown(t1, true), rightTown = getTown(t2, false);
        if (leftTown != left && rightTown != right) {
            TreeNode *tmp = t1;
            t1 = t2;
            t2 = tmp;
        } else if (leftTown == left && rightTown != right)
            inverse(t2);
        else if (leftTown != left && rightTown == right)
            inverse(t1);
    }
    merge(t1, t2);
}

inline void shiftLeft(TreeNode *&root, int pos) {
    TreeNode *t1 = nullptr, *t2 = nullptr;
    split(root, t1, t2, pos);
    root = merge(t2, t1);
    update(root);
}

inline void erase(std::vector<TreeNode *> &towns, int left, int right) {
    TreeNode *t1 = nullptr, *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    int ind1 = getInd(towns[left]), ind2 = getInd(towns[right]);
    if (t1 != t2)
        return;
    if (t1->type) {
        setType(t1, false);

        if ((ind1 == 0 && ind2 == getSize(t1) - 1) || (ind2 == 0 && ind1 == getSize(t1) - 1))
            return;
        shiftLeft(t1, max(ind1, ind2));
        return;
    } else {
        if (ind1 < ind2)
            split(t1, t1, t2, ind1 + 1);
        else
            split(t2, t1, t2, ind2 + 1);
    }
}

inline int query(std::vector<TreeNode *> &towns, int left, int right) {
    TreeNode *t1 = nullptr, *t2 = nullptr;
    t1 = getRoot(towns[left]);
    t2 = getRoot(towns[right]);
    int ind1 = getInd(towns[left]), ind2 = getInd(towns[right]);
    if (t1 != t2)
        return -1;
    else {
        if (t1->type) {
            return min(abs(ind1 - ind2), getSize(t1) - abs(ind1 - ind2)) - 1;
        } else {
            return abs(ind1 - ind2) - 1;
        }
    }
}

int main() {
    srand(9051999);
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<TreeNode *> towns(n);
    for (int i = 0; i < n; i++)
        towns[i] = new TreeNode(i);
    int town1, town2;
    for (int i = 0; i < m; i++) {
        std::cin >> town1 >> town2;
        if (town1 != town2)
            insert(towns, town1 - 1, town2 - 1); // Добавление пути
    }
    char operation;
    for (int i = 0; i < q; i++) {
        std::cin >> operation >> town1 >> town2;
        switch (operation) {
            case '+' :
                if (town1 != town2)
                    insert(towns, town1 - 1, town2 - 1); // Добавление пути
                break;
            case '-' :
                if (town1 != town2)
                    erase(towns, town1 - 1, town2 - 1); // Удаление пути
                break;
            case '?' :
                if (town1 != town2)
                    printf("%d\n", query(towns, town1 - 1, town2 - 1));
                else printf("0\n");
                break;
        }
    }
    return 0;
}