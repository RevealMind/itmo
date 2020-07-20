#include <iostream>
#include <vector>

std::string s;
using std::size_t;
using std::vector;

void solve() {
    size_t k, a, b, c, d;

    std::cin >> s >> k;

    size_t n = s.size();
    vector<long long> pow(n);
    vector<long long> hash(n);
    pow[0] = 1;

    for (int i = 1; i < n; ++i) {
        pow[i] = pow[i - 1] * 31;
    }

    for (int i = 0; i < n; i++) {
        hash[i] = (s[i] - 'a' + 1) * pow[i] + ((i) ? hash[i - 1] : 0);
    }

    for (int i = 0; i < k; ++i) {
        std::cin >> a >> b >> c >> d;
        if ((b - a) == (d - c)) {
            long long hash_first = hash[b - 1] - ((a - 1) ? hash[a - 2] : 0);
            long long hash_second = hash[d - 1] - ((c - 1) ? hash[c - 2] : 0);
            if (a < c) {
                hash_first *= pow[c - a];
            } else {
                hash_second *= pow[a - c];
            }
            if (hash_first == hash_second) {
                std::cout << "Yes";
            } else {
                std::cout << "No";
            }
        } else {
            std::cout << "No";
        }
        std::cout << "\n";
    }
}

int main() {
    solve();
    return 0;
}