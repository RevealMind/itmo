//
// Created by Dmitry on 05.05.2019.
//

#include <iostream>
#include <vector>
#include <deque>

struct Edge{
    size_t from, to;
    int64_t f, c, cost;
    size_t rev;

    Edge() {}

    Edge(size_t from, size_t to, int64_t f, int64_t c, int64_t cost) : from(from), to(to), f(f), c(c), cost(cost) {}
};

using std::vector;
using std::deque;

const int64_t INF = std::numeric_limits<int64_t>::max();

size_t n, m, s, t;
int64_t min_cost, max_flow;
vector<vector<Edge>> edges;



void init() {

    std::cin >> n >> m;
    edges.resize(n + 1);

    s = 1; t = n;
    int64_t c, cost;
    for (size_t from, to, i = 0; i < m; ++i) {
        std::cin >> from >> to >> c >> cost;

        edges[from].emplace_back(from, to, 0, c, cost);
        edges[to].emplace_back(to, from, 0, 0, -cost);

        edges[from].back().rev = edges[to].size() - 1;
        edges[to].back().rev = edges[from].size() - 1;
    }
}

bool check(Edge &edge, vector<int64_t> &d) {
    return edge.f < edge.c && d[edge.to] > d[edge.from] + edge.cost;
}

void process() {
    while (true) {
        vector<int> id(n + 1, 0);
        vector<int64_t > d(n + 1, INF);
        vector<Edge *> p(n + 1, nullptr);
        deque<size_t > q;

        d[s] = 0;
        q.push_back(s);

        while (!q.empty()) {
            size_t v = q.front(); q.pop_front();
            id[v] = 2;
            for (Edge &edge : edges[v]) {
                size_t to = edge.to;
                size_t from = edge.from;
                if (check(edge, d)) {
                    d[to] = d[from] + edge.cost;
                    if (id[to] == 0) {
                        q.push_back(to);
                    } else if (id[to] == 2) {
                        q.push_front(to);
                    }
                    p[to] = &edge;
                    id[to] = 1;
                }
            }
        }

        if (d[t] == INF) {
            break;
        }

        int64_t delta = INF;

        for (size_t v = t; v != s; v = p[v]->from) {
            Edge* e = p[v];
            delta = std::min(delta, e->c - e->f);
        }

        for (size_t v = t; v != s; v = p[v]->from) {
            Edge* e = p[v];
            Edge* e_rev = &edges[e->to][e->rev];

            e->f += delta;
            e_rev->f -= delta;

            min_cost += e->cost * delta;
        }

        max_flow += delta;
    }
}

void out() {
    std::cout << min_cost;
}

void solve() {
    init();
    process();
    out();
}

int main() {
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);
    solve();
}