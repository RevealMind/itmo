//
// Created by Dmitry on 14.04.2019.
//

#include <iostream>
#include <vector>


using std::vector;

std::string expression;
int ind = 0;

int64_t max(long long int a, long long int b);

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int64_t soch(int64_t n, int64_t k) {
    double res = 1;
    for (int64_t i = 1; i < k + 1; i++) {
        res = res * (n - k + i) / i;
    }
    return (int64_t) (res + 0.01);
}

vector<int64_t> solve() {
    vector<int64_t> out(7);
    vector<int64_t> l_expr;
    vector<int64_t> r_expr;
    switch (expression[ind]) {
        case 'B' :
            ind++;
            out = {0, 1, 0, 0, 0, 0, 0};
            break;
        case 'L' :
            ind += 2;
            l_expr = solve();
            ind++;
            out[0] = 1;
            for (int k = 1; k < 7; ++k) {
                int64_t sum_k = 0;
                for (int i = 1; i <= k; ++i) {
                    sum_k += l_expr[i] * out[k - i];
                }
                out[k] = sum_k;
            }
            break;
        case 'S' :
            ind += 2;
            l_expr = solve();
            ind++;

            int64_t m[7][7];
            m[0][0] = 1;
            for (int i = 1; i < 7; ++i) {
                m[0][i] = 1;
                m[i][0] = 0;
            }

            out[0] = 1;
            for (int n = 1; n < 7; ++n){
                for (int k = 1; k < 7; ++k) {
                    int64_t sum_k = 0;
                    for (int i = 0; i <= n / k; ++i) {
                        sum_k += soch(max(l_expr[k] + i - 1, 0LL), i) * m[n - i * k][k - 1];
                    }
                    m[n][k] = sum_k;
                }
                out[n] = m[n][n];
            }
            break;
        case 'C' :
            ind += 2;
            l_expr = solve();
            ind++;

            int64_t b[7][7];
            for (int n = 0; n < 7; ++n) {
                b[n][1] = l_expr[n];
                b[n][0] = 0;
                b[0][n] = 0;
            }

            for (int n = 1; n < 7; ++n) {
                for (int k = 2; k < 7; ++k) {
                    int64_t sum_k = 0;
                    for (int i = 1; i < n; ++i) {
                        sum_k += l_expr[i] * b[n - i][k - 1];
                    }
                    b[n][k] = sum_k;
                }
            }
            out[0] = 0;
            for (int n = 1; n < 7; ++n) {
                int64_t sum = 0;
                for (int s = 1; s <= n; ++s) {
                    int64_t st_i = 0;
                    for (int i = 0; i <= s - 1; ++i) {
                        int g = gcd(s, i);
                        int64_t tmp = (n % (s / g) != 0 ? 0 : b[(n * g) / s][g]);
                        st_i += tmp;
                    }
                    sum += st_i / s;
                }
                out[n] = sum;
            }
            break;
        case 'P' :
            ind += 2;
            l_expr = solve();

            ind++ ;
            r_expr = solve();
            ind++;

            for (int k = 0; k < 7; ++k) {
                int64_t sum_k = 0;
                for (int i = 0; i <= k; ++i) {
                    sum_k += l_expr[i] * r_expr[k - i];
                }
                out[k] = sum_k;
            }
            break;
    }
    return std::move(out);
}

int64_t max(long long int a, long long int b) {
    return a > b ? a : b;
}

//L(P(L(L(L(P(P(P(B,L(B)),L(B)),P(B,L(B)))))),P(B,L(B))))
/*
int main() {
    std::ios_base::sync_with_stdio(false);
    getline(std::cin, expression);
    for (auto o : solve()) {
        std::cout << o << " ";
    }
}
*/