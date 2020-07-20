//
// Created by Dmitry on 14.04.2019.
//

#include <iostream>
#include <vector>

using std::vector;

const uint64_t MOD = 1000000007LL;

/*int main() {
    size_t k_, m;
    std::cin >> k_ >> m;

    vector<bool> nodes(m + 1, false);
    vector<uint64_t> trees(m + 1);
    vector<uint64_t> pref_sum(m + 1);

    for (int in, i = 0; i < k_; i++) {
        std::cin >> in;
        nodes[in] = true;
    }

    trees[0] = 1;
    pref_sum[0] = 1;

    for (int k = 1; k <= m; k++) {
        uint64_t sum_k = 0;

        for (int i = 1; i <= k; i++) {
            if (nodes[i]) {
                sum_k +=  (pref_sum[k - i]) % MOD;
            }
        }

        trees[k] = sum_k % MOD;

        std::cout << trees[k] << ' ';

        for (int i = 0; i <= k; i++) {
            pref_sum[k] = (pref_sum[k] + trees[i] * trees[k - i]) % MOD;
        }
    }
}*/