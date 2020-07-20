#include <iostream>
#include <cstdlib>
#include <cstdio>

const long long MOD = 1000000000;

struct TreeNode {
    long long key, priority, sum;
    TreeNode *left, *right;

    TreeNode(long long key) : key(key), sum(key % MOD), priority(rand() * rand()), left(nullptr), right(nullptr) {}
};
long long _getSum(TreeNode *root) {
    return root == nullptr ? 0 : root->sum;
}
void update(TreeNode *root) {
    if (root == nullptr)
        return;
    root->sum = _getSum(root->left) + _getSum(root->right) + root->key;
}
void split(TreeNode *root, TreeNode *&left, TreeNode *&right, long long key) {
    if (root == nullptr) {
        left = right = nullptr;
        return;
    }
    if (root->key < key) {
        split(root->right, root->right, right, key);
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

bool isFinde(TreeNode *root, long long key) {
    if (root == nullptr)
        return false;
    if (root->key == key)
        return true;
    return root->key < key ? isFinde(root->right, key) : isFinde(root->left, key);
}

void insert(TreeNode *&root, long long key) {
    if (!isFinde(root, key)) {
        TreeNode *t1 = nullptr, *t2 = nullptr;
        split(root, t1, t2, key);
        TreeNode *newNode = new TreeNode(key);
        root = merge(merge(t1, newNode), t2);
    }
}

long long getSum(TreeNode *root, int l, int r) {
    TreeNode *t1 = nullptr, *t2 = nullptr, *t3 = nullptr, *t4 = nullptr;
    split(root, t1, t2, l);
    split(t2, t2, t3, r + 1);
    long long ans = t2 == nullptr ? 0 : t2->sum;
    root = merge(t1, merge(t2, t3));
    return ans;
}
void print(TreeNode *root, std::string offset) {
    if(root == nullptr)
        return;
    print(root->right, offset + "   ");
    std::cout << offset << root->key << "\n";
    print(root->left, offset + "   ");
}

int main() {
    int n, l, r;
    long long key, ans;
    bool lastGetSum = false;
    TreeNode* root = nullptr;
    scanf("%d", &n);
    char c;
    for(int i = 0; i < n; i++) {
        std::cin >> c;
        switch (c) {
            case '+' :
                scanf("%lld", &key);
                insert(root, lastGetSum ? (key + ans) % MOD : key);
                lastGetSum = false;
                break;
            case '?' :
                scanf("%d %d", &l, &r);
                ans = getSum(root, l, r);
                lastGetSum = true;
                printf("%lld\n", ans);
                break;

        }
        //print(root, "");
    }
    return 0;
}