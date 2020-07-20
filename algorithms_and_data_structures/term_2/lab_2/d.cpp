#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>


struct TreeNode {
    int key, priority, size, zero;
    TreeNode *left, *right, *parent;

    TreeNode(int key, int priority, TreeNode *left, TreeNode *right, TreeNode *parent) :
            key(key), priority(priority), size(1), zero(key ? 0 : 1), left(left), right(right), parent(parent) {}
};

int getZero(TreeNode *root) {
    return root == nullptr ? 0 : root->zero;
}

int getSize(TreeNode *root) {
    return root == nullptr ? 0 : root->size;
}

void update(TreeNode *root) {
    if (root == nullptr) return;
    root->size = getSize(root->left) + getSize(root->right) + 1;
    root->zero = getZero(root->left) + getZero(root->right) + ((root->key == 0) ? 1 : 0);
}

void updateAllNode(TreeNode *root) {
    if (root == nullptr) return;
    updateAllNode(root->left);
    updateAllNode(root->right);
    update(root);
}

void split(TreeNode *root, TreeNode *&left, TreeNode *&right, int key) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    int rootKey = getSize(root->left);
    if (rootKey < key) {
        split(root->right, root->right, right, key - rootKey - 1);
        left = root;
    } else {
        split(root->left, left, root->left, key);
        right = root;
    }
    update(root);
}

TreeNode *merge(TreeNode *left, TreeNode *right) {
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

TreeNode *build(std::pair<int, int> arr[], int n) {
    TreeNode *root = new TreeNode(arr[0].first, arr[0].second, nullptr, nullptr, nullptr);
    TreeNode *last = root;
    for (int i = 1; i < n; i++) {
        if (last->priority > arr[i].second) {
            last->right = new TreeNode(arr[i].first, arr[i].second, nullptr, nullptr, last);
            last = last->right;
        } else {
            TreeNode *cur = last;
            while (cur->parent != nullptr && cur->priority <= arr[i].second)
                cur = cur->parent;
            if (cur->priority <= arr[i].second) {
                last = new TreeNode(arr[i].first, arr[i].second, cur, nullptr, nullptr);
                cur->parent = last;
            } else {
                last = new TreeNode(arr[i].first, arr[i].second, cur->right, nullptr, cur);
                cur->right = last;
            }
        }
    }
    while (last->parent != nullptr)
        last = last->parent;
    updateAllNode(last);
    return last;
}

void print(TreeNode *root, std::string offset) {
    if (root == nullptr) {
        std::cout << "\n";
        return;
    }
    print(root->right, offset + "   ");
    std::cout << offset << root->key << "(" << root->zero << ")" << "\n";
    print(root->left, offset + "   ");
}

void printLine(TreeNode *root,std::vector<int> &arr, int &count, int &k) {
    if (count == 0 || root == nullptr) return;
    printLine(root->left, arr, count, k);
    if (count == 0 && root->key == 0) return;
    arr.push_back(root->key);
    //std::cout << root->key << " ";
    k++;
    if (root->key != 0)
        count--;
    printLine(root->right, arr, count, k);
}

int findNode(TreeNode *root, int ind) {
    if (root == nullptr || root->zero == 0) {
        return -1;
    }
    int rootZero = getZero(root->left);
    if (rootZero == 0 && root->key == 0) {
        return ind - getSize(root->right) - 1;
    }
    if (rootZero > 0) {
        return findNode(root->left, ind - getSize(root->right) - 1);
    } else
        return findNode(root->right, ind);
}

TreeNode *_delete(TreeNode *curNode, int pos) {
    TreeNode *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    split(curNode, t1, t2, pos);
    split(t2, t2, t3, 1);
    curNode = merge(t1, t3);
    delete t2;
    return curNode;

}

void insert(TreeNode *&root, int pos, int key) {
    TreeNode *t1 = nullptr, *t2 = nullptr;
    split(root, t1, t2, pos);
    int posZero;
    if (t2 != nullptr) {
        posZero = findNode(t2, t2->size);
        if (posZero != -1)
            t2 = _delete(t2, posZero);
    }
    TreeNode *newNode = new TreeNode(key, rand() * rand(), nullptr, nullptr, nullptr);
    root = merge(merge(t1, newNode), t2);
}

int find(TreeNode *root, int ind) {
    if (root == nullptr) {
        return -1;
    }
    int rootZero = getZero(root->right);
    if (root->size == 1 && root->key == 0) {
        return ind - getSize(root->right) - 1;
    }
    if (rootZero <= getSize(root->right)) {
        return findNode(root->right, ind);
    } else
        return findNode(root->left, ind - getSize(root->right) - 1);
}

int main() {
    srand(8454198);
    int n, m;
    scanf("%d %d", &n, &m);
    std::pair<int, int> arr[m];
    for (int i = 0; i < m; i++) {
        arr[i].first = 0;
        arr[i].second = rand() * rand();
    }
    TreeNode *root = build(arr, m);
    int pos;
    for (int i = 0; i < n; i++) {
        scanf("%d", &pos);
        insert(root, pos - 1, i + 1);
        /*std::cout << "-------------------";
        print(root, "");
        std::cout << "-------------------";*/
    }
    std::vector<int> a;
    int count = root->size - root->zero;
    //std::cout << count;
    int k = 0;
    printLine(root,a, count, k);
    std::cout << k << "\n";

    for(int i = 0; i < k; i++)
        std::cout << a[i] << " ";
    return 0;
}