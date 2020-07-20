#include <iostream>

class Segment_tree {
private:
    const long long INF = 9223372036854775807;
    const long long IDEN = 1000000000000000001;
    long long *arr;
    long long *add;
    long long *set;

    void push(int v, int vl, int vr) {
        if (set[v] != IDEN) {
            arr[v] = set[v];
            if (vl != vr) {
                set[2 * v + 1] = set[v];
                set[2 * v + 2] = set[v];
                add[2 * v + 1] = 0;
                add[2 * v + 2] = 0;
            }
            set[v] = IDEN;
        }
        if (add[v] != 0) {
            arr[v] += add[v];
            if (vl != vr) {
                add[2 * v + 1] += add[v];
                add[2 * v + 2] += add[v];
            }
            add[v] = 0;
        }
    }

public:
    Segment_tree(int n) {
        arr = new long long[4 * n];
        add = new long long[4 * n];
        set = new long long[4 * n];
        for (int i = 0; i < 4 * n; i++) {
            arr[i] = INF;
            add[i] = 0;
            set[i] = IDEN;
        }
    }

    void build(int v, int vl, int vr, const long long *a) {
        if (vl == vr) {
            arr[v] = a[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm, a);
        build(2 * v + 2, vm + 1, vr, a);
        arr[v] = std::min(arr[2 * v + 1], arr[2 * v + 2]);
    }

    void print(int v, std::string offset) {
        if (arr[v] == INF) {
            std::cout << offset << "INF\n";
            return;
        }
        print(2 * v + 2, offset + "      ");
        std::cout << offset << arr[v] << "/";
        if(set[v] == IDEN) std::cout << "NaN/";
        else std::cout << set[v] << "/";
        if(add[v] == 0) std::cout << "NaN\n";
        else std::cout << add[v] << "\n";
        print(2 * v + 1, offset + "      ");
    }

    long long min(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (r < vl || vr < l) {
            return (INF);
        }
        if (l <= vl && vr <= r) {
            return arr[v];
        }
        int vm = (vl + vr) / 2;
        return std::min(min(2 * v + 1, vl, vm, l, r), min(2 * v + 2, vm + 1, vr, l, r));
    }

    void modify(int v, int vl, int vr, int l, int r, long long  add, long long set) {
        push(v, vl, vr);
        if (r < vl || vr < l) {
            return;
        }
        if (l <= vl && vr <= r) {
            if (add != 0)
                this->add[v] += add;
            if (set != IDEN) {
                this->set[v] = set;
            }
            push(v, vl, vr);
            return;
        }
        int vm = (vl + vr) / 2;
        modify(2 * v + 1, vl, vm, l, r, add, set);
        modify(2 * v + 2, vm + 1, vr, l, r, add, set);
        arr[v] = std::min(arr[2 * v + 1], arr[2 * v + 2]);
    }
};

int main() {
    freopen("rmq2.in", "r", stdin);
    freopen("rmq2.out", "w", stdout);
    int n;
    std::cin >> n;
    Segment_tree s_tree(n);
    long long *arr = new long long[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    s_tree.build(0, 0, n - 1, arr);
    std::string str;
    int i1, i2, i3;
    while (std::cin >> str >> i1 >> i2) {
        switch (str[0]) {
            case 'm' :
                std::cout << s_tree.min(0, 0, n - 1, i1 - 1, i2 - 1) << "\n";
                //s_tree.print(0, "");
                //std::cout << "-------------------------------------------\n\n";
                break;
            case 'a':
                std::cin >> i3;
                s_tree.modify(0, 0, n - 1, i1 - 1, i2 - 1, i3, 1000000000000000001);
                //s_tree.print(0, "");
                //std::cout << "-------------------------------------------\n\n";
                break;
            case 's' :
                std::cin >> i3;
                s_tree.modify(0, 0, n - 1, i1 - 1, i2 - 1, 0, i3 );
                //s_tree.print(0, "");
                //std::cout << "-------------------------------------------\n\n";
                break;
        }
    }
    return 0;
}