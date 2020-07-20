#include <iostream>
#include <cstdlib>

struct Node {
    Node *left, *right;
    int key, priority, size;

    Node(int key) : left(nullptr), right(nullptr), key(key), priority(rand() * rand()), size(1) {}
};

int get_size(Node *cur) {
    return cur == nullptr ? 0 : cur->size;
}

void update(Node *cur) {
    if (cur == nullptr)
        return;
    cur->size = get_size(cur->left) + get_size(cur->right) + 1;
}

void split(Node *curNode, Node *&left, Node *&right, int key) {
    if (curNode == nullptr) {
        left = right = nullptr;
        return;
    }
    if (curNode->key < key) {
        split(curNode->right, curNode->right, right, key);
        left = curNode;
    } else {
        split(curNode->left, left, curNode->left, key);
        right = curNode;
    }
    update(curNode);

}

Node *merge(Node *left, Node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    }
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

bool is_finde(Node *curNode, int key) {
    if (curNode == nullptr)
        return false;
    if (curNode->key == key)
        return true;
    return curNode->key < key ? is_finde(curNode->right, key) : is_finde(curNode->left, key);
}

void insert(Node *&curNode, int key) {
    Node *left = nullptr, *right = nullptr;
    split(curNode, left, right, key);
    Node *n = new Node(key);
    curNode = merge(merge(left, n), right);
    //update(curNode);
}

void _delete(Node *&curNode, int key) {
    if (curNode->key == key) {
        curNode = merge(curNode->left, curNode->right);
    } else {
        if (curNode->key < key) {
            _delete(curNode->right, key);
        } else {
            _delete(curNode->left, key);
        }
    }
    update(curNode);
}

int kthElem(Node *curNode, int k) {
    int curNumber = get_size(curNode->left);
    if (curNumber == k)
        return curNode->key;
    if (k < curNumber)
        return kthElem(curNode->left, k);
    else
        return kthElem(curNode->right, k - curNumber - 1);
}

void print(Node *root, std::string offset) {
    if (root == nullptr) {
        std::cout << "\n";
        return;
    }
    print(root->right, offset + "   ");
    std::cout << offset << root->key << "(" << root->size << ")" << std::endl;
    print(root->left, offset + "   ");
}

int main() {
    Node *root = nullptr;
    int a, key, n = 0, size;
    std::cin >> size;
    for (int i = 0; i < size; i++) {
        std::cin >> a >> key;
        switch (a) {
            case 1 :
                if (!is_finde(root, key)) {
                    insert(root, key);
                    n++;
                }
                break;
            case -1 :
                if (is_finde(root, key)) {
                    _delete(root, key);
                    n--;
                }
                break;
            case 0 :
                std::cout << kthElem(root, n - key) << "\n";
                break;
        }
        //print(root, "");
    }
    return 0;
}