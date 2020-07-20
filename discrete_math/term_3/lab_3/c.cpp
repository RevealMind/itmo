#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using std::vector;
using std::pair;

std::string file_name = "matching";

vector<pair<int, int> > weights;
vector<vector<int> > G;
vector<int> mt, mt_reverse;
vector<bool> used;

void init();

void solve();

bool khun(int v);

void init() {
    int n;

    std::cin >> n;

    for (int i = 0, weight; i < n; ++i) {
        std::cin >> weight;
        weights.emplace_back(weight, i);
    }

    std::sort(weights.begin(), weights.end(), std::greater<pair<int, int> >());

    G.resize(n);
    used.resize(n);
    mt.resize(n, -1);
    mt_reverse.resize(n, -1);

    for (int i = 0, m; i < n; ++i) {
        std::cin >> m;
        for (int j = 0, to; j < m; j++) {
            std::cin >> to;
            G[i].push_back(to - 1);
        }
    }
}

void solve() {
    int n = used.size();
    for (auto cur : weights) {
        used.assign(n, false);
        khun(cur.second);
    }

    for (auto out : mt_reverse) {
        std::cout << out + 1 << " ";
    }
}

bool khun(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (auto to : G[v]) {
        if (mt[to] == -1 || khun(mt[to])) {
            mt[to] = v;
            mt_reverse[v] = to;
            return true;
        }
    }
    return false;
}

int main() {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
    init();
    solve();
}
