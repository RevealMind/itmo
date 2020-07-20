#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;
using std::size_t;

vector<vector<pair<int, int> > > G;
vector<int> d, p;

int const INF = 1000000000;

void init();

void solve();

int max(int a, int b);

void init() {
    size_t n;
    int weight;

    std::cin >> n;
    G.resize(n);
    p.resize(n, -1);
    d.resize(n, INF);

    for (size_t from = 0; from < n; from++) {
        for (size_t to = 0; to < n; to++) {
            std::cin >> weight;
            if (weight != 100000) {
                G[from].emplace_back(to, weight);
            }
        }
    }
}

void solve() {
    int x = -1;
    d[0] = 0;
    size_t n = G.size();
    for (int k = 0; k < n; k++) {
        x = -1;
        for (int from = 0; from < n; from++) {
            for (auto tmp : G[from]) {
                int to = tmp.first;
                int weight = tmp.second;
                if (d[to] > d[from] + weight) {
                    d[to] = max((-1) * INF, d[from] + weight);
                    p[to] = from;
                    x = to;
                }
            }
        }
    }

    if (x == -1) {
        std::cout << "NO";
    } else {
        int start = x;
        for (int i = 0; i < n; ++i)
            start = p[start];

        vector<int> ans;
        for (int cur = start;; cur = p[cur]) {
            if (cur == start && ans.size() > 1) break;
            ans.push_back(cur);
        }
        std::reverse(ans.begin(), ans.end());

        std::cout << "YES\n";
        std::cout << ans.size() << "\n";
        for (int out : ans)
            std::cout << out + 1 << ' ';
    }
}


int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    init();
    solve();
    return 0;
}