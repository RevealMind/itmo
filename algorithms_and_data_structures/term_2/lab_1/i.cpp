#include <iostream>
#include <cstdio>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct Segment_Tree_Node {
    int rise_set;
    int rise;
    int high;
    Segment_Tree_Node *left, *right;

    Segment_Tree_Node() :
            rise_set(INF), rise(0), high(0), left(NULL), right(NULL) {};
};

void push(Segment_Tree_Node *v, int vl, int vr) {

    if (vl != vr) {
        if (!v->left && !v->right) {
            v->left = new Segment_Tree_Node();
            v->right = new Segment_Tree_Node();
        }
    }

    if (v->rise_set != INF) {
        v->high = v->rise = (vr - vl + 1) * v->rise_set;
        if (vl != vr) {
            v->left->rise_set = v->rise_set;
            v->right->rise_set = v->rise_set;
        }
        v->rise_set = INF;
    }
}

void modify(Segment_Tree_Node *v, int vl, int vr, int l, int r, int new_rise) {
    push(v, vl, vr);
    if (r < vl || vr < l) {
        return;
    }
    if (l <= vl && vr <= r) {
        v->rise_set = new_rise;
        push(v, vl, vr);
        return;
    }
    int vm = (vl + vr) / 2;
    modify(v->left, vl, vm, l, r, new_rise);
    modify(v->right, vm + 1, vr, l, r, new_rise);
    v->rise = v->left->rise + v->right->rise;
    v->high = std::max(v->left->high, v->left->rise + v->right->high);
}


void print(Segment_Tree_Node *v, std::string offset) {
    if (!v) {
        return;
    }
    print(v->right, offset + "     ");
    std::cout << offset << v->rise << "( " << v->high << " )" << "\n";
    print(v->left, offset + "     ");
}

int find(Segment_Tree_Node *v, int vl, int vr, int high) {
    push(v, vl, vr);
    if (vl == vr) {
        return (high >= v->rise) ? vl + 1 : vl;
    }
    int vm = (vl + vr) / 2;
    push(v->left, vl, vm);
    if (high < v->left->high)
        return find(v->left, vl, vm, high);
    else
        return find(v->right, vm + 1, vr, high - v->left->rise);

}

int main() {
    Segment_Tree_Node *root = new Segment_Tree_Node();
    int n;
    scanf("%d", &n);
    char c;
    int high, rise;
    int l, r;
    while (true) {
        scanf("%c", &c);
        switch (c) {
            case 'Q' :
                scanf("%d", &high);
                printf("%d\n", find(root, 0, n - 1, high));
                //print(root, "");
                break;
            case 'I' :
                scanf("%d %d %d", &l, &r, &rise);
                modify(root, 0, n - 1, l - 1, r - 1, rise);
                //print(root, "");
                break;
            case 'E' :
                return 0;
        }
    }
}