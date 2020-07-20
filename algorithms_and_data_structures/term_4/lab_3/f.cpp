#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>

# define PI           3.14159265358979323846

using std::string;
using std::vector;

vector<int32_t> a, b, ans;
bool is_neg = false;

void check_sign(string &number_s) {
    if (number_s[0] == '-') {
        is_neg ^= true;
        number_s[0] = '0';
    }
}

void str_to_vec(string &number_s, vector<int32_t> &number) {
    for (auto &c: number_s) {
        number.push_back((int32_t) (c - '0'));
    }
    std::reverse(number.begin(), number.end());
}

void input() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    string a_s, b_s;
    std::cin >> a_s >> b_s;

    check_sign(a_s);
    check_sign(b_s);

    str_to_vec(a_s, a);
    str_to_vec(b_s, b);
}

void fft(vector<std::complex<double>> &a, bool invert) {
    size_t n = a.size();
    if (n == 1) {
        return;
    }

    vector<std::complex<double>> a0(n / 2);
    vector<std::complex<double>> a1(n / 2);

    for (size_t i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double ang = (invert ? -2 : 2) * PI / n;
    std::complex<double> w(1, 0);
    std::complex<double> wn(std::cos(ang), std::sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

size_t normalize_size(size_t max_size) {
    size_t size = 1;
    while (size < max_size) {
        size <<= 1;
    }
    size <<= 1;
    return size;
}

void normalize_number(vector<int32_t> &number) {
    int carry = 0;
    for (size_t i = 0; i < ans.size(); ++i) {
        ans[i] += carry;
        carry = ans[i] / 10;
        ans[i] %= 10;
    }
}

void process()  {
    vector<std::complex<double> > f_a(a.begin(), a.end());
    vector<std::complex<double> > f_b(b.begin(), b.end());

    size_t size = normalize_size(std::max(a.size(), b.size()));

    f_a.resize(size);
    f_b.resize(size);

    fft(f_a, false);
    fft(f_b, false);
    for (size_t i = 0; i < size; ++i) {
        f_a[i] *= f_b[i];
    }

    fft(f_a, true);

    ans.resize(size);
    for (size_t i = 0; i < size; ++i) {
        ans[i] = std::lround(f_a[i].real());
    }

    normalize_number(ans);
}

int32_t skip_leading_zeros(vector<int32_t> &number) {
    for (size_t ind = number.size() - 1; ind >= 0; --ind) {
        if (number[ind]) {
            return ind;
        }
    }
    return -1;
}

void out() {
    int32_t ind = skip_leading_zeros(ans);
    if (ind != -1) {
        if (is_neg) {
            std::cout << '-';
        }
        for (; ind >= 0; --ind) {
            std::cout << ans[ind];
        }
    } else {
        std::cout << "0";
    }
}

void solve() {
    input();
    process();
    out();
}

int main() {
    solve();
}

