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
    int k = n - pref[n - 1];
    if (n % k == 0) {
        std::cout << k;
    } else {
        std::cout << n;
    }
}

int main() {
    solve();
    return 0;
}