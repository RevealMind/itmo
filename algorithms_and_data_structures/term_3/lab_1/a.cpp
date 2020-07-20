#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
vector<bool> used;
vector<int> color;
vector<vector<int> > G;
vector<int> sort;

void init() {
    int n(1);
    int m(0);
    int u(0);
    int v(0);
    std::cin >> n >> m;
    used.resize(n + 1, false);
    color.resize(n + 1, 0);
    G.resize(n + 1);
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
    }
}

bool dfs(int v) {
    if (color[v] == 1)
        return true;
    if (color[v] == 2)
        return false;
    color[v] = 1;
    for (int u : G[v]) {
        if (dfs(u))
            return true;
    }
    color[v] = 2;
    sort.push_back(v);
    return false;
}

bool top_sort() {
    for (int u = 1; u < G.size(); u++)
        if (dfs(u))
            return false;
    std::reverse(sort.begin(), sort.end());
    return true;
}

void ans() {
    if (!top_sort())
        std::cout << -1;
    else
        for (int out : sort)
            std::cout << out << " ";
}
int main() {
    init();
    ans();
    return 0;
}