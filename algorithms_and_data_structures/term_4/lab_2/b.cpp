#include <iostream>
#include <vector>

using std::vector;
using std::pair;

const int INF = std::numeric_limits<int>::max();

size_t n, m;
vector<vector<int>> table;
pair<int, vector<int>> ans;

void init() {
    std::cin >> n;
    m = n;
    table.resize(n + 1, vector<int>(n + 1));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            std::cin >> table[i][j];
        }
    }
}

pair<int, vector<int>> hungarian_algorithm() {
    vector<int> u(n + 1);
    vector<int> v(m + 1);
    vector<size_t> p(m + 1);
    vector<size_t> way(m + 1);
    vector<int> ans(n + 1);

    for (size_t row = 1; row <= n; ++row) {
        p[0] = row;
        size_t column = 0;
        vector<int> min_v(m + 1, INF);
        vector<bool> used(m + 1, false);

        do {
            used[column] = true;
            size_t cur_row = p[column];
            size_t next_column = 0;
            int delta = INF;
            for (size_t cur_column = 1; cur_column <= m; ++cur_column) {
                if (!used[cur_column]) {
                    int cur = table[cur_row][cur_column] - u[cur_row] - v[cur_column];
                    if (cur < min_v[cur_column]) {
                        min_v[cur_column] = cur;
                        way[cur_column] = column;
                    }
                    if (min_v[cur_column] < delta) {
                        delta = min_v[cur_column];
                        next_column = cur_column;
                    }
                }
            }

            for (size_t cur_column = 0; cur_column <= m; ++cur_column) {
                if (used[cur_column]) {
                    u[p[cur_column]] += delta;
                    v[cur_column] -= delta;
                } else {
                    min_v[cur_column] -= delta;
                }
            }

            column = next_column;
        } while (p[column] != 0);

        do {
            size_t next_column = way[column];
            p[column] = p[next_column];
            column = next_column;
        } while (column);
    }

    for (size_t cur_column = 1; cur_column <= m; ++cur_column) {
        ans[p[cur_column]] = cur_column;
    }

    return {-v[0], ans};
}

void process() {
    ans = hungarian_algorithm();
}

void out() {
    std::cout << ans.first << "\n";
    for (size_t i = 1; i <= m; ++i) {
        std::cout << i << " " << ans.second[i] << "\n";
    }
}

void solve() {
    init();
    process();
    out();
}

int main() {
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    solve();
}