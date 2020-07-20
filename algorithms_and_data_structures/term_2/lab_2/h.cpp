#include <iostream>
#include <cstdlib>
#include <cstdio>

struct TreeNode {
    int priority, mask, size, key, letter;
    TreeNode *left, *right;

    TreeNode(int mask, int size, TreeNode *left = nullptr, TreeNode *right = nullptr) :
            letter(mask), key(size), priority(rand()), mask(mask), size(size), left(left), right(right) {}
};

inline int getKey(TreeNode *root) {
    return root == nullptr ? 0 : root->key;
}

inline int getLetter(TreeNode *root) {
    return root == nullptr ? 0 : root->letter;
}

inline void update(TreeNode *root) {
    if (root == nullptr) return;
    root->key = getKey(root->left) + getKey(root->right) + root->size;
    root->letter = (getLetter(root->left) | getLetter(root->right)) | root->mask;
}

inline void push(TreeNode *&);

inline void split(TreeNode *root, TreeNode *&left, TreeNode *&right, int key) {
    push(root);
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    int rootKey = getKey(root->left);
    if (rootKey < key) {
        split(root->right, root->right, right, key - rootKey - 1);
        left = root;
    } else {
        split(root->left, left, root->left, key);
        right = root;
    }
    update(root);
}

inline TreeNode *merge(TreeNode *left, TreeNode *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

inline void push(TreeNode *&root) {
    if (root == nullptr || root->size == 1) return;

    int sizeLeftNode = root->size / 2,
            sizeRootNode = 1,
            sizeRightNode = root->size - sizeLeftNode - sizeRootNode;
    TreeNode *left = new TreeNode(root->mask, sizeLeftNode);
    root->size = sizeRootNode;
    root->left = merge(root->left, left);
    if (sizeRightNode) {
        TreeNode *right = new TreeNode(root->mask, sizeRightNode);
        root->right = merge(right, root->right);
    }
}

inline void insert(TreeNode *&root, int pos, int letterMask, int size) {
    if (root == nullptr) {
        root = new TreeNode(letterMask, size);
    } else {
        TreeNode *t1 = nullptr, *t2 = nullptr;
        split(root, t1, t2, pos);
        TreeNode *newNode = new TreeNode(letterMask, size);
        root = merge(merge(t1, newNode), t2);
    }
}

inline void erase(TreeNode *&root, int l, int r) {
    TreeNode *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    split(root, t1, t2, l);
    split(t2, t2, t3, r);
    delete t2;
    root = merge(t1, t3);
}

inline int countLetter(int mask) {
    int letter = 0;
    while (mask != 0) {
        if (mask % 2)
            letter++;
        mask >>= 1;
    }
    return letter;
}

inline int querry(TreeNode *&root, int l, int r) {
    TreeNode *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    split(root, t1, t2, l);
    split(t2, t2, t3, r);
    int ans = t2->letter;
    root = merge(merge(t1, t2), t3);
    return countLetter(ans);
}

inline int getMask(char letter) {
    return (1 << (letter - 'a'));
}

int main() {
    srand(45621848);
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    freopen("log.in", "r", stdin);
    freopen("log.out", "w", stdout);
    TreeNode *root = nullptr;
    int n, ind1, ind2;
    char letter, operation;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> operation >> ind1 >> ind2;
        switch (operation) {
            case '+' :
                std::cin >> letter;
                insert(root, ind1 - 1, getMask(letter), ind2);
                break;
            case '-' :
                erase(root, ind1 - 1, ind2);
                break;
            case '?' :
                std::cout << querry(root, ind1 - 1, ind2 - ind1 + 1) << "\n";
                break;
        }
    }
    return 0;
}