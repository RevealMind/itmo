#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
using std::set;

struct task {
    int time;
    int cost;

    task(int time, int cost) : time(time), cost(cost) {}
};

vector<task> tasks;
set<int> is_free;

long long ans = 0;

int max(const int a, const int b) {
    return a > b ? a : b;
}

void init() {
    size_t n;
    int time, cost, max_time = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> time >> cost;
        tasks.emplace_back(time, cost);
    }
    std::sort(tasks.begin(), tasks.end(), [](const task &a, const task &b) { return a.cost > b.cost; });
    for (int i = 0; i < n; i++) {
        is_free.insert(i);
    }
    int last = n - 1;
    for (int i = 0; i < n; i++) {
        if (tasks[i].time >= n)
            continue;
        int deadline = tasks[i].time;
        if (is_free.lower_bound(deadline) == is_free.end()) {
            is_free.insert(deadline);
            auto it = --is_free.lower_bound(deadline);
            if (*it >= deadline) {
                ans += tasks[i].cost;
            } else
                is_free.erase(--is_free.lower_bound(deadline));
            is_free.erase(deadline);
        } else {
            auto it = --is_free.lower_bound(deadline);
            if (*it >= deadline) {
                ans += tasks[i].cost;
            } else
            is_free.erase(--is_free.lower_bound(deadline));
        }
    }
    std::cout << ans;
}

int main() {
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    init();
    return 0;
}