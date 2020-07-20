#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
using std::pair;
using std::set;
using std::size_t;

vector<vector<pair<int, long long> > > G;
vector<long long> da, db;
set<pair<int, long long> > _set;

long long const INF = 200000000000000LL;

int a, b, c;

void init();

void solve();

long long min(long long a, long long b);

void find_cost_of_min_path(vector<long long> &d, int start);

void init() {
    size_t n, m;
    int from, to;
    long long weight;

    std::cin >> n >> m;
    G.resize(n);
    da.assign(n, INF);
    db.assign(n, INF);
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> weight;
        from--;
        to--;
        G[from].emplace_back(to, weight);
        G[to].emplace_back(from, weight);
    }
    std::cin >> a >> b >> c;
    a--;
    b--;
    c--;
}

void solve() {
    da[a] = 0;
    db[b] = 0;
    size_t n = G.size();
    find_cost_of_min_path(da, a);
    find_cost_of_min_path(db, b);
    if (da[b] == INF || da[c] == INF || db[a] == INF || db[c] == INF) {
        std::cout << -1;
        return;
    }

    long long tmp = min(da[b] + da[c], da[c] + db[c]);
    long long _min = min(tmp, db[a] + db[c]);
    std::cout << _min;

}

long long min(long long a, long long b) {
    return a < b ? a : b;
}

void find_cost_of_min_path(vector<long long> &d, int start){
    _set.emplace(std::make_pair(start, 0));
    while (!_set.empty()) {
        pair<int, int> cur = *_set.begin();
        _set.erase(_set.begin());
        for (auto tmp : G[cur.first]) {
            int to = tmp.first;
            long long weight = tmp.second;
            if (d[cur.first] + weight < d[to]) {
                _set.erase(std::make_pair(to, d[to]));
                d[to] = d[cur.first] + weight;
                _set.emplace(std::make_pair(to, d[to]));
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    init();
    solve();
    return 0;
}