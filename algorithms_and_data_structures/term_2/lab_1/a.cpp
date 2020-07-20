#include <iostream>
const int MOD_1 = (1 << 16), MOD_2 = (1 << 30);
void init(int *arr, const int n, const int x, const int y, const int MOD) //O(n)
{
    for (int i = 1; i < n; i++) {
        arr[i] = (x * arr[i - 1] + y) % MOD;
        if (arr[i] < 0) {
            arr[i] = MOD + arr[i];
        }
    }
}
int main() {
    freopen("sum0.in", "r", stdin);
    freopen("sum0.out", "w", stdout);
    int n, x, y, m, z, t;
    std::cin >> n >> x >> y;
    int *a = new int[n];
    std::cin >> a[0] >> m;
    int *b = new int[2 * m];
    int *c = new int[2 * m];
    std::cin >> z >> t >> b[0];
    init(a, n, x, y, MOD_1);
    long long *pref = new long long[n + 1];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i - 1]; // O(n)
    }
    init(b, 2 * m, z, t, MOD_2);
    for (int i = 0; i < 2 * m; i++) {
        c[i] = b[i] % n; // O(2m)
    }
    long long ans = 0;
    for (int i = 0; i < 2 * m; i += 2) // O(M)
    {
        if (c[i] > c[i + 1]) {
            int t = c[i];
            c[i] = c[i + 1];
            c[i + 1] = t;
        }
        ans += pref[c[i + 1] + 1] - pref[c[i]];
    }
    std::cout << ans;
}