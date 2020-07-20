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
    int posX;
    int posY;
    Edge * rev;
    bool isReverse;

    void print() {
        std::cout << a << " - > " << b << "\n";
    }

    Edge(int a, int b, int c, int f, int posX, int posY, bool isReverse = false) : a(a), b(b), f(f), c(c),
                                                                                               posX(posX),
                                                                                               posY(posY),
                                                                                               rev(nullptr),
                                                                                               isReverse(isReverse) {}

    int remain() {
        return c - f;
    }
};

size_t s, t;
size_t n, m;
vector<int> matching;
vector<vector<Edge*> > g1, g2;

vector<bool> used;
vector<vector<bool> > brokenCell;
vector<bool> reachFromS;
vector<int> ptr;
vector<int> dist;

std::ostream& operator<<(std::ostream& out, Edge const & e) {
    return out << "[" << e.a << "->" << e.b << " :: " << e.f << "/" << e.c << "]";
}



void dfs(int const cur, vector<vector<Edge*> > &g) {
    reachFromS[cur] = true;
    for (size_t i = 0; i < g[cur].size(); ++i) {
        int to = g[cur][i]->b;
        if (!reachFromS[to] && g[cur][i]->remain()) {
            dfs(to, g);
        }
    }
}

void out(vector<vector<Edge*> >& g, int w) {
    dfs(s, g);
    for (int i = 1; i < n + m; ++i) {
        if (!reachFromS[i]) {
            for (auto it = g[i].begin(); it != g[i].end(); ++it) {
                int to = (*it)->b,
                    x = (*it)->posX,
                    y = (*it)->posY;
                if (to != s) {
                    std::cout << 1 << " " << x << " " << y << " " << ((x + y) % 2 == w? "W" : "B") << "\n";
                    break;
                }
            }
        }
    }

    for (int i = n + m; i < (2 * (n + m)); ++i) {
        if (reachFromS[i]) {
            for (auto it = g[i].begin(); it != g[i].end(); ++it) {
                int to = (*it)->b,
                    x = (*it)->posX,
                    y = (*it)->posY;
                if (to != t) {
                    std::cout << 2 << " " << x << " " << y << " " << ((x + y) % 2 == w? "W" : "B") << "\n";
                    break;
                }
            }
        }
    }
}

int dfs(int const cur, int const flow, vector<vector<Edge*>> &g) {
    if (flow == 0) {
        return 0;
    }
    if (cur == t) {
        return flow;
    }
    for (;ptr[cur] < (int) g[cur].size(); ++ptr[cur]) {
        int to = g[cur][ptr[cur]]->b;
        if (dist[to] != dist[cur] + 1) {
            continue;
        }
        int delta = dfs(to, std::min (flow, g[cur][ptr[cur]]->remain()), g);
        if (delta) {
            g[cur][ptr[cur]]->f += delta;
            g[cur][ptr[cur]]->rev->f -=delta;
            return delta;
        }
    }
    return 0;
}


bool bfs(int const s, vector<vector<Edge*>> &g) {
    dist.assign(dist.size(), -1);
    std::queue<int> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty() && dist[t] == -1) {
        int cur = q.front();
        q.pop();
        for (auto it = g[cur].begin(); it != g[cur].end(); ++it) {
            int to = (*it)->b;
            if (dist[to] == -1 && (*it)->remain() > 0) {
                dist[to] = dist[cur] + 1;
                q.push(to);
            }
        }
    }
    return dist[t] != -1;
}

int dinic(vector<vector<Edge*>> &g) {
    int flow = 0;
    while (bfs(s, g)) {
        ptr.assign(ptr.size(), 0);
        int pushed = dfs(s, 1, g);
        if (pushed) {
            flow += pushed;
        }
    }
    return flow;
}

// (0,0) - white;
void getMask() {
    std::string in;
    for (int i = 0; i < n; ++i) {
        std::cin >> in;
        for (int j = 0; j < m; ++j) {
            bool even = (i + j) % 2 == 0;
            char c = in[j];
            switch (c) {
                case 'W' :
                    brokenCell[i][j] = !even;
                    break;
                case 'B' :
                    brokenCell[i][j] = even;
                    break;
                default:
                    break;
            }
        }
    }
}

void addEdge(vector<vector<Edge*> > &g, int const from, int const to, int const x, int const y) {
    Edge * e1 = new Edge(from, to, 1, 0, x, y);
    Edge * e2 = new Edge(to, from, 1, 1, x, y, true);
    e1->rev = e2;
    e2->rev = e1;
    g[from].push_back(e1);
    g[to].push_back(e2);
}

void setEdge() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int from = i + j + 1,
                    to = j - (i - n + 1) + n + m;
            if (brokenCell[i][j]) {
                addEdge(g1, from, to, i + 1, j + 1);
            } else {
                addEdge(g2, from, to, i + 1, j + 1);
            }
        }
    }

    for (int i = 1; i < n + m; ++i) {
        addEdge(g1, 0, i, -1, -1);
        addEdge(g2, 0, i, -1, -1);
    }

    for (int i = n + m; i < 2 * (n + m) - 1; ++i) {
        addEdge(g1, i, 2 * (n + m) - 1, -1, -1);
        addEdge(g2, i, 2 * (n + m) - 1, -1, -1);
    }
}

void init() {
    std::cin >> n >> m;
    s = 0;
    t = 2 * (n + m) - 1;
    used.resize(2 * (n + m));
    dist.resize(2 * (n + m));
    ptr.resize(2 * (n + m));
    reachFromS.resize(2 * (n + m), false);
    g1.resize(2 * (n + m));
    g2.resize(2 * (n + m));
    brokenCell.resize(n, vector<bool>(m));
}

void solve() {
    init();
    getMask();
    setEdge();
    int flow1 = dinic(g1),
        flow2 = dinic(g2);
    std::cout << std::min (flow1, flow2) << "\n";

    out((flow1 < flow2) ? g1 : g2, (flow1 < flow2) ? 0 :  1);
}

int main() {
    solve();
    return 0;
}
