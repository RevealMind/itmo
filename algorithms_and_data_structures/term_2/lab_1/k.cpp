#include <iostream>
#include <cstdio>

struct Segment_Tree {
    long long *sum, *hash_sum, *pow, *pref_hash_sum;

    Segment_Tree(long long *arr, int n) {
        sum = new long long[4 * n];
        hash_sum = new long long[4 * n];
        pow = new long long[n + 1];
        pref_hash_sum = new long long[n + 1];
        for (int i = 0; i < n; i++)
            sum[i] = hash_sum[i] = 0;
        build(0, 0, n - 1, arr);
        pref_hash_sum[0] = 0;
        for (int i = 1; i < n + 1; i++) {
            pref_hash_sum[i] = pref_hash_sum[i - 1] + pow[i];
        }
    }

    bool check(int l, int r, int n) {
        /*printf("%lld == %lld\n%lld == %lld", pref_hash_sum[r - l + 1], get_sum(0, 0, n - 1, l - 1, r - 1, false),
               static_cast<long long int>(((r - l + 1) * (1 + (r - l + 1))) / 2), get_sum(0, 0, n - 1, l - 1, r - 1, true));*/
        return (pref_hash_sum[r - l + 1] == get_sum(0, 0, n - 1, l - 1, r - 1, false)
                && (((r - l + 1) * (1 + (r - l + 1))) / 2) == get_sum(0, 0, n - 1, l - 1, r - 1, true));
    }

    long long get_sum(int v, int vl, int vr, int l, int r, bool flag) {
        if (r < vl || vr < l) {
            return 0;
        }
        if (l <= vl && vr <= r) {
            return (flag) ? sum[v] : hash_sum[v];
        }
        int vm = (vl + vr) / 2;
        return get_sum(2 * v + 1, vl, vm, l, r, flag) + get_sum(2 * v + 2, vm + 1, vr, l, r, flag);
    }

    void modify(int v, int vl, int vr, int pos, int val) {
        if (vl == vr) {
            hash_sum[v] = pow[val];
            sum[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (pos <= vm)
            modify(2 * v + 1, vl, vm, pos, val);
        else
            modify(2 * v + 2, vm + 1, vr, pos, val);
        sum[v] = sum[2 * v + 1] + sum[2 * v + 2];
        hash_sum[v] = hash_sum[2 * v + 1] + hash_sum[2 * v + 2];
    }

private:
    void build(int v, int vl, int vr, long long *arr) {
        if (vl == vr) {
            sum[v] = arr[vl];
            pow[arr[vl]] = hash_sum[v] = hash(arr[vl]);
            return;
        }
        int vm = (vl + vr) / 2;
        build(2 * v + 1, vl, vm, arr);
        build(2 * v + 2, vm + 1, vr, arr);
        sum[v] = sum[2 * v + 1] + sum[2 * v + 2];
        hash_sum[v] = hash_sum[2 * v + 1] + hash_sum[2 * v + 2];
    }

    long long hash(long long val) {
        return bin_pow(val, 2);
    }

    long long bin_pow(long long a, long long n) {
        if (n == 0) {
            return 1;
        }
        if (n % 2 == 1) {
            return bin_pow(a, n - 1) * a;
        } else {
            long long b = bin_pow(a, n / 2);
            return b * b;
        }
    }
};

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    int n, m;
    scanf("%d", &n);
    long long *arr = new long long[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    Segment_Tree s_tree(arr, n);
    scanf("%d", &m);
    int op, i1, i2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &op, &i1, &i2);
        switch (op) {
            case 2:
                if (s_tree.check(i1, i2, n))
                    std::cout << "YES\n";
                else std::cout << "NO\n";
                break;
            case 1:
                s_tree.modify(0, 0, n - 1, i1 - 1, i2);
                break;
        }
    }
    return 0;
}