#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <set>

using std::vector;

struct Edge {
    int a;      // start of the edge
    int b;      // end of the edge
    int f, c;
    Edge *rev;

    Edge(int a, int b, int c, int f) : a(a), b(b), f(f), c(c), rev(nullptr) {}

    int remain() {
        return c - f;
    }
};

size_t const MAXD = static_cast<const size_t>(10e4);

size_t s, t;
size_t n, m, k;
size_t day = 1;

vector<vector<Edge *> > g;

vector<int> from, to;

std::ostream &operator<<(std::ostream &out, Edge const &e) {
    return out << "[" << e.a << "->" << e.b << " :: " << e.f << "/" << e.c << "]";
}

void out() {
    vector<int> ships(k, s);
    for (size_t i = 0; i < day; ++i) {
        std::stringstream buffer;
        size_t amount = 0;
        for (int j = 0; j < k; ++j) {
            for (auto &e : g[ships[j]]) {
                if (e->f > 0) {
                    e->f--;
                    ships[j] = e->b;
                    if (e->c != std::numeric_limits<int>::max()) {
                        amount++;
                        buffer << " " << j + 1 << " " << e->b % n + 1;
                    }
                    break;
                }
            }
        }
        std::cout << amount << buffer.str() << "\n";
        buffer.flush();
    }

}

size_t getId(int const day, int const system) {
    return day * n + system;
}

int dfs(int const cur, int const flow, vector<bool> &used) {
    if (cur == t || flow == 0) {
        return flow;
    }
    used[cur] = true;
    for (auto&e : g[cur]) {
        if (!used[e->b] && e->remain() > 0) {
            int delta = dfs(e->b, std::min (flow, e->remain()), used);
            if (delta) {
                e->f += delta;
                e->rev->f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int dinic(size_t const size, int const countOfShip) {
    int flow = 0;
    vector<bool> used(size);
    while (true) {
        used.assign(used.size(), false);
        int pushed = dfs(s, 1, used);
        flow += pushed;
        if (pushed == 0 || flow == countOfShip) {
            break;
        }
    }
    return flow;
}



void addEdge(int const from, int const to, int const c) {
    Edge *e1 = new Edge(from, to, c, 0);
    Edge *e2 = new Edge(to, from, 0, 0);
    e1->rev = e2;
    e2->rev = e1;
    g[from].push_back(e1);
    g[to].push_back(e2);
}



void init() {
    std::cin >> n >> m >> k >> s >> t;
    s--;
    t--;
    g.resize(51 * MAXD);
    from.resize(m);
    to.resize(m);
    for (size_t start, end, i = 0; i < m; ++i) {
        std::cin >> start >> end;
        from[i] = start - 1;
        to[i] = end - 1;
    }
}

void solve() {
    init();

    int count = 0;

    while (count != k) {
        for (int i = 0; i < n; ++i) {
            addEdge(getId(day - 1, i), getId(day, i), std::numeric_limits<int>::max());
        }
        for (int i = 0; i < m; ++i) {
            addEdge(getId(day - 1, from[i]), getId(day, to[i]), 1);
            addEdge(getId(day - 1, to[i]), getId(day, from[i]), 1);
        }
        size_t saveT = t;
        t = getId(day, t);
        count += dinic(getId(day, n), k - count);
        day++;
        t = saveT;
    }
    std::cout << --day << "\n";
    out();
}

int main() {
    freopen("bring.in", "r", stdin);
    freopen("bring.out", "w", stdout);
    solve();
    return 0;
}
