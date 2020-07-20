#include <iostream>
#include <vector>

using std::vector;

void solve() {
    std::string p, s;
    std::cin >> p >> s;
    size_t p_size = p.size(), s_size = s.size();
    s = p + '#' + s;
    size_t n = s.size();
    vector<int> pref(n);
    pref[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pref[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pref[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pref[i] = j;
    }
    vector<int> ans;
    for (int i = p_size + 1; i < n; i++) {
        if (pref[i] == p_size) {
            ans.push_back(i - 2 * p_size);
        }
    }
    std::cout << ans.size() << "\n";
    for (int out : ans) {
        std::cout << out + 1 << " ";
    }
}

int main() {
    solve();
    return 0;
}