#include <iostream>
#include <cstdio>
#include <cstdlib>


struct TreeNode {
    int key, priority, size;
    bool reverse;
    TreeNode *left, *right, *parent;

    TreeNode(int key, int priority, TreeNode *left, TreeNode *right, TreeNode *parent) :
            key(key), priority(priority), size(1), left(left), right(right), parent(parent), reverse(false) {}
};

int getSize(TreeNode *);

void update(TreeNode *);

void updateAllNode(TreeNode *);

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
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
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

int getSize(TreeNode *root) {
    return root == nullptr ? 0 : root->size;
}

void update(TreeNode *root) {
    if (root == nullptr)
        return;
    root->size = getSize(root->left) + getSize(root->right) + 1;
}

void updateAllNode(TreeNode *root) {
    if (root == nullptr)
        return;
    updateAllNode(root->left);
    updateAllNode(root->right);
    update(root);
}

void inverse(TreeNode *root, int l, int r) {
    TreeNode *t1 = nullptr, *t2 = nullptr, *t3 = nullptr;
    split(root, t1, t2, l);
    split(t2, t2, t3, r + 1);
    merge(t2, merge(t1, t3));
}

void print(TreeNode *root) {
    if (root == nullptr) return;
    print(root->left);
    std::cout << root->key << " ";
    print(root->right);
}

int main() {
    srand(4567862);
    TreeNode *root = nullptr;
    int n, m, l, r;
    scanf("%d %d", &n, &m);
    std::pair<int, int> arr[n];
    for (int i = 0; i < n; i++) {
        arr[i].first = i + 1;
        arr[i].second = rand() * rand();
    }
    root = build(arr, n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l, &r);
        inverse(root, l - 1, r - l);
    }
    print(root);
    return 0;
}