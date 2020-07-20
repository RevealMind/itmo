#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

int32_t n, e, c, d;

int32_t gcd(int32_t a, int32_t b, int32_t &x, int32_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int32_t x1, y1;
    int32_t d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void input() {
    scanf("%d%d%d", &n, &e, &c);
}

vector<int32_t> get_factorization(int32_t number) {
    for (int32_t i = 2 ; i <= sqrt(number); ++i) {
        if (n % i == 0) {
            return {i, n / i};
        }
    }
}

void process() {
    vector<int32_t> fact = get_factorization(n);
    int32_t phi = (fact[1] - 1) * (fact[0] - 1);
    int32_t x, y;
    gcd(e, phi, x, y);
    d = (x % phi + phi) % phi;
}

bool even(int32_t &number) {
    return !(number & 1);
}

int32_t mul_mod(int32_t a, int32_t b, int32_t const &mod) {
    int32_t ans = 0;
    while (b) {
        if (!even(b))
            ans = (ans + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

int32_t bin_pow(int32_t a, int32_t n, int32_t const &mod) {
    int32_t ans = 1;
    while (n) {
        if (!even(n)) {
            ans = mul_mod(ans, a, mod);
        }
        a = mul_mod(a, a, mod);
        n >>= 1;
    }
    return ans;
}

void out() {
    printf("%d", bin_pow(c, d, n));
}

void solve() {
    input();
    process();
    out();
}

int main() {
    solve();
}

