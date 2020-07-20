#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

const size_t MAXN = 1000000 + 10;

vector<uint32_t> min_prime(MAXN);

void process() {
    for (size_t i = 0; i <= MAXN; ++i) {
        min_prime[i] = i;
    }

    for (size_t i = 2; i <= MAXN; ++i) {
        if (min_prime[i] == i && i * 1LL * i <= MAXN) {
            for (size_t j = i * i; j <= MAXN; j += i) {
                min_prime[j] = i;
            }
        }
    }
}

void out() {
    size_t n;
    scanf("%u", &n);
    uint32_t number;
    vector<uint32_t> out;
    for (size_t i = 0; i < n; ++i) {
        scanf("%u", &number);
        out.clear();
        while (number != 1) {
            uint32_t div = min_prime[number];
            out.push_back(div);
            number /= div;
        }
        std::sort(out.begin(), out.end());
        for (auto& o : out) {
            printf("%u ", o);
        }
        printf("\n");
    }
}

void solve() {
    process();
    out();
}

int main() {
    solve();
}