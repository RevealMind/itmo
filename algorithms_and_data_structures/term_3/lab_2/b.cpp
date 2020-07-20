#include <iostream>
#include <vector>
#include <set>

using std::vector;
using std::pair;
using std::set;

vector<vector<pair<int, long long> > > G;
vector<long long> d;
vector<bool> used;
long long int INF = 9000000000;

void init() {
    size_t n, m;
    int from, to, weight;
    std::cin >> n >> m;
    G.resize(n);
    d.resize(n, INF);
    used.resize(n, false);
    d[0] = 0;
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> weight;
        from --;
        to --;
        G[from].emplace_back(to, weight);
        G[to].emplace_back(from, weight);
    }
}

void algo() {
    set<pair<int, long> > s;
    s.insert(std::make_pair(0, d[0]));
    while (!s.empty()) {
        int from = s.begin()->first;
        s.erase(s.begin());
        for (auto to : G[from]) {
            if (d[to.first] > d[from] + to.second) {
                s.erase(std::make_pair(to.first, d[to.first]));
                d[to.first] = d[from] + to.second;
                s.insert(std::make_pair(to.first, d[to.first]));
            }
        }
    }
}

void print() {
    for (auto out : d) {
        std::cout << out << " ";
    }
}

void solve() {
    init();
    algo();
    print();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    solve();
    return 0;
}