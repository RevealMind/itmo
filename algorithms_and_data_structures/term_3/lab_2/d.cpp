#include <iostream>
#include <vector>
#include <algorithm>
#include <afxres.h>

using std::vector;
using std::pair;
using std::size_t;

vector<vector<pair<int, int> > > G;
vector<vector<int> > d;

int const INF = 1000000000;

int start, k;

void init();

void solve();

int max(int a, int b);

void init() {
    size_t n, m;
    int from, to, weight;

    std::cin >> n >> m >> k >> start;
    start--;
    G.resize(n);
    d.resize(k + 1, vector<int>(n, INF));

    for (size_t i = 0; i < m; i++) {
        std::cin >> from >> to >> weight;
        from--;
        to--;
        G[from].emplace_back(to, weight);
    }
}

void solve() {
    d[0][start] = 0;
    size_t n = G.size();
    for (int i = 0; i < k; i++) {
        for (int from = 0; from < n; from++) {
            for (auto tmp : G[from]) {
                int to = tmp.first;
                int weight = tmp.second;
                if (d[i][from] < INF && d[i + 1][to] > d[i][from] + weight) {
                    d[i + 1][to] = d[i][from] + weight;
                }
            }
        }
    }
    for (int i : d[k]) {
        if (i == INF)
            std::cout << -1 << "\n";
        else
            std::cout << i << "\n";
    }
}


int main() {
    init();
    solve();
    return 0;
}
