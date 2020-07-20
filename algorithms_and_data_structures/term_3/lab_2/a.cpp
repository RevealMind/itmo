#include <iostream>
#include <vector>

using std::vector;

vector<vector<long> > G;

int min (int a, int b) {
    return a < b ? a : b;
}

void init() {
    size_t n;
    long weight;
    std::cin >> n;
    G.resize(n, vector<long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> weight;
            G[i][j] = weight;
        }
    }
}

void floyd () {
    size_t n = G.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}

void print() {
    size_t n = G.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << G[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void solve() {
    init();
    floyd();
    print();
}

int main() {
    solve();
    return 0;
}