#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using std::vector;
int used[1005];
vector<vector<int> > G;
vector<vector<bool> > _G;

void init() {
    int n(1);
    int weight(0);
    scanf("%d", &n);
    G.resize(n, vector<int>(n));
    _G.resize(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &weight);
            G[i][j] = weight;
        }
    }
}

void dfs(int v, bool is_reverse) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if ((is_reverse ? _G[i][v] : _G[v][i]) && !used[i])
            dfs(i, is_reverse);
    }
}

bool check() {
    for (int i = 0; i < G.size(); i++)
        if (!used[i])
            return false;
    return true;
}

void ans() {
    int left = 0;
    int right = 2000000000;
    int middle;
    int flag;
    while (left < right) {
        middle = (left + right) / 2;

        for (int i = 0; i < G.size(); ++i)
            for (int j = 0; j < G[i].size(); ++j)
                _G[i][j] = G[i][j] <= middle;
        memset(used,0,sizeof(used));
        dfs(0, false);
        flag = 1;
        if (check()) {
            memset(used,0,sizeof(used));
            dfs(0, true);
            if (!check()) flag = 0;
        } else
            flag = 0;

        if (flag) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    std::cout << left;
}

int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    init();
    ans();
    return 0;
}