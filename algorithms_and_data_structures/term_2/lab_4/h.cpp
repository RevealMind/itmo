#include <iostream>
#include <vector>
std::vector<std::string> arr;
void gen(int n, bool last_is_one, std::string str) {
    if (n == 0) {
        arr.push_back(str);
        return;
    }
    if (last_is_one) {
        gen(n - 1, false, str + "0");
    } else {
        gen(n - 1, false, str + "0");
        gen(n - 1, true, str + "1");
    }
}
int main() {
    freopen("vectors2.in", "r", stdin);
    freopen("vectors2.out", "w", stdout);
    int n;
    std::cin >> n;
    gen(n, false, "");
    std::cout << arr.size() << "\n";
    for (auto i : arr) {
        std::cout << i << "\n";
    }
}