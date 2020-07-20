#include <iostream>

int MOD;

struct Matrix {
    int x11, x12, x21, x22;
    Matrix(int x11 = 1, int x12 = 0, int x21 = 0, int x22 = 1):
            x11(x11), x12(x12), x21(x21), x22(x22) {};
};

class Segment_tree {
private:
    Matrix *arr;
    Matrix neutral;
public:
    Segment_tree(int n, Matrix *arr) {
        this->arr = new Matrix[4 * n];
        neutral.x11 = 1;
        neutral.x12 = 0;
        neutral.x21 = 0;
        neutral.x22 = 1;
        this->build(0, 0, n - 1, arr);
    }

    Matrix mul_m(const Matrix &a, const Matrix &b) {
        return Matrix((a.x11 * b.x11 + a.x12 * b.x21) % MOD,
               (a.x11 * b.x12 + a.x12 * b.x22) % MOD,
               (a.x21 * b.x11 + a.x22 * b.x21) % MOD,
               (a.x21 * b.x12 + a.x22 * b.x22) % MOD);
    }

    void build(int v, int vl, int vr, Matrix *a) {
        if (vl == vr) {
            arr[v] = a[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm, a);
        build(2 * v + 2, vm + 1, vr, a);
        arr[v] = mul_m(arr[2 * v + 1],arr[2 * v + 2]);
    };

    Matrix mul(int v, int vl, int vr, int l, int r) {
        if (r < vl || vr < l) {
            return neutral;
        }
        if (l <= vl && vr <= r) {
            return arr[v];
        }
        int vm = (vl + vr) / 2;
        return mul_m(mul(2 * v + 1, vl, vm, l, r), mul(2 * v + 2, vm + 1, vr, l, r));
    }
};

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int n, m, left, right;
    std::cin >> MOD >> n >> m;
    Matrix *arr = new Matrix[n];
    for (int i = 0; i < n; i++)
        scanf("%d %d %d %d", &arr[i].x11, &arr[i].x12, &arr[i].x21, &arr[i].x22);
    Segment_tree s_tree(n, arr);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &left, &right);
        Matrix t = s_tree.mul(0, 0, n - 1, left - 1, right - 1);
        printf("%d %d\n%d %d\n", t.x11, t.x12, t.x21, t.x22);
    }
    return 0;
}