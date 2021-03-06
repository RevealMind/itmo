#include <iostream>
#include <vector>

using std::vector;

void solve() {
    std::string s;
    std::cin >> s;
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
    for (int out : pref) {
        std::cout << out << " ";
    }
}

int main() {
    solve();
    return 0;
}