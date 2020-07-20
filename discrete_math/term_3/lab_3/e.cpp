#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;

std::string file_name = "cycles";

vector<pair<int, int> > weights;
vector<bool> s;
queue<int> q;
int n, m;

void init() {
    std::cin >> n >> m;

    for (int i = 0, weight; i < n; ++i) {
        std::cin >> weight;
        weights.emplace_back(weight, i);
    }

    std::sort(weights.begin(), weights.end(), std::greater<pair<int, int> >());

    s.resize((1 << n), false);

    for (int i = 0, k; i < m; ++i) {
        int cycle = 0;
        std::cin >> k;
        for (int j = 0, shift; j < k; ++j) {
            std::cin >> shift;
            cycle |= (1 << (shift - 1));
        }
        s[cycle] = true;
        q.push(cycle);
    }
}

void solve() {
    while (!q.empty()) {
        int cycle = q.front();
        q.pop();
        for (int i = 0; i < n; ++i) {
            int tmp = (cycle | (1 << i));
            if ((cycle & (1 << i)) == 0 && !s[tmp]) {
                s[tmp] = true;
                q.push(tmp);
            }
        }
    }

    int ans = 0;
    int base = 0;

    for (int i = 0; i < n; ++i) {
        if (!s[base | (1 << weights[i].second)]) {
            base |=  (1 << weights[i].second);
            ans += weights[i].first;
        }
    }

    std::cout << ans;
}

int main() {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
    std::ios_base::sync_with_stdio(false);
    init();
    solve();
    return 0;
}