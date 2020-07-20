#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstdio>

using std::vector;
using std::pair;

vector<pair<int, int> > E;
vector<vector<int>> E_for_check;
std::vector<int> order;
vector<int> part;

void init();
void solve();
bool is_cross(pair<int, int> &a, pair<int, int> &b);
bool is_bigraph();

bool is_cross(pair<int, int> &a, pair<int, int> &b) {
    int a1 = a.first, a2 = a.second, b1 = b.first, b2 = b.second;
    return (order[a2] > order[b1] && order[a2] < order[b2] && order[a1] < order[b1]) ||
           (order[b2] > order[a1] && order[b2] < order[a2] && order[b1] < order[a1]);
}

bool is_bigraph() {
    bool flag = true;
    part.resize(E_for_check.size(), 0);
    for (int i = 0; i < (int) E_for_check.size(); i++) {
        if (part[i] == 0) {
            std::queue<int> q;
            q.push(i);
            part[i] = 1;
            while (!q.empty()) {
                int from = q.front();
                q.pop();
                for (int j = 0; j < (int) E_for_check[from].size(); j++) {
                    int to = E_for_check[from][j];

                    if (part[to] == 0) {
                        part[to] = part[from] * (-1);
                        q.push(to);
                    } else {
                        flag &= (part[to] != part[from]);
                    }
                }
            }
        }
    }
    return flag;
}

void init() {
    int n, m;
    int from, to;
    int cycle;

    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> from >> to;
        from--;
        to--;
        E.emplace_back(from, to);
    }

    order.resize(n);
    for (int i = 0; i < n; i++) {
        std::cin >> cycle;
        cycle--;
        order[cycle] = i;
    }
}

void solve() {
    for (auto &i : E) {
        if (order[i.first] > order[i.second])
            std::swap(i.first, i.second);
    }

    E_for_check.resize(E.size());
    for (int i = 0; i < E.size(); i++) {
        for (int j = 0; j < E.size(); j++) {
            if (i != j && is_cross(E[i], E[j])) {
                E_for_check[i].push_back(j);
            }
        }
    }

    if (is_bigraph()) {
        std::cout << "YES\n";

        for (int i : order) {
            std::cout << 2 * i << " " << 0 << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < E.size(); i++) {
            int x = order[E[i].first] + order[E[i].second],
                    y = std::abs(order[E[i].first] - order[E[i].second]) * part[i];
            std::cout << x << " " << y << "\n";
        }
    } else {
        std::cout << "NO";
    }
}

int main() {
    init();
    solve();
    return 0;
}