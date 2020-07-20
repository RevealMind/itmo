#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <set>

using std::vector;

struct Rect {
    long long x1, y1, x2, y2;

    Rect() {}

    Rect(long long x1, long long y1, long long x2, long long y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};


vector<vector<long long> > g;
vector<Rect> rectangles;
vector<long long> d;
size_t n;
long long w;
long long const INF = (long long) 10000000000;

long long getDist(Rect &r1, Rect &r2) {
    long long a = (r1.x1 < r2.x1) ? r2.x1 - r1.x2 : r1.x1 - r2.x2;
    long long b = (r1.y1 < r2.y1) ? r2.y1 - r1.y2 : r1.y1 - r2.y2;
    return std::max((long long) 0, std::max(a, b));
}

void init() {
    std::cin >> n >> w;
    g.resize(n + 2, std::vector<long long>(n + 2));
    rectangles.resize(n);
    for (size_t i = 0; i < rectangles.size(); ++i) {
        long long x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        rectangles[i] = Rect(x1, y1, x2, y2);
    }

    g[0][n + 1] = g[n + 1][0] = w;

    for (size_t i = 0; i < n; i++) {
        Rect rectangle = rectangles[i];
        g[0][i + 1] = g[i + 1][0] = w - rectangle.y2;
        g[n + 1][i + 1] = g[i + 1][n + 1] = rectangle.y1;
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                g[i + 1][j + 1] = g[j + 1][i + 1] = getDist(rectangle, rectangles[j]);
            }
        }
    }
}

void dijkstra() {
    vector<bool> used(n + 2, false);
    d.resize(n + 2, INF);
    d[0] = 0;
    for (int i = 0; i < n + 2; ++i) {
        long long v = -1;
        for (int j = 0; j < n + 2; ++j) {
            if (!used[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        used[v] = true;
        for (int u = 0; u < n + 2; ++u) {
            if (v != u) {
                long long dist = g[v][u];
                if (d[v] + dist < d[u]) {
                    d[u] = d[v] + dist;
                }
            }
        }
    }
}

void out() {
    std::cout << ((d[n + 1] == INF) ? 0 : d[n + 1]) << "\n";
}

void solve() {
    init();
    dijkstra();
    out();
}

int main() {
    solve();
    return 0;
}
