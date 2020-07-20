#include <iostream>
#include <vector>
#include <cstdio>
#include <limits>
#include <set>

using std::vector;
using std::set;

vector<vector<int> > g;
int n;
vector<int> res(1000000 + 10), col(1000000 + 10);
vector<set<int> > s(1000000 + 10);

void _union(set<int> &a, set<int> &b) {
    if (a.size() < b.size()) a.swap(b);
    for(set<int>::iterator p = b.begin(); p != b.end(); p++)
        a.insert(*p);
    b.clear();
}

void dfs(int v, int p = 0) {
    s[v].insert(col[v]);
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        //if (to != p) {
            dfs(to, v);
        //}
        _union(s[v], s[to]);
    }
    res[v] = s[v].size();
}

void init() {
    int v, color;
    scanf("%d", &n);
    g.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &v, &color);
        g[v].push_back(i);
        col[i] = color;
    }
}

void solve() {
    printf("%d",res[1]);
    for(int i = 2; i <= n; i++)
        printf(" %d",res[i]);
    printf("\n");
}

void preprocessing() {
    dfs(0);
}

void _start() {
    init();
    preprocessing();
    solve();
}

int main() {
    _start();
}