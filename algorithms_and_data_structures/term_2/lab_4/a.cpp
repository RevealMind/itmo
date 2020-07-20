#include<iostream>
#include <vector>
#include <algorithm>

int main() {
    freopen("cobbler.in", "r", stdin);
    freopen("cobbler.out", "w", stdout);
    int k, n, count = 0;
    std::cin >> k >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::sort(arr.begin(), arr.end());
    for (auto i : arr) {
        if (k - i < 0)
            break;
        count++;
        k -= i;
    }
    std::cout << count;
}