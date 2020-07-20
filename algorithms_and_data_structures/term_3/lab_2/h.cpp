#include <iostream>
#include <vector>
#include <cstdio>

using std::vector;
using std::pair;
using std::size_t;

vector<vector<pair<int, long long> > > G;
vector<long long> d;
vector<int> _set;
vector<bool> used;

void init();

void solve();

void init() {
    size_t n, m;
    int a, x, y;
    std::cin >> n >> m;
    d.resize(n);
    G.resize(n);
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> a >> x >> y;
        a--; x--; y--;
        G[x].emplace_back(a, y);
        G[y].emplace_back(a, x);
    }
}

void solve() {
    size_t n = G.size();
    for (int i = 0; i < n; i++)
        _set.push_back(i);
    while(!_set.empty()) {
        int cur = _set.back();
        _set.pop_back();
        used[cur] = true;
        for (auto tmp : G[cur]) {
            int to = tmp.first;
            long long weight = tmp.second;
            if (d[cur] + d[weight] < d[to]) {
                d[to] = d[cur] + d[weight];
                if (used[to]) {
                    used[to] = false;
                    _set.push_back(to);
                }
            }
        }
    }
    std::cout << d[0];

}

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("dwarf.in", "r", stdin);
    freopen("dwarf.out", "w", stdout);
    init();
    solve();
    return 0;
}