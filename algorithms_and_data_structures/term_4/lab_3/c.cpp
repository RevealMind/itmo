#include <iostream>

int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool even(int64_t &number) {
    return !(number & 1);
}

void transform(int64_t number, int64_t &p, int64_t &q) {
    p = 0;
    while (even(number)) {
        ++p;
        number >>= 1;
    }
    q = number;
}

int64_t mul_mod(int64_t a, int64_t b, int64_t const &mod) {
    int64_t ans = 0;
    while (b) {
        if (!even(b))
            ans = (ans + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

int64_t bin_pow(int64_t a, int64_t n, int64_t const &mod) {
    int64_t ans = 1;
    while (n) {
        if (!even(n)) {
            ans = mul_mod(ans, a, mod);
        }
        a = mul_mod(a, a, mod);
        n >>= 1;
    }
    return ans;
}

bool miller_rabin(int64_t &number) {
    if (number == 2) {
        return true;
    }

    if (number < 2 || even(number)) {
        return false;
    }

    int64_t t_number = number - 1, p, q;
    transform(t_number, p, q);

    for (int i = 0; i < 5; ++i) {
        int64_t b = (rand() % (number - 2)) + 2;
        int64_t rem = bin_pow(b, q, number);

        if (rem == 1 || rem == t_number) {
            continue;
        }

        for (int j = 1; j < p; ++j) {
            rem = mul_mod(rem, rem, number);
            if (rem == t_number) {
                break;
            }
        }

        if (rem != t_number) {
            return false;
        }
    }
    return true;
}

void solve() {
    srand(NULL);
    size_t n;
    scanf("%d", &n);
    for (size_t i = 0; i < n; ++i) {
        int64_t a;
        scanf("%lld", &a);
        if (miller_rabin(a)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    solve();
}

