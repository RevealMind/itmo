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
    long f, c;
    Edge *rev;

    Edge(int a, int b, long c, long f) : a(a), b(b), f(f), c(c), rev(nullptr) {}

    long remain() {
        return c - f;
    }
};

size_t const MAXN = static_cast<const size_t>(100 + 5);

size_t s, t;
size_t n, m, k;
size_t day = 1;

vector<std::string> table(MAXN);

vector<vector<Edge *> > g(MAXN);

vector<size_t> scores(MAXN), needScores(MAXN);
vector<vector<int> > notPlay(MAXN);
vector<bool> used(MAXN);

std::ostream &operator<<(std::ostream &out, Edge const &e) {
    return out << "[" << e.a << "->" << e.b << " :: " << e.f << "/" << e.c << "]";
}

void out() {
    for (int i = 1; i <= n; ++i) {
        for (auto edge : g[i]) {
            if (edge->b != t && edge->b != s && i < edge->b) {
                switch (edge->f) {
                    case 0 :
                        table[i][edge->b] = 'W';
                        table[edge->b][i] = 'L';
                        break;
                    case 1 :
                        table[i][edge->b] = 'w';
                        table[edge->b][i] = 'l';
                        break;
                    case 2 :
                        table[i][edge->b] = 'l';
                        table[edge->b][i] = 'w';
                    break;
                    default :
                        table[i][edge->b] = 'L';
                        table[edge->b][i] = 'W';
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cout << table[i][j];
        }
        std::cout << "\n";
    }
}

long dfs(int const cur, long const flow) {
    if (cur == t || flow == 0) {
        return flow;
    }
    used[cur] = true;
    for (auto&e : g[cur]) {
        if (!used[e->b] && e->remain() > 0) {
            int delta = dfs(e->b, std::min (flow, e->remain()));
            if (delta) {
                e->f += delta;
                e->rev->f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

long dinic() {
    long flow = 0;
    while (true) {
        used.assign(used.size(), false);
        long pushed = dfs(s, std::numeric_limits<long>::max());
        flow += pushed;
        if (pushed == 0) {
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

long canFlow(int const team) {
    long flow = 0;
    for (size_t i = 0; i < notPlay[team].size(); ++i) {
        if (notPlay[team][i] > team) {
            flow += 3;
        }
    }
    return flow;
}

void init() {
    std::cin >> n;
    s = 0;
    t = n + 1;
    std::string ss;
    for (int i = 1; i <= n; ++i) {
        std::cin >> ss;
        table[i].push_back('-');
        for (int j = 1; j <= n; ++j) {
            table[i].push_back(ss[j - 1]);
            switch (ss[j - 1]) {
                case 'W' :
                    scores[i] += 3;
                    break;
                case 'w' :
                    scores[i] += 2;
                    break;
                case 'L' :
                    scores[i] += 0;
                    break;
                case 'l' :
                    scores[i] += 1;
                    break;
                case '.' :
                    notPlay[i].push_back(j);
                    break;
                default:
                    break;
            }
        }
    }
    for (size_t in, i = 1; i <= n; ++i) {
        std::cin >> in;
        needScores[i] = std::max ((size_t) 0, in - scores[i]);
    }

    for (int i = 1; i <= n; ++i) {
        addEdge(s, i, canFlow(i));
    }

    for (int i = 1; i <= n; ++i) {
        addEdge(i, t, needScores[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < notPlay[i].size(); ++j) {
            if (notPlay[i][j] > i) {
                addEdge(i, notPlay[i][j], 3);
            }
        }
    }
    dinic();
}

void solve() {
    init();
    out();
}

int main() {
    solve();
    return 0;
}
