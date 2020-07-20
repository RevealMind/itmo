#include <iostream>

struct Segment_tree {

private :
    long long *arr;
public:
    Segment_tree(int n) {
        arr = new long long[4 * n];
        for (int i = 0; i < 4 * n; i++) {
            arr[i] = NULL;
        }
    }

    void build(const int *value, int v, int l, int r) {
        if (l == r) {
            arr[v] = value[r];
            return;
        }
        int m = (l + r) / 2;
        this->build(value, 2 * v, l, m);
        this->build(value, 2 * v + 1, m + 1, r);
        arr[v] = arr[2 * v] + arr[2 * v + 1];
        return;
    }

    void print(int v, std::string offset) {
        if (arr[v] == NULL) {
            std::cout << offset << "NULL" << "\n";
            return;
        }
        print(v * 2, offset + "   ");
        std::cout << offset << arr[v] << "\n";
        print(v * 2 + 1, offset + "   ");
        return;
    }

    long long sum(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == tl && tr == r)
            return arr[v];
        int tm = (tl + tr) / 2;
        return sum(2 * v, tl, tm, l, std::min(tm, r))
               + sum(2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r);
    }

    void update(int v, int tl, int tr, int p, int val) {
        if (tl == tr)
            arr[v] = val;
        else {
            int tm = (tl + tr) / 2;
            if (p <= tm)
                update(2 * v, tl, tm, p, val);
            else
                update(2 * v + 1, tm + 1, tr, p, val);
            arr[v] = arr[2 * v] + arr[2 * v + 1];
        }
    }
};

int main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    int n, i1, i2;
    std::cin >> n;
    Segment_tree s_tree(n);
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    s_tree.build(arr, 1, 0, n - 1);
    std::string str;
    while (std::cin >> str) {
        std::cin >> i1 >> i2;
        switch (str[1]) {
            case 'u' :
                std::cout << s_tree.sum(1, 0, n - 1, i1 - 1, i2 - 1) << "\n";
                break;
            case 'e' :
                s_tree.update(1, 0, n - 1, i1 - 1, i2);
                break;
        }
    }
    return 0;
}