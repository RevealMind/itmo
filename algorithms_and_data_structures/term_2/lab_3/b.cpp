#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <limits>

using std::vector;
using std::map;
using std::pair;

map<pair<int, int>, int> e;
vector<vector<int> > g, up, w;
int m, n, l;
vector<int> in, out, d;

int depth = 0, timer = 0;

void dfs(int v, int p = 0) {
    in[v] = ++timer;
    up[v][0] = p;
    w[v][0] = e[{v, p}];
    d[v] = depth;
    for (int i = 1; i <= l; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
        w[v][i] = std::min(w[v][i - 1], w[up[v][i - 1]][i - 1]);
    }
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != p) {
            ++depth;
            dfs(to, v);
            --depth;
        }
    }
    out[v] = ++timer;
}

bool upper(int a, int b) {
    return in[a] <= in[b] && out[a] >= out[b];
}

int findLCA(int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    for (int i = l; i >= 0; i--) {
        if (!upper(up[a][i], b))
            a = up[a][i];
    }
    return up[a][0];
}

int go(int v, int u) {
    int ans = std::numeric_limits<int>::max();
    for (int i = l; i >= 0; i--) {
        if ((1 << i) <= d[v] - d[u]) {
            ans = std::min(ans, w[v][i]);
            v = up[v][i];
        }
    }
    return ans;
}

void init() {
    int v, weight;
    scanf("%d", &n);
    g.resize(n);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &v, &weight);
        --v;
        g[v].push_back(i);
        e[{v, i}] = weight;
        e[{i, v}] = weight;
    }
}

void solve() {
    int u, v, x;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        x = findLCA(--u, --v);
        printf("%d\n", std::min(go(u, x), go(v, x)));
    }
}

void preprocessing() {
    l = 1;
    while ((1 << l) <= n) l++;
    in.resize(n);
    out.resize(n);
    d.resize(n);
    up.resize(n, vector<int>(l + 1));
    w.resize(n, vector<int>(l + 1));
    dfs(0);
}

void _start() {

    init();
    preprocessing();
    solve();
}

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    _start();
}