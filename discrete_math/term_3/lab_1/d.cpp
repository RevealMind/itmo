#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <cstdio>

using std::deque;
using std::string;
using std::vector;

vector<vector<bool> > G;
vector<int> vertex_order;
deque<int> ans;

void init() {
    int n;
    string tmp;
    std::cin >> n;
    G.resize(n, vector<bool>(n, false));
    vertex_order.push_back(0);
    for (int i = 1; i < n; i++) {
        vertex_order.push_back(i);
        std::cin >> tmp;
        for (int j = 0; j < i; j++) {
            bool flag = tmp[j] - '0';
            G[i][j] = flag;
            G[j][i] = !flag;
        }
    }
}


void bin_search(int left, int right, int key) {
    while (right - left > 1) {
        int middle_pos = (right + left) / 2;
        deque<int>::iterator middle = ans.begin();
        std::advance(middle, middle_pos);
        if (G[*middle][key]) {
            left = middle_pos;
        } else
            right = middle_pos;
    }
    deque<int>::iterator position = ans.begin();
    std::advance(position, right);
    ans.insert(position, key);
}

void solve() {
    while (true) {
        ans.push_back(vertex_order[0]);
        for (int i = 1; i < G.size(); i++)
            bin_search(-1, i, vertex_order[i]);

        if (G[*(ans.end() - 1)][*ans.begin()]) {
            break;
        }
        else {
            std::random_shuffle(vertex_order.begin(), vertex_order.end());
            ans.clear();
        }
    }

    for (int out : ans) {
        std::cout << out + 1 << " ";
    }
}

int main() {
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);
    init();
    solve();
    return 0;
}