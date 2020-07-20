#include <iostream>
#include <deque>
#include <vector>
#include <cstdio>
#include <algorithm>

using std::deque;
using std::vector;
using std::string;

vector<vector<bool> > G;
deque<int> vertex;

void init() {
    int n;
    string tmp;
    std::cin >> n;
    G.resize(n, vector<bool>(n, false));
    vertex.push_back(0);
    for (int i = 1; i < n; i++) {
        vertex.push_back(i);
        std::cin >> tmp;
        for (int j = 0; j < i; j++)
            G[i][j] = G[j][i] = tmp[j] - '0';
    }
}

void solve() {
    for (int k = 0; k < (G.size() * (G.size() - 1)); k++) {
        int u = vertex.at(0);
        int v = vertex.at(1);
        if (G[u][v] == 0) {
            int i = 2;
            while (!(G[u][vertex.at(i)] == 1 && G[v][vertex.at(i + 1)] == 1))
                i++;
            std::reverse(vertex.begin() + 1, vertex.begin() + i + 1);
        }
        vertex.push_back(u);
        vertex.pop_front();
    }

    for (int v : vertex)
        std::cout << v + 1<< " ";
}

int main() {
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);
    init();
    solve();
    return 0;
}