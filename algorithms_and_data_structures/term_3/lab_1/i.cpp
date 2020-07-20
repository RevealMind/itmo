#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using std::vector;
using std::pair;
using std::sqrt;

vector<pair<int, int> > vertex;
const int MAX = 100000;

double distance(pair<int, int> a, pair<int, int> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void init() {
    int n;
    int x, y;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x, &y);
        vertex.push_back(std::make_pair(x, y));
    }
}

void ans() {
    init();
    vector<bool> used(vertex.size(), false);
    vector<double> min(vertex.size(), MAX);
    vector<int> end(vertex.size(), -1);
    min[0] = 0;
    double ans = 0;

    for (int i = 0; i < vertex.size(); i++) {
        int v = -1;
        for (int j = 0; j < vertex.size(); j++)
            if (!used[j] && (v == -1 || min[j] < min[v]))
                v = j;
        if (v == -1) {
            std::cout << -1;
            return;
        }

        used[v] = true;

        if (end[v] != -1)
            ans += (distance(vertex[v], vertex[end[v]]));

        for (int j = 0; j < vertex.size(); j++) {
            if (distance(vertex[v], vertex[j]) < min[j]){
                min[j] = distance(vertex[v], vertex[j]);
                end[j] = v;
            }
        }
    }
    printf("%.10f", ans);
}

int main() {
    ans();
    return 0;
}