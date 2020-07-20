#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <deque>
#include <cstdio>

std::deque<std::pair<int, int> > seq, ans_left, ans_right;
int sum = 0;

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    int n, data;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        seq.push_back(std::make_pair(data, i + 1));
        sum += data;
    }
    if (sum % 2 == 1) {
        std::cout << "-1";
        return 0;
    }
    sum /= 2;
    std::sort(seq.begin(), seq.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first > b.first;
    });
    int sum_left = 0, sum_right = 0;
    for (auto val : seq) {
        if (sum_left < sum_right) {
            ans_left.push_back(val);
            sum_left += val.first;
        } else {
            ans_right.push_back(val);
            sum_right += val.first;
        }
    }
    std::sort(ans_left.begin(), ans_left.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    });

    if (sum_left == sum) {
        std::cout << ans_left.size() << "\n";
        for (auto ans : ans_left) {
            std::cout << ans.second << " ";
        }
    } else
        std::cout << "-1";
    return 0;
}