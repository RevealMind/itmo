#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using std::map;
using std::vector;
using std::string;

map<string, int> friends;
map<int, string> _friends;

vector<vector<int> > G, T;
vector<bool> used;
vector<int> sort, comp;
vector<string> out;

void set_edge(string const&  _from, string const&  _to) {
    int from = friends[_from.substr(1)];
    int to = friends[_to.substr(1)];
    if (_from[0] == '-') {
        if (_to[0] == '-') {
            G[from ^ 1].push_back(to ^ 1);
            G[to].push_back(from);
            T[to ^ 1].push_back(from ^ 1);
            T[from].push_back(to);
        }  else {
            G[from ^ 1].push_back(to);
            G[to ^ 1].push_back(from);
            T[to].push_back(from ^ 1);
            T[from].push_back(to ^ 1);
        }
    } else {
        if (_to[0] == '-') {
            G[from].push_back(to ^ 1);
            G[to].push_back(from ^ 1);
            T[to ^ 1].push_back(from);
            T[from ^ 1].push_back(to);
        }  else {
            G[from].push_back(to);
            G[to ^ 1].push_back(from ^ 1);
            T[to].push_back(from);
            T[from ^ 1].push_back(to ^ 1);
        }
    }
}

void init() {
    int n;
    int m;
    string name;
    string from, tmp, to;
    std::cin >> n >> m;
    G.resize(n * 2);
    T.resize(n * 2);
    used.resize(n * 2, false);
    comp.resize(n * 2, -1);
    for (int i = 0; i < n; i++) {
        std::cin >> name;
        friends[name] = 2 * i;
        _friends[2 * i] = name;
    }
    for (int i = 0; i < m; i++) {
        std::cin >> from >> tmp >> to;
        set_edge(from, to);
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

void _dfs(int v, int color) {
    comp[v] = color;
    for (int u : T[v])
        if (comp[u] == -1)
            _dfs(u, color);
}

void ans() {
    for (int v = 0; v < G.size(); v++)
        if (!used[v])
            dfs(v);
    std::reverse(sort.begin(), sort.end());
    for (int v = 0, color = 0; v < sort.size(); v++)
        if (comp[sort[v]] == -1)
            _dfs(sort[v], color++);
    for (int v = 0; v < comp.size(); v++)
        if (comp[v] == comp[v ^ 1]) {
            std::cout << -1;
            return;
        }
    for (int v = 0; v < comp.size(); v += 2) {
        if (comp[v] > comp[v ^ 1])
            out.push_back(_friends[v]);
    }
    std::cout << out.size() << "\n";
    for (const string &name : out)
        std::cout << name << "\n";
}
int main() {
    //freopen("test.in", "r", stdin);
    init();
    ans();
    return 0;
}