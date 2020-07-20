#include <iostream>


class Segment_tree {
private:
    int *arr;
    int n;
    int find_near(int v, int vl, int vr, int k) {
        if (k > arr[v]) {
            return (find_near(0, 0, n - 1, 1));
        }
        if (vl == vr) {
            return vl;
        }
        int vm = (vl + vr) / 2;
        if (arr[2 * v + 1] >= k) {
            return find_near(2 * v + 1, vl, vm, k);
        } else {
            return find_near(2 * v + 2, vm + 1, vr, k - arr[2 * v + 1]);
        }
    }

    void build(int v, int vl, int vr) {
        if (vl == vr) {
            arr[v] = 1;
            return;
        }
        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm);
        build(2 * v + 2, vm + 1, vr);
        arr[v] = arr[2 * v + 1] + arr[2 * v + 2];
    }

public:
    Segment_tree(int n) {
        this->n = n;
        arr = new int[4 * n];
        for (int i = 0; i < 4 * n; i++)
            arr[i] = -1; // free = 1
        this->build(0, 0, n - 1);
    }

    int sum(int v, int vl, int vr, int l, int r) {
        if (r < vl || vr < l) {
            return 0;
        }
        if (l <= vl && vr <= r) {
            return arr[v];
        }
        int vm = (vl + vr) / 2;
        return sum(2 * v + 1, vl, vm, l, r) + sum(2 * v + 2, vm + 1, vr, l, r);
    }

    void enter(int v, int vl, int vr, int pos) {
        if (vl == vr && arr[v] == 1) {
            arr[v] = 0;
            std::cout << vl + 1 << "\n";
            return;
        } else if (vl == vr && arr[v] == 0) {
            enter(0, 0, n - 1, find_near(0, 0, n - 1, sum(0, 0, n - 1, 0, pos) + 1));
            return;
        }
        int vm = (vl + vr) / 2;
        if (pos <= vm) {
            enter(2 * v + 1, vl, vm, pos);
        } else {
            enter(2 * v + 2, vm + 1, vr, pos);
        }
        arr[v] = arr[2 * v + 1] + arr[2 * v + 2];
    }

    void exit(int v, int vl, int vr, int pos) {
        if (vl == vr) {
            arr[v] = 1;
            return;
        }
        int vm = (vl + vr) / 2;
        if (pos <= vm) {
            exit(2 * v + 1, vl, vm, pos);
        } else {
            exit(2 * v + 2, vm + 1, vr, pos);
        }
        arr[v] = arr[2 * v + 1]  + arr[2 * v + 2];
    }
};

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    int n, _n, pos;
    std::string str;
    std::cin >> n >> _n;
    Segment_tree s_tree(n);
    for (int i = 0; i < _n; i++) {
        std::cin >> str >> pos;
        switch (str[1]) {
            case 'n' :
                s_tree.enter(0, 0, n - 1, pos - 1);
                break;
            case 'x' :
                s_tree.exit(0, 0, n - 1, pos - 1);
                break;
        }
    }
    return 0;
}