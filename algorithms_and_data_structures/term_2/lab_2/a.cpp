#include <iostream>
#include <cstdlib>

struct Node {
    Node *left, *right;
    int key, priority;

    Node(int key) : left(nullptr), right(nullptr), key(key), priority(rand() * rand()) {}
};

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
}

Node *merge(Node *left, Node *right) {
    if (left == nullptr || right == nullptr) {
        return right == nullptr ? left : right;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
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
    if (!is_finde(curNode, key)) {
        Node *left = nullptr, *right = nullptr;
        split(curNode, left, right, key);
        Node *n = new Node(key);
        curNode = merge(merge(left, n), right);
    }
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
}
int get(Node *cur, char side) {
    switch (side) {
        case 'l' :
            if(cur->left != nullptr)
                return get(cur->left, side);
            break;
        case 'r' :
            if(cur->right != nullptr)
                return get(cur->right, side);
            break;
    }
    return cur->key;
}

int next(Node *curNode, int key) {
    Node *left = nullptr, *right = nullptr;
    split(curNode, left, right, key + 1);
    int ans = right != nullptr ? get(right, 'l') : key;
    merge(left, right);
    return ans;
}

int prev(Node *curNode, int key) {
    Node *left = nullptr, *right = nullptr;
    split(curNode, left, right, key);
    int ans = left != nullptr ? get(left, 'r') : key;
    merge(left, right);
    return ans;
}


void print(Node *root, std::string offset) {
    if(root == nullptr) {
        std::cout << "\n";
        return;
    }
    print(root->right, offset + "   ");
    std::cout << offset << root->key << std::endl;
    print(root->left, offset + "   ");
}

int main() {
    Node *root = nullptr;
    std::string str;
    int key;
    while (std::cin >> str) {
        std::cin >> key;
        switch (str[0]) {
            case 'i' :
                insert(root, key);
                break;
            case 'd' :
                if (is_finde(root, key))
                    _delete(root, key);
                break;
            case 'e' :
                if (is_finde(root, key)) {
                    std::cout << "true\n";
                } else
                    std::cout << "false\n";
                break;
            case 'n' :
                if (key != next(root, key)) {
                    std::cout << next(root, key) << "\n";
                } else
                    std::cout << "none\n";
                break;
            case 'p' :
                if (key != prev(root, key)) {
                    std::cout << prev(root, key) << "\n";
                } else
                    std::cout << "none\n";
                break;
        }
    }
    return 0;
}