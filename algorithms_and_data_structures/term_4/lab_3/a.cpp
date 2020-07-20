#include <iostream>
#include <vector>

using std::vector;

const size_t MAXN = 20000000 + 10;

vector<uint32_t> numbers;
vector<char> prime(MAXN, true);

void init() {
    size_t n;
    std::cin >> n;
    numbers.resize(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
}

void process() {
    prime[0] = prime[1] = false;
    for (size_t i = 2; i <= MAXN; ++i) {
        uint64_t tmp = i * 1ULL * i;
        if (tmp < 0) {
            std::cout << tmp << std::endl;
        }
        if (prime[i] && i * 1ULL * i <= MAXN * 1ULL) {
            for (size_t j = i * i; j <= MAXN; j += i) {
                prime[j] = false;
            }
        }
    }
}

void out() {
    for (auto& number : numbers) {
        std::cout << (prime[number] ? "YES\n" : "NO\n");
    }
}

void solve() {
    init();
    process();
    out();
}

int main() {
    solve();
}