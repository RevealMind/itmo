#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::vector;
using std::pair;

std::string file_name = "destroy";

struct Edge {
    int v1 = 0, v2 = 0;
    uint64_t weight = 0;

    Edge(int v1, int v2, uint64_t weight) : v1(v1), v2(v2), weight(weight) {}
};

bool operator<(const Edge &a, const Edge &b) {
    return a.weight > b.weight;
}

vector<pair<Edge, int> > G;
vector<int> p, res;
vector<bool> used;
int n, m;
uint64_t S, sum = 0;

int dsu_get(int v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1)
        std::swap(a, b);
    if (a != b)
        p[a] = b;
}

uint64_t kruskalMST() {
    for (int i = 0; i < n; ++i)
        p[i] = i;

    uint64_t res = 0;
    for (int i = 0; i < m; i++) {
        if (dsu_get(G[i].first.v1) != dsu_get(G[i].first.v2)) {
            used[i] = 1;
            res += G[i].first.weight;
            dsu_unite(G[i].first.v1, G[i].first.v2);
        }
    }
    return res;
}

void init() {
    int v1, v2;
    uint64_t weight;

    std::cin >> n >> m >> S;

    p.resize(n);
    used.resize(m, false);

    for (int i = 0; i < m; i++) {
        std::cin >> v1 >> v2 >> weight;
        G.emplace_back(Edge(v1 - 1, v2 - 1, weight), i);
        sum += weight;
    }

    std::sort(G.begin(), G.end());
}

void solve() {
    uint64_t cur_tree_weight = kruskalMST();
    int j = 0;
    while (sum - cur_tree_weight > S) {
        if (!used[j]) {
            used[j] = true;
            cur_tree_weight += G[j].first.weight;
        }
        j++;
    }

    for (int i = 0; i < m; ++i) {
        if (!used[i]) {
            res.push_back(G[i].second);
        }
    }

    std::sort (res.begin(), res.end());

    std::cout << res.size() << "\n";
    for (int out : res) {
        std::cout << out + 1 << " ";
    }
}


int main() {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
    std::ios_base::sync_with_stdio(false);
    init();
    solve();
    return 0;
}