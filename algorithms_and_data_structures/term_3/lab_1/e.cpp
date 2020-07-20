#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
vector<bool> used;
vector<int> t_in;
vector<int> d;
std::vector<int> out;
vector<vector<std::pair<int, int> > > G;
int timer = 1;
int max_color = 0;

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
    out.resize(m + 1);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        G[u].emplace_back(v, i + 1);
        G[v].emplace_back(u, i + 1);

    }
}

bool dfs(int v, int parent) {
    d[v] = t_in[v] = timer++;
    for (auto u : G[v]) {
        if (u.first == parent)
            continue;
        if (t_in[u.first] != 0)
            d[v] = min(d[v], t_in[u.first]);
        else {
            dfs(u.first, v);
            d[v] = min(d[v], d[u.first]);
        }
    }
}


void set_color(int u, int v, int color) {
    for (auto t : G[v]) {
        if (t.first == u)
            out[t.second] = color;
    }
}
void dfs2 (int v, int color, int parent) {
    used[v] = true;
    for (auto u : G[v]) {
        if (u.first == parent)
            continue;
        if (!used[u.first]) {
            if (d[u.first] >= t_in[v]) {
                int next_color =  ++max_color;
                set_color(u.first, v, next_color);
                dfs2(u.first, next_color, v);
            } else {
                set_color(u.first, v, color);
                dfs2(u.first, color, v);
            }
        }
        else if (t_in[u.first] < t_in[v])
            set_color(u.first, v, color);
    }
}

void ans() {
    for (int u = 1; u < G.size(); u++)
        if (t_in[u] == 0)
            dfs(u, -1);
    for (int u = 1; u < G.size(); u++) {
        if (!used[u]) {
            dfs2(u, max_color, -1);
        }
    }
    std::cout << max_color << "\n";
    for (int i = 1; i < out.size(); i++) {
        std::cout << out[i] << " ";
    }
}

int main() {
    init();
    ans();
    return 0;
}