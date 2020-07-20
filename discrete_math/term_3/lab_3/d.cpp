#include <iostream>
#include <vector>
#include <cstdio>

using std::vector;

vector<int> s;
int n, m;
bool check1, check3;
vector<bool> check2;

void check_pos_bit(int mask, vector<bool> &mas, bool state) {
    for (int i = 0; i < n; ++i) {
        if ((mask & (1 << i)) != 0)
            mas[i] = state;
    }
}

void init() {
    std::cin >> n >> m;
    s.resize(1 << n, -1);
    check2.resize(1 << n, false);
    for (int i = 0, size; i < m; ++i) {
        int elem = 0;
        std::cin >> size;
        if (size == 0)
            check1 = true;
        for (int j = 0, shift; j < size; j++) {
            std::cin >> shift;
            elem |= (1 << (shift - 1));
        }
        check2[elem] = true;
        s[elem] = size;
    }
}

void solve() {
    if (!check1) {
        std::cout << "NO";
        return;
    }

    for (int i = 1; i < (1 << n); ++i) {
        if (s[i] == -1) {
            continue;
        }
        int cur_ind = 0;
        while ((1 << cur_ind) <= i) {
            int cur = i & (~(1 << cur_ind));
            if (!check2[cur]) {
                std::cout << "NO";
                return;
            }
            cur_ind++;
        }
    }

    check3 = false;
    for (int i = 0; i < (1 << n); ++i) {
        if (s[i] != -1) {
            for (int j = i + 1;  j < (1 << n); ++j) {
                if (s[j] != -1) {
                    int mask_a = i, mask_b = j;
                    check3 = false;

                    if (s[mask_a] == s[mask_b])
                        continue;

                    if (s[mask_a] < s[mask_b]) {
                        std::swap(mask_a, mask_b);
                    }

                    vector<bool> a_without_b(n, false);

                    check_pos_bit(mask_a, a_without_b, true);
                    check_pos_bit(mask_b, a_without_b, false);

                    for (int k = 0; k < n; ++k) {
                        if (a_without_b[k] && s[mask_b | (1 << k)] != -1) {
                            check3 = true;
                            break;
                        }
                    }
                    if (!check3) {
                        std::cout << "NO";
                        return;
                    }
                }
            }
        }
    }
    std::cout << "YES";

}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    init();
    solve();
    return 0;
}