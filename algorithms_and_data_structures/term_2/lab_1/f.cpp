#include <iostream>

class Sparse_Table {
    int *log;
    int **arr;
public:
    Sparse_Table(int *a, int size) {
        log = new int[100005];
        arr = new int *[20];
        for (int i = 0; i < 20; i++)
            arr[i] = new int[100005];
        log[0] = log[1] = 0;
        for (int i = 2; i <= size; i++)
            log[i] = log[i / 2] + 1;
        for (int j = 0; (1 << j) <= size; j++)
            for (int i = 0; i + (1 << j) <= size; i++)
                arr[j][i] = (j) ? std::min(arr[j - 1][i], arr[j - 1][i + (1 << j - 1)]) : a[i];
    }

    int min(int l, int r) {
        int newlog = log[r - l + 1];
        return std::min(arr[newlog][l], arr[newlog][r - (1 << newlog) + 1]);
    }
};

int main() {
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    scanf("%d", &a[0]);
    for (int i = 1; i < n; i++)
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    Sparse_Table s(a, n);
    int u[m], v[m];
    scanf("%d %d", &u[0], &v[0]);
    for (int i = 1; i < m; i++) {
        int ans = s.min(std::min(u[i - 1] - 1, v[i - 1] - 1), std::max(u[i - 1] - 1, v[i - 1] - 1));
        u[i] = ((17 * u[i - 1] + 751 + ans + 2 * i) % n) + 1;
        v[i] = ((13 * v[i - 1] + 593 + ans + 5 * i) % n) + 1;
    }
    printf("%d %d %d", u[m - 1], v[m - 1],
           s.min(std::min(u[m - 1] - 1, v[m - 1] - 1), std::max(u[m - 1] - 1, v[m - 1] - 1)));
}