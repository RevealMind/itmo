#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

std::string str, str1, str2;
int pos;
using std::vector;
using std::pair;

vector<int> suf_mas(std::string &str) {
    int n = str.size();
    vector<int> out(n);
    vector<int> class_eq(n);
    for (int i = 0; i < n; ++i) {
        out[i] = i;
    }
    std::sort(out.begin(), out.end(), [&str](int a, int b) {
        return str[a] < str[b];
    });
    class_eq[0] = 0;
    for (int i = 1; i < n; i++) {
        if (str[out[i]] == str[out[i - 1]]) {
            class_eq[i] = class_eq[i - 1];
        } else {
            class_eq[i] = class_eq[i - 1] + 1;
        }
    }

    vector<int> rev_out(n);

    for (int h = 1; (1 << (h - 1)) <= n; ++h) {
        for (int i = 0; i < n; i++) {
            rev_out[out[i]] = i;
        }

        std::sort(out.begin(), out.end(), [&class_eq, &rev_out, h, n](int a, int b) {
            return std::less<std::pair<int, int> >()(
                    std::make_pair(class_eq[rev_out[a]], class_eq[rev_out[(a + (1 << (h - 1))) % n]]),
                    std::make_pair(class_eq[rev_out[b]], class_eq[rev_out[(b + (1 << (h - 1))) % n]])
            );
        });

        vector<int> new_class_eq(n);
        new_class_eq[0] = 0;

        for (int i = 1; i < n; i++) {
            if ((class_eq[rev_out[out[i]]] !=
                 class_eq[rev_out[out[i - 1]]]) ||
                (class_eq[rev_out[(out[i] + (1 << (h - 1))) % n]] !=
                 class_eq[rev_out[(out[i - 1] + (1 << (h - 1))) % n]])) {
                new_class_eq[i] = new_class_eq[i - 1] + 1;
            } else {
                new_class_eq[i] = new_class_eq[i - 1];
            }
        }

        class_eq = new_class_eq;
    }
    return out;
}

vector<int> lcp(vector<int> &suf_mas) {
    int n = str.size();
    vector<int> out(n);
    vector<int> rev_suf(n);
    for (int i = 0; i < n; ++i) {
        rev_suf[suf_mas[i]] = i;
    }

    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (cur > 0) {
            --cur;
        }

        if (rev_suf[i] == n - 1) {
            out[n - 1] = -1;
            cur = 0;
            continue;
        }

        for (int tmp = suf_mas[rev_suf[i] + 1];
             std::max(i + cur, tmp + cur) < n && str[i + cur] == str[tmp + cur]; ++cur);

        out[rev_suf[i]] = cur;
    }

    return out;
}

void init() {
    std::cin >> str1 >> str2;
    std::cin >> pos;
}

void solve() {
    str = str1 + (char)('a' - 5) + str2 + (char)('a' - 10);
    int n = str.size();
    vector<int> s_mas = suf_mas(str);
    vector<int> lcp_mas = lcp(s_mas);
    int out_size = std::numeric_limits<int>::min(), out_pos;
    for (int i = 2; i < lcp_mas.size() - 1; i++) {
        if (s_mas[i] < str1.size() && str1.size() < s_mas[i + 1] ||
                s_mas[i + 1] < str1.size() && str1.size() < s_mas[i]) {
            if (out_size < lcp_mas[i]) {
                out_size = std::max(out_size, lcp_mas[i]);
                out_pos = s_mas[i];
            }
        }
    }
    std::cout << str.substr(out_pos, out_size);
}

int main() {
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);
    init();
    solve();
    return 0;
}