#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;
using std::size_t;

vector<vector<pair<int, long long> > > G;
vector<long long> d;
vector<int> p;

long long const INF = 5000000000000000000LL;
long long const NEGINF = -5000000000000000000LL;

int start;

//######################################################
                                                     //@
void init();                                         //@
                                                     //@
void solve();                                        //@
                                                     //@
long long max(long long a, long long b);             //@
                                                     //@
void dfs(int cur, vector<bool> &used);               //@
                                                     //@
//######################################################

void init() {
    size_t n, m, from, to;
    long long weight;
    std::cin >> n >> m >> start;
    start--;
    G.resize(n);
    p.resize(n);
    d.resize(n, INF);
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> weight;
        from--;
        to--;
        G[from].emplace_back(to, weight);
    }
}

void solve() {
    d[start] = 0;
    size_t n = G.size();
    for (int k = 0; k < n - 1; k++) {
        for (int from = 0; from < n; from++) {
            for (auto tmp : G[from]) {
                int to = tmp.first;
                long long weight = tmp.second;
                if (d[from] < INF && d[to] > d[from] + weight) {
                    d[to] = max(NEGINF, d[from] + weight);
                }
            }
        }
    }

    vector<bool> isChange(n, false);
    for (int from = 0; from < n; from++) {
        for (auto tmp : G[from]) {
            int to = tmp.first;
            long long weight = tmp.second;
            if (d[from] < INF && d[to] > d[from] + weight) {
                isChange[to] = true;
            }
        }
    }

    vector<bool> isNegCycle(n, false);
    for (int i = 0; i < n; i++) {
        if (isChange[i]) {
            dfs(i, isNegCycle);
        }
    }

    for (int i = 0; i < d.size(); i++) {
        if (isNegCycle[i])
            std::cout << "-";
        else if (d[i] == INF)
            std::cout << "*";
        else
            std::cout << d[i];
        std::cout << "\n";
    }

}

long long max(long long a, long long b) {
    return a > b ? a : b;
}

void dfs(int cur, vector<bool> &used) {
    used[cur] = true;
    for (auto tmp : G[cur]) {
        int to = tmp.first;
        if (!used[to])
            dfs(to, used);
    }
}

int main() {
    init();
    solve();
    return 0;
}