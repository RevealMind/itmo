#include <iostream>
#include <limits>
#include <cstdio>

struct Segment_Tree {
    long long *min, *arr, *leaf, *ans;
    const long long MAX = std::numeric_limits<int>::max(), UND = std::numeric_limits<long long>::min();

    Segment_Tree(int n) {
        leaf = new long long[n];
        min = new long long[4 * n];
        arr = new long long[4 * n];
        ans = new long long[4 * n];
        for (int i = 0; i < 4 * n; i++) {
            ans[i] = arr[i] = MAX;
            min[i] = UND;
        }
    }

    void modify(int v, int vl, int vr, int l, int r, long long val) {
        if (r < vl || vr < l) {
            return;
        }
        if (l <= vl && vr <= r) {
            min[v] = std::max(min[v], val);
            return;
        }
        int vm = (vl + vr) / 2;
        modify(2 * v + 1, vl, vm, l, r, val);
        modify(2 * v + 2, vm + 1, vr, l, r, val);
    }

    void push(int v, int vl, int vr) {
        if (min[v] != UND) {
            arr[v] = min[v];
            if (vl != vr) {
                min[2 * v + 1] = std::max(min[v], min[2 * v + 1]);
                //if (min[2 * v + 2] == UND)
                min[2 * v + 2] = std::max(min[v], min[2 * v + 2]);
            }
            min[v] = UND;
        }
    }

    long long get_min(int v, int vl, int vr, int l, int r) {
        if (r < vl || vr < l) {
            return (MAX);
        }
        if (l <= vl && vr <= r) {
            return ans[v];
        }
        int vm = (vl + vr) / 2;
        return std::min(get_min(2 * v + 1, vl, vm, l, r), get_min(2 * v + 2, vm + 1, vr, l, r));
    }

    void push_all(int v, int vl, int vr) {
        push(v, vl, vr);
        if (vl == vr) {

            leaf[vl] = arr[v];
            //std::cout << leaf[vl]<< "\n";
            return;
        }
        int vm = (vl + vr) / 2;
        push_all(2 * v + 1, vl, vm);
        push_all(2 * v + 2, vm + 1, vr);
    }

    void build(int v, int vl, int vr) {
        if (vl == vr) {
            ans[v] = leaf[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm);
        build(2 * v + 2, vm + 1, vr);
        ans[v] = std::min(ans[2 * v + 1], ans[2 * v + 2]);
    }

    void printl(int n) {
        for (int i = 0; i < n; i++) {
            std::cout << leaf[i] << " ";
        }
    }

    void print(int v, int vl, int vr, std::string offset) {
        if (vl == vr) {
            std::cout << offset << ans[v] << std::endl;
            return;
        }
        int vm = (vl + vr) / 2;
        print(2 * v + 2, vm + 1, vr, offset + "   ");
        std::cout << offset << ans[v]  << std::endl;
        print(2 * v + 1, vl, vm, offset + "   ");
    }
};

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    Segment_Tree s_tree(n);
    int *l = new int[m];
    int *r = new int[m];
    long long *min = new long long[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &l[i], &r[i], &min[i]);
        s_tree.modify(0, 0, n - 1, l[i] - 1, r[i] - 1, min[i]);
    }
    s_tree.push_all(0, 0, n - 1);
    s_tree.build(0, 0, n - 1);
    //std::cout << "-------------------------------------------------\n";
    //s_tree.print(0, 0, n - 1, "");
    //std::cout << "-------------------------------------------------\n";
    for (int i = 0; i < m; i++) {
        if (s_tree.get_min(0, 0, n - 1, l[i] - 1, r[i] - 1) != min[i]) {
            std::cout << "inconsistent" << std::endl;
            return 0;
        }
    }
    std::cout << "consistent\n";
    s_tree.printl(n);
    return 0;
}