#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::min;

const int INF = std::numeric_limits<int>::max();

const size_t root = 1;

size_t n, k, p;

vector<vector<int>> table;
vector<vector<size_t>> edges;
vector<vector<int>> costs;
vector<vector<vector<int>>> dp;

inline void add_edge(size_t from, size_t to) {
    edges[from].push_back(to);
}

inline void init() {
    std::cin >> n >> k >> p;
    edges.resize(n + 1);
    costs.resize(n + 1, vector<int>(k + 1));
    dp.resize(n + 1, vector<vector<int>>(k + 1, vector<int>(k + 1, 0)));

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= k; ++j) {
            std::cin >> costs[i][j];
        }
    }

    for (size_t from, to, i = 1; i < n; ++i) {
        std::cin >> from >> to;
        add_edge(from, to);
        add_edge(to, from);
    }

}

int hungarian_algorithm(vector<vector<int>> &table, size_t n, size_t m) {
    vector<int> u(n + 1, 0);
    vector<int> v(m + 1, 0);
    vector<size_t> p(m + 1, 0);
    vector<size_t> way(m + 1, 0);

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

    return -v[0];
}

void dp_init(size_t v) {
    for (int color = 1; color <= k; ++color) {
        for (int parent_color = 1; parent_color <= k; ++parent_color) {
            dp[v][color][parent_color] = costs[v][color];
        }
    }
}

void create_tree_with_root(size_t v, vector<bool> &&used, vector<vector<size_t>> &children) {
    used[v] = true;

    for (size_t to : edges[v]) {
        if (!used[to]) {
            children[v].push_back(to);
            create_tree_with_root(to, ((vector<bool> &&) used), children);
        }
    }

    if (children[v].empty()) {
        dp_init(v);
    }
}


void dp_update(size_t v, vector<vector<size_t>> &children) {
    for (size_t parent_color = 1; parent_color <= k; ++parent_color) {
        for (size_t color = 1; color <= k; ++color) {
            if (!children[v].empty()) {
                dp[v][color][parent_color] = p + costs[v][color];
            }

            for (size_t child : children[v]) {
                int cost = INF;
                for (size_t child_color = 1; child_color <= k; ++child_color) {
                    cost = min(cost, dp[child][child_color][color]);
                }
                dp[v][color][parent_color] += cost;
            }

            if (!children[v].empty() && children[v].size() < k ||
                v == root && children[v].size() <= k) {
                for (size_t i = 0; i < children[v].size(); ++i) {
                    for (size_t child_color = 1; child_color <= k; ++child_color) {
                        if (v != root && child_color == parent_color) {
                            table[i + 1][child_color] = INF;
                        } else {
                            table[i + 1][child_color] = dp[children[v][i]][child_color][color];
                        }
                    }
                }
                dp[v][color][parent_color] = min(dp[v][color][parent_color],
                                                 hungarian_algorithm(table, children[v].size(), k) + costs[v][color]);
            }
        }
    }
}

void dfs(size_t v, vector<vector<size_t>> children) {
    for (size_t to : children[v]) {
        dfs(to, children);
    }
    dp_update(v, children);
}

inline void process() {
    vector<bool> used(n + 1, false);
    vector<vector<size_t>> children(n + 1);
    create_tree_with_root(root, vector<bool>(n + 1, false), children);
    table.resize(n + 2, vector<int>(k + 2));
    dfs(root, children);
}

inline void out() {
    int out = INF;
    for (size_t color = 1; color <= k; ++color) {
        out = min(out, dp[root][color][1]);
    }
    std::cout << out;
}

inline void solve() {
    init();
    process();
    out();
}

int main() {
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    solve();
}