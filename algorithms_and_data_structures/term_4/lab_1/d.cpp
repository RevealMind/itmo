#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>

struct Edge {
    int a;      // start of the edge
    int b;      // end of the edge
    int c;      // max flow
    int f;      // current flow (f <= c)

    bool del;  // is edge was del

    Edge (int a, int b, int c, int f) : a(a), b(b), c(c), f(f), del(false) {}
};

// GLOBAL variables
int const INF = 1000000000;

int n, m;            // number of vertices and edges
std::vector<int> matching;
std::vector<std::vector<int> > g;
std::vector<bool> used;
int size = 0;

//
//

// FUNCTION declaration

void solve();
void init();
void out();

bool dfs(int const);

//
//


// FUNCTION definition

void solve() {
    init();
    out();
}

void init() {
    std::cin >> n >> m;

    matching.resize(m, -1);
    g.resize(n);

    for (int cur, i = 0; i < n; ++i) {
        std::cin >> cur;
        while (cur != 0) {
            g[i].push_back(cur - 1);
            std::cin >> cur;
        }
    }

    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        size += dfs(i) ? 1 : 0;
    }
}

void out() {
    std::cout << size << "\n";
    for (int i = 0; i < m; ++i) {
        if (matching[i] != -1) {
            std::cout << matching[i] + 1 << " " << i + 1 << "\n";
        }
    }
}

bool dfs(int const cur) {
    if (used[cur]) {
        return false;
    }
    used[cur] = true;
    for (int i = 0; i < g[cur].size(); ++i) {
        int to = g[cur][i];
        if (matching[to] == -1 || dfs(matching[to])) {
            matching[to] = cur;
            return true;
        }
    }
    return false;
}

//
//

int main() {
    solve();
}
