#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
vector<bool> used;
vector<int> t_in;
vector<int> d;
vector<int> out;
vector<vector<int> > G, S;
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
    S.resize(n + 1);
    out.resize(n + 1);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

bool check2(int v, int u) {
    int k = 0;
    for (int t : G[v])
        if (t == u)
            k++;
    return k <= 1;
}

bool dfs(int v, int parent) {
    used[v] = true;
    d[v] = t_in[v] = timer++;
    for (int u : G[v]) {
        if (u == parent)
            continue;
        if (used[u])
            d[v] = min(d[v], t_in[u]);
        else {
            dfs(u, v);
            d[v] = min(d[v], d[u]);
            if (d[u] > t_in[v] && check2(u, v)) {
                S[v].push_back(u);
                S[u].push_back(v);
            }
        }
    }
}

bool check(int v, int u) {
    for (int t : S[v]) {
        if (u == t)
            return false;
    }
    return true;
}
bool dfs2(int v, int k) {
    used[v] = false;
    out[v] = k;
    for (auto u : G[v]) {
        if (used[u] && check(v, u))
            dfs2(u, k);
    }
}

void ans() {
    int k = 1;
    for (int u = 1; u < G.size(); u++)
        if (!used[u])
            dfs(u, -1);
    for (int i=0; i< G.size(); ++i)
        if (used[i]) {
            dfs2(i, k);
            k++;
        }
    std::cout << k - 1 << "\n";
    for (int i = 1; i < out.size(); i++)
        std::cout << out[i] << " ";
}

int main() {
    init();
    ans();
    return 0;
}