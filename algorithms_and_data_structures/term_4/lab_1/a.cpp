#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Edge {
  int a, b, c, f;
  Edge(int a, int b, int c, int f) : a(a), b(b), c(c), f(f) {}
  void print() {
      printf("Start: %d\n", a);
      printf("End: %d\n", b);
      printf("Capacity: %d\n", c);
      printf("Current flow: %d\n", f);
  }
};

const int MAXN = 105;
const int INF = 1e9;

int s, t; // s - start; t - end;
int n, m; // n - number of vertex; m - number of e;
int lim;

std::vector<Edge> e;
std::vector<int> g[MAXN];
std::queue<int> q;
int ptr[MAXN];
int d[MAXN];

long long flow = 0;

void init();
void out();
void addEdge(int const, int const, int const);
int dinic();
bool bfs();
int dfs(int const, int const);

void init() {
    scanf("%d %d", &n, &m);

    s = 0;
    t = n - 1;

    for (int a, b, c, i = 0; i < m; ++i) {
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
        //addEdge(b, a, c);
    }

    /*for (int i = 0; i < e.size(); i++) {
        printf("e[%d]\n", i);
        e[i].print();
        printf("\n");
    }*/



    out();
}

void out () {
    std::cout << std::setprecision(8) << dinic() << "\n";
    for (int i = 0; i < e.size() /*&& e[i].f != 0*/; i+=2) {
        if (e[i].f) {
            printf("e[%d]\n", i);
            e[i].print();
            printf("\n");
        }
    }
    /*for (int i = 0; i < e.size(); i += 4) {
        if (e[i].f == 0)
            std::cout << std::setprecision(8) << e[i + 3].f;
        else
            std::cout << std::setprecision(8) << e[i].f;
        std::cout << "\n";
    }*/
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
        memset(ptr, 0, n * sizeof ptr[0]);
        int pushed = dfs(s, INF);
        if (pushed) {
            total += pushed;
        }
    }
    return total;
}

bool bfs(){
    memset(d, -1, n * sizeof d[0]);
    std::queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
        int cur = q.front(); q.pop();
        for (int i = 0; i < (int) g[cur].size(); ++i) {
            int id = g[cur][i],
                to = e[id].b;

            if (d[to] == -1 && e[id].f < e[id].c) {
                d[to] = d[cur] + 1;
                q.push(to);
            }
        }
    }
    return d[t] != -1;
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
        if (d[to] != d[cur] + 1) {
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
/*
void dinic() {
    for (lim = (1 << 30); lim >= 1;){
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        memset(ptr, 0, n * sizeof ptr[0]);

        while (int cur_flow = dfs(s, lim)) {
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

int dfs(int const cur, int const flow) {
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
        int pushed = dfs(e[id].b, std::min(flow, e[id].c - e[id].f));
        if (pushed) {
            e[id].f += pushed;
            e[id ^ 1].f -= pushed;
            return pushed;
        }
    }
    return 0;

}*/

int main() {
    init();
}
