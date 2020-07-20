//
// Created by Dmitry on 14.04.2019.
//

#include <iostream>
#include <vector>


using std::vector;

const int64_t MOD = 104857601;

int main() {
    int k;
    int64_t n;
    std::cin >> k >> n;
    n--;
    vector<int64_t> a(2 * k);
    vector<int64_t> q(2000, 0);
    vector<int64_t> r(2000, 0);
    vector<int64_t> q_neg_t(2000, 0);

    for (int64_t in, i = 0; i < k; i++) {
        std::cin >> in;
        a[i] = in;
    }

    q[0] = 1;
    for (int64_t in, i = 1; i <= k; i++) {
        std::cin >> in;
        q[i] = (MOD - in) % MOD;
    }

    while (n >= k) {
        for (int i = k; i < 2 * k; i++) {
            a[i] = 0;
            for (int j = 1; j <= k; j++) {
                a[i] = (a[i] - q[j] * a[i - j]) % MOD;
                while (a[i] < 0)
                    a[i] += MOD;
            }
        }

        for (int i = 0; i <= k; i++) {
                q_neg_t[i] = (i % 2) == 0 ? q[i] : (MOD - q[i]) % MOD;
        }

        for (int i = 0; i <= 2 * k; i += 2) {
            int64_t sum = 0;
            for (int j = 0; j <= i; j++) {
                sum = (sum + q[j] * q_neg_t[i - j] + MOD) % MOD;
            }
            r[i / 2] = sum;
        }

        for (int i = 0; i <= k; i++)
            q[i] = r[i];

        for (int ind = 0, i = 0; i < 2 * k; i++) {
            if (n % 2 == i % 2) {
                a[ind] = a[i];
                ind++;
            }
        }
        n = n / 2;
    }
    std::cout << a[n];
}