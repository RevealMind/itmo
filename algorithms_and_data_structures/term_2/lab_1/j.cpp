#include <algorithm>
#include <cstdio>
#include <iostream>

struct Segment_Tree {
    int *min, *set;
    const int MAX = 10000000;

    Segment_Tree(int *arr, int n) {
        min = new int[4 * n];
        set = new int[4 * n];
        for (int i = 0; i < 4 * n; i++) {
            min[i] = MAX;
            set[i] = 0;
        }
        build(0, 0, n - 1, arr);
    }

    int get_min(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (r < vl || vr < l) {
            return MAX;
        }

        if (l <= vl && vr <= r) {
            return min[v];
        }
        int vm = (vl + vr) / 2;
        return std::min(get_min(2 * v + 1, vl, vm, l, r), get_min(2 * v + 2, vm + 1, vr, l, r));
    }

    void modify(int v, int vl, int vr, int l, int r, int val) {
        push(v, vl, vr);
        if (r < vl || vr < l)
            return;
        if (l <= vl && vr <= r) {
            set[v] = val;
            push(v, vl, vr);
            return;
        }
        int vm = (vl + vr) / 2;
        modify(2 * v + 1, vl, vm, l, r, val);
        modify(2 * v + 2, vm + 1, vr, l, r, val);
        min[v] = std::min(min[2 * v + 1], min[2 * v + 2]);
    }


    int get_pos(int v, int vl, int vr, int l, int r, int val) {
        push(v, vl, vr);
        if (r < vl || vr < l)
            return MAX;
        int vm = (vl + vr) / 2;
        if (l <= vl && vr <= r) {
            if (vl == vr) {
                return (min[v] == val)? vl : MAX;
            }
            push(2 * v + 1, vl, vm);
            push(2 * v + 2, vm + 1, vr);
            if (min[2 * v + 1] == val)
                return get_pos(2 * v + 1, vl, vm, l, r, val);
            else
                return get_pos(2 * v + 2, vm + 1, vr, l, r, val);
        }
        return std::min(get_pos(2 * v + 1, vl, vm, l, r, val), get_pos(2 * v + 2, vm + 1, vr, l, r, val));
    }

    void print(int v, int vl, int vr, std::string offset) {
        if (vl == vr) {
            std::cout << offset << min[v] << std::endl;
            return;
        }
        int vm = (vl + vr) / 2;
        print(2 * v + 2, vm + 1, vr, offset + "   ");
        std::cout << offset << min[v] << "(" << set[v] << ")" << std::endl;
        print(2 * v + 1, vl, vm, offset + "   ");
    }

private:
    void build(int v, int vl, int vr, int *arr) {
        if (vl == vr) {
            min[v] = arr[vl];
            return;
        }

        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm, arr);
        build(2 * v + 2, vm + 1, vr, arr);
        min[v] = std::min(min[2 * v + 1], min[2 * v + 2]);
    }

    void push(int v, int vl, int vr) {
        if (set[v] != 0) {
            min[v] = std::max(min[v], set[v]);
            if (vl != vr) {
                set[2 * v + 1] = std::max(set[v], set[2 * v + 1]);
                set[2 * v + 2] = std::max(set[v], set[2 * v + 1]);
            }
            set[v] = 0;
        }
    }
};

int main() {
    //freopen("j.in", "r", stdin);
    //freopen("j.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    Segment_Tree s_tree(arr, n);
    std::string str;
    int l, r, set;
    for (int i = 0; i < m; i++) {
        std::cin >> str;
        scanf("%d %d", &l, &r);
        switch (str[0]) {
            case 'd' :
                scanf("%d", &set);
                s_tree.modify(0, 0, n - 1, l - 1, r - 1, set);
                //std::cout << "-------------------------------------------------\n";
                //s_tree.print(0, 0, n - 1, "");
                //std::cout << "-------------------------------------------------\n";
                break;
            case 'a' :
                printf("%d %d\n", s_tree.get_min(0, 0, n - 1, l - 1, r - 1),
                       s_tree.get_pos(0, 0, n - 1, l - 1, r - 1, s_tree.get_min(0, 0, n - 1, l - 1, r - 1)) + 1);
                //std::cout << "-------------------------------------------------\n";
                //s_tree.print(0, 0, n - 1, "");
                //std::cout << "-------------------------------------------------\n";
                break;
        }
    }
    return 0;
}