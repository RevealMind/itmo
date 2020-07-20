#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <set>

using std::vector;
using std::pair;
using std::sqrt;
using std::set;

vector<vector<pair<int, int> > > g;
const int MAX = 1000000000;

void init() {
    int n, m;
    int u, v, w;
    scanf("%d %d", &n, &m);
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &v, &u, &w);
        if (u != v) {
            g[v - 1].push_back(std::make_pair(u - 1, w));
            g[u - 1].push_back(std::make_pair(v - 1, w));
        }
    }

}

void ans() {
    init();

    vector<bool> used(g.size(), false);
    vector<int> min(g.size(), MAX);
    vector<int> end(g.size(), -1);
    set<pair<int, int> > q;

    min[0] = 0;
    long long int ans = 0;
    q.insert(std::make_pair(0, 0));

    for (int i = 0; i < g.size(); i++) {
        int v = q.begin()->second;
        q.erase(q.begin());
        if (end[v] != -1) {
            used[end[v]] = true;
        }
        for (int j = 0; j < g[v].size(); j++) {
            if (!used[g[v][j].first] && g[v][j].second < min[g[v][j].first]) {
                q.erase(std::make_pair(min[g[v][j].first], g[v][j].first));
                min[g[v][j].first] = g[v][j].second;
                end[g[v][j].first] = v;
                q.insert(std::make_pair(min[g[v][j].first], g[v][j].first));
            }
        }
    }

    for (long long s : min)
        if (s != MAX)
            ans += s;

    printf("%lld", ans);
}

int main() {
    ans();
    return 0;
}

