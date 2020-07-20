#include <iostream>

int64_t m[2], r[2];
int64_t x = 0;

int64_t gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void input() {
    scanf("%lld%lld%lld%lld", &r[0], &r[1], &m[0], &m[1]);
}

void process() {
    int64_t const M = m[0] * m[1];
    for (size_t i = 0; i < 2; i++) {
        int64_t y_i = M / m[i];
        int64_t x1, y1;
        gcd(y_i, m[i], x1, y1);
        int64_t s_i = (x1 % m[i] + m[i]) % m[i],
                c_i = (r[i] * s_i) % m[i];

           x = (x + c_i * y_i) % M;
    }

}

void out() {
    printf("%lld", x);
}

void solve() {
    input();
    process();
    out();
}

int main() {
    solve();
}

