#include <iostream>
#include <vector>

using std::vector;
vector<vector<int> > g, up;
int l, timer = 0;
vector<int> in, out;

void dfs(int v, int p = 0) {
    in[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to != p) {
                dfs(to, v);
        }
    }
    out[v] = ++timer;
}

bool upper(int a, int b) {
    return in[a] <= in[b] && out[a] >= out[b];
}

int findLCA(int a, int b) {
    if (upper(a,b)) return a;
    if (upper(b,a)) return b;
    for (int i = l; i >= 0; i--) {
        if (!upper(up[a][i], b))
            a = up[a][i];
    }
    return up[a][0];
}
int main() {
    int n;
    scanf("%d", &n);
    int pos;
    l = 1;
    while ((1 << l) <= n) l++;
    g.resize(n);
    up.resize(n, vector<int> (l + 1, 100));
    in.resize(n);
    out.resize(n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &pos);
        g[pos - 1].push_back(i);
    }
    dfs(0);
    int m, u, v;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        printf("%d\n", findLCA(u - 1, v - 1) + 1);
    }
}