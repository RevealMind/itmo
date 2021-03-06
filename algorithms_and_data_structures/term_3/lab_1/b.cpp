#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
vector<bool> used;
vector<int> t_in;
vector<int> d;
vector<int> out;
vector<vector<std::pair<int, int> > > G, E;
int timer = 0;

int min(int a, int b) {
    return a < b ? a : b;
}

void init() {
    int n(1);
    int m(0);
    int u(0);
    int v(0);
    std::cin >> n >> m;
    used.resize(n + 1, false);
    t_in.resize(n + 1, 0);
    d.resize(n + 1, 0);
    G.resize(n + 1);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        G[u].emplace_back(v, i + 1);
        G[v].emplace_back(u, i + 1);

    }
}

bool dfs(int v, int parent) {
    used[v] = true;
    d[v] = t_in[v] = timer++;
    for (auto u : G[v]) {
        if (u.first == parent)
            continue;
        if (used[u.first])
            d[v] = min(d[v], t_in[u.first]);
        else {
            dfs(u.first, v);
            d[v] = min(d[v], d[u.first]);
            if (d[u.first] > t_in[v])
                out.push_back(u.second);
        }
    }
}


void ans() {
    for (int u = 1; u < G.size(); u++)
        if (!used[u])
            dfs(u, -1);
    std::sort(out.begin(), out.end());
    std::cout << out.size() << "\n";
    for (int v : out)
        std::cout << v << " ";
}

int main() {
    init();
    ans();
    return 0;
}