#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>


struct apple {
    int a, b, ind;
    apple(int a, int b, int ind): a(a), b(b), ind(ind){};
};
std::vector<apple> arr, ans;
int main() {
    freopen("apples.in", "r", stdin);
    freopen("apples.out", "w", stdout);
    int n, s, a, b;
    std::cin >> n >> s;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        arr.push_back(apple(a, b, i + 1));
    }
    std::sort(arr.begin(), arr.end(), [](apple a, apple b) {
        return a.a < b.a;
    });

    for (auto _apple : arr) {
        if (_apple.b - _apple.a >= 0) {
            ans.push_back(_apple);
            s += _apple.b - _apple.a;
        }
    }
    std::sort(arr.begin(), arr.end(), [](apple a, apple b) {
        return a.b > b.b;
    });
    for (auto _apple : arr) {
        if (_apple.b - _apple.a < 0 && s - _apple.a > 0) {
            ans.push_back(_apple);
            s -= _apple.b - _apple.a;
        }
    }
    if (ans.size() == n) {
        for (auto _apple : ans) {
            std::cout << _apple.ind << " ";
        }
    } else {
        std::cout << "-1";
    }
};