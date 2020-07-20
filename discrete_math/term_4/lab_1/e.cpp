//
// Created by Dmitry on 14.04.2019.
//

#include <iostream>
#include <vector>

using std::vector;

const int64_t MOD = 998244353;
vector<vector<int64_t>> C;

int64_t C_init(int k) {
    C.assign(k + 1, vector<int64_t>(k + 1));
    for (int n = 0; n <= k; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % MOD;
            while (C[n][k] < 0)
                C[n][k] += MOD;
        }
    }

}

int64_t normalize(int64_t &a) {
    while (a < 0) {
        a += MOD;
    }
    return a;
}
/*
int main() {
    int k, n, a_tree_size, b_tree_size;
    std::cin >> k >> n;
    C_init(k);

    a_tree_size = (k - 1) / 2;
    b_tree_size = k / 2;
    vector<int64_t> a_tree(5005, 0), b_tree(5005, 0), b_tree_inv(5005, 0);
    if (k % 2 == 0) {
        a_tree_size++;
    } else {
        b_tree_size++;
    }

    for (int i = 0; i < a_tree_size; i++) {
        a_tree[i] = (i % 2 == 0 ? 1 : -1) * C[k - 1 - i - 1][i] ;
    }

    for (int i = 0; i < b_tree_size; i++) {
        b_tree[i] = (i % 2 == 0 ? 1 : -1) * C[k - i - 1][i];
    }

    //---- A / B ----

    b_tree_inv[0] = (1 / b_tree[0]);
    for (int k = 1; k <= n; k++) {
        int64_t sum_k = 0;
        for (int i = 1; i <= k; i++) {
            sum_k = (sum_k + b_tree[i] * b_tree_inv[k - i] + MOD) % MOD;
            normalize(sum_k);
        }
        b_tree_inv[k] = ((-sum_k / b_tree[0]) + MOD) % MOD;
        normalize(b_tree_inv[k]);
    }

    for (int k = 0; k < n; k++) {
        int64_t sum_k = 0;
        for (int i = 0; i <= k; i++) {
            sum_k = (sum_k + a_tree[i] * b_tree_inv[k - i]) % MOD;
            normalize(sum_k);
        }
        std::cout << sum_k << "\n";
    }
}*/