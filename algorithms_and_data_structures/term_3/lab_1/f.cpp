#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::vector;
using std::set;
using std::pair;

vector<bool> used;
vector<int> sort;
vector<int> color;
vector<vector<int> > G, T;
set<pair<int, int> > out;

void init() {
    int n(1);
    int m(0);
    int u(0);
    int v(0);
    std::cin >> n >> m;
    used.resize(n + 1, false);
    G.resize(n + 1);
    T.resize(n + 1);
    color.resize(n + 1, 0);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
        T[v].push_back(u);
    }
}

void dfs(int v) {
    used[v] = true;
    for (int u : G[v]) {
        if (!used[u])
            dfs(u);
    }
    sort.push_back(v);
}

void _dfs(int v, int cur_color) {
    color[v] = cur_color;
    for (int u : T[v])
        if (color[u] == 0)
            _dfs(u, cur_color);
}

void ans() {
    for (int i = 1; i < G.size(); i++)
        if (!used[i])
            dfs(i);
    int cur_color = 1;
    for (int i = 1; i < G.size(); i++) {
        int v = sort.back();
        sort.pop_back();
        if (color[v] == 0)
         _dfs(v, cur_color++);
    }
    for (int v = 1; v < G.size(); v++)
        for (int u : G[v])
            if (color[v] != color[u])
                out.insert(std::make_pair(color[v], color[u]));
    std::cout << out.size();

}

int main() {
    init();
    ans();
    return 0;
}