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
int s, t;            // vertices of source and stock
std::vector<Edge> e; // e[i] - edge, e[i ^ 1] - rev e[i]
std::vector<std::vector<int> > g;
std::vector<int> ptr;
std::vector<int> dist;

//
//

// FUNCTION declaration

void solve();
void init();
void addEdge(int const, int const, int const);

int dinic();
bool bfs();
int dfs(int const, int const);

void out();
void outHelper();
void resetFlow();
void dfs(int const, std::vector<int> &);

//
//


// FUNCTION definition

void solve() {
    init();
    out();
}

void init() {
    std::cin >> n >> m >> s >> t;
    s--; t--;

    g.resize(n);
    ptr.resize(n);
    dist.resize(n);

    for (int from, to, i = 0; i < m; i++) {
        std::cin >> from >> to;
        if (from != to)
            addEdge(--from, --to, 1);
    }
}

void addEdge(int const a, int const b, int const c) {
    g[a].push_back((int) e.size());
    e.emplace_back(a, b, c, 0);
    g[b].push_back((int) e.size());
    e.emplace_back(b, a, 0, 0);
}


int dinic() {
    int total = 0;
    while (bfs()) {
        memset(ptr.data(), 0, n * sizeof ptr[0]);
        int pushed = dfs(s, INF);
        if (pushed) {
            total += pushed;
        }
    }
    return total;
}

bool bfs(){
    memset(dist.data(), -1, dist.size() * sizeof dist[0]);
    std::queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty() && dist[t] == -1) {
        int cur = q.front(); q.pop();
        for (int i = 0; i < (int) g[cur].size(); ++i) {
            int id = g[cur][i],
                to = e[id].b;

            if (!e[id].del && dist[to] == -1 && e[id].f < e[id].c) {
                dist[to] = dist[cur] + 1;
                q.push(to);
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int const cur, int const flow) {
    if (flow == 0) {
        return 0;
    }
    if (cur == t) {
        return flow;
    }
    for (; ptr[cur] < (int) g[cur].size(); ++ptr[cur]) {
        int id = g[cur][ptr[cur]],
            to = e[id].b;
        if (e[id].del || dist[to] != dist[cur] + 1) {
            continue;
        }
        int delta = dfs(to, std::min (flow, e[id].c - e[id].f));
        if (delta) {
            e[id].f += delta;
            e[id ^ 1].f -= delta;
            return delta;
        }
    }
    return 0;
}

void out() {
    if (dinic() < 2) {
        std::cout << "NO";
    } else {
        std::cout << "YES\n";
        outHelper();
        resetFlow();
        dinic();
        outHelper();
    }
}

void resetFlow() {
    for (int i = 0; i < e.size(); i += 2) {
        if (e[i].del) {
            e[i ^ 1].del = true;
        }
        e[i].f = 0;
        e[i ^ 1].f = 0;
    }
}

void outHelper() {
    std::vector<int> out1;
    dfs(s, out1);
    out1.push_back(t);
    for (int o : out1) {
        std::cout << o + 1 << " ";
    }
    std::cout << "\n";
}

void dfs(int const cur, std::vector<int> &list) {
    if (cur == t) {
        return;
    }
    list.push_back(cur);
    for (int i = 0; i < g[cur].size(); ++i) {
        int id = g[cur][i],
            to = e[id].b;
        if (!e[id].del && e[id].f == 1) {
            e[id].del = true;
            dfs(to, list);
            return;
        }
    }
}

//
//

int main() {
    solve();
}
