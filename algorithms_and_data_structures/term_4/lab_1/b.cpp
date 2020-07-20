#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Edge {
  int a, b;
  int64_t c, f;
  Edge(int a, int b, int64_t  c, int64_t  f) : a(a), b(b), c(c), f(f) {}
  void print() {
      printf("Start: %d\n", a);
      printf("End: %d\n", b);
      printf("Capacity: %d\n", c);
      printf("Current flow: %d\n", f);
  }
};

const int MAXN = 105;
const int64_t INF = 1e15;

int s, t; // s - start; t - end;
int n, m; // n - number of vertex; m - number of e;
int64_t lim = 1125899906842624ll;

std::vector<Edge> e;
std::vector<int> g[MAXN];
std::queue<int> q;
int ptr[MAXN];
int d[MAXN];


std::vector<bool> reachFromS;
int cnt = 0;

int64_t flow = 0;

void init();
void out();
void addEdge(int const, int const, int const);
void dinic();
bool bfs();
int64_t dfs(int const, int64_t const);
void dfs(int const);

void init() {
    scanf("%d %d", &n, &m);

    s = 0;
    t = n - 1;

    for (int a, b, c, i = 0; i < m; ++i) {
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
        //addEdge(b, a, c);
    }

    dinic();

    out();
}

void out () {
    std::vector<int> out;
    reachFromS.resize(n, false);
    dfs(s);
    int num_a = 0;
    for (int i = 0; i < e.size(); i += 2) {
        if (reachFromS[e[i].a] ^ reachFromS[e[i].b]) {
            out.push_back(i / 2 + 1);
        }
    }
    std::cout << out.size() << " " << flow << "\n";
    for (int o : out) {
        std::cout << o << " ";
    }
}

void dfs(int const cur) {
    reachFromS[cur] = true;
    for (size_t i = 0; i < (int) g[cur].size(); i++) {
        int id = g[cur][i];
        int to = e[id].b;
        if (e[id].f < e[id].c && !reachFromS[to]) {
            dfs(to);
        }
    }
}

void addEdge(int const a, int const b, int const c) {
    g[a].push_back((int) e.size());
    e.emplace_back(a, b, c, 0);
    g[b].push_back((int) e.size());
    e.emplace_back(b, a, 0, 0);
}

void dinic() {
    for (lim = (1 << 30); lim >= 1;){
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        memset(ptr, 0, n * sizeof ptr[0]);

        while (int64_t  cur_flow = dfs(s, lim)) {
            flow += cur_flow;
        }
    }
}

bool bfs() {
    memset(d, -1, n * sizeof d[0]);
    d[s] = 0;
    q.push(s);
    while (!q.empty() && d[t] == -1) {
        int cur = q.front();
        q.pop();
        for (size_t i = 0; i < g[cur].size(); i++) {
            int id = g[cur][i];
            int to = e[id].b;
            if (d[to] == -1 && e[id].c - e[id].f >= lim) {
                d[to] = d[cur] + 1;
                q.push(to);
            }
        }
    }
    std::queue<int>().swap(q);
    return d[t] != -1;
}

int64_t  dfs(int const cur, int64_t  const flow) {
    if (flow == 0) {
        return 0;
    }
    if (cur == t) {
        return flow;
    }
    for (; ptr[cur] < (int) g[cur].size(); ptr[cur]++) {
        int id = g[cur][ptr[cur]];
        int to = e[id].b;

        if (d[to] != d[cur] + 1) {
            continue;
        }
        int64_t  pushed = dfs(e[id].b, std::min(flow, e[id].c - e[id].f));
        if (pushed) {
            e[id].f += pushed;
            e[id ^ 1].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

int main() {
    init();
}
