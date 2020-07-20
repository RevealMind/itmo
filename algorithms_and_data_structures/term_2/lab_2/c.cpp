#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

struct Node {
    Node *left, *right, *parent;
    int key, priority, pos;

    Node(int key, int priority, int pos, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr)
            : left(left), right(right), parent(parent), key(key), priority(priority), pos(pos) {}
};

struct Vertex {
    int key, priority, pos;
};

struct Ans {
    int l, r, p;
};

void get_ans(Node *root, Ans ans[], int p) {
    if (root == nullptr) {
        return;
    }
    ans[root->pos - 1].p = p;
    ans[root->pos - 1].l = root->left == nullptr ? 0 : root->left->pos;
    ans[root->pos - 1].r = root->right == nullptr ? 0 : root->right->pos;
    get_ans(root->left, ans, root->pos);
    get_ans(root->right, ans, root->pos);
}

Node *build(std::vector<Vertex> &arr, int n) {
    Node *root = new Node(arr[0].key, arr[0].priority, arr[0].pos);
    Node *last = root;

    for (int i = 1; i < n; i++) {
        if (last->priority <= arr[i].priority) {
            last->right = new Node(arr[i].key, arr[i].priority, arr[i].pos, nullptr, nullptr, last);
            last = last->right;
        } else {
            Node *cur = last;
            while (cur->parent != nullptr && cur->priority > arr[i].priority)
                cur = cur->parent;
            if (cur->priority > arr[i].priority)
                last = new Node(arr[i].key, arr[i].priority, arr[i].pos, cur);
            else {
                last = new Node(arr[i].key, arr[i].priority, arr[i].pos, cur->right, nullptr, cur);
                cur->right = last;
            }
        }
    }

    while (last->parent != nullptr)
        last = last->parent;
    return last;
}

void print(Node *root, std::string offset) {
    if (root == nullptr) {
        std::cout << "\n";
        return;
    }
    print(root->right, offset + "   ");
    std::cout << offset << root->pos << std::endl;
    print(root->left, offset + "   ");
}

int main() {
    int n;
    Node *root = nullptr;
    scanf("%d", &n);
    std::vector<Vertex> arr(n);
    Ans *_ans = new Ans[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].key, &arr[i].priority);
        arr[i].pos = i + 1;
    }
    std::sort(arr.begin(), arr.end(), [](const Vertex &a, const Vertex &b) {
        return a.key < b.key;
    });
    root = build(arr, n);
    get_ans(root, _ans, 0);
    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d %d %d\n", _ans[i].p, _ans[i].l, _ans[i].r);

    return 0;
}
