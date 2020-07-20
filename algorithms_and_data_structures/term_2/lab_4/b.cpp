#include<iostream>
#include <vector>
#include <algorithm>

int main() {
    freopen("request.in", "r", stdin);
    freopen("request.out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int> > arr;
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        arr.push_back(std::make_pair(l, r));
    }
    std::sort(arr.begin(), arr.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.second < b.second;
    });
    int count = 1;
    int pre_r = arr[0].second;
    for (int i = 1; i < n; i++) {
        if (pre_r <= arr[i].first){
            count++;
            pre_r = arr[i].second;
        }
    }
    std::cout << count;
}