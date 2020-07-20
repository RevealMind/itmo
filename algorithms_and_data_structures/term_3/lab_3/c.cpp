#include <iostream>
#include <vector>

using std::vector;

int min(int a, int b) {
    return a < b ? a : b;
}

void solve() {
    std::string s;
    std::cin >> s;
    size_t n = s.size();
    vector<int> z_func(n);
    z_func[0] = 0;
    for (int i = 1, left = 0, right = 0; i < n; i++) {
        if (i <= right) {
            z_func[i] = min(right - i + 1, z_func[i - left]);
        }
        while (i + z_func[i] < n && s[z_func[i]] == s[i + z_func[i]]) {
            ++z_func[i];
        }
        if (i + z_func[i] - 1 > right){
            left = i;
            right = i + z_func[i] - 1;
        }
    }
    for (int i = 1; i < n; i++) {
        std::cout << z_func[i] << " ";
    }
}

int main() {
    solve();
    return 0;
}