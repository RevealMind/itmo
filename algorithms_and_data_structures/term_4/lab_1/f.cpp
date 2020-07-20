#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cmath>
struct Point {
    int x, y;
    int speed;

    Point(int const x, int const y, int const speed = -1) : x(x), y(y), speed(speed) {}
};

// GLOBAL variables
double const INF = std::numeric_limits<int>::max();
double const EPS = 0.00001;

int n, m;            // number of vertices and edges
std::vector<int> matching;
std::vector<std::vector<int> > g;
std::vector<bool> used;
int size = 0;

std::vector<Point> startPoints;
std::vector<Point> finalPoints;

//
//

// FUNCTION declaration

void solve();
void init();
void out();

bool dfs(int const);

double binSearch();
bool check(double const);
double dist(Point const, Point const);
double pow(double const);
//
//


// FUNCTION definition

void solve() {
    init();
    out();
}

void init() {
    std::cin >> n;
    matching.resize(n);
    g.resize(n);
    for (int x, y, speed, i = 0; i < n; ++i) {
        std::cin >> x >> y >> speed;
        startPoints.emplace_back(x, y, speed);
    }
    for (int x, y, i = 0; i < n; ++i) {
        std::cin >> x >> y;
        finalPoints.emplace_back(x, y);
    }
}

void out() {
    std::cout << binSearch();
}

bool dfs(int const cur) {
    if (used[cur]) {
        return false;
    }
    used[cur] = true;
    for (int i = 0; i < g[cur].size(); ++i) {
        int to = g[cur][i];
        if (matching[to] == -1 || dfs(matching[to])) {
            matching[to] = cur;
            return true;
        }
    }
    return false;
}

double binSearch() {
    double left = 0,
           right =  INF;
    while (right - left > EPS) {
        double m = (right + left) / 2;
        if (check(m)) {
            right = m;
        } else {
            left = m;
        }
    }
    return right;
}

bool check(double const time) {
    for (int i = 0; i < g.size(); i++) {
        g[i].clear();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist(startPoints[i], finalPoints[j]) <= time) {
                g[i].push_back(j);
            }
        }
    }
    matching.assign(n, -1);
    size = 0;
    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        size += dfs(i) ? 1 : 0;
    }

    return size == n;
}

double dist(Point const start, Point const end) {
    return std::sqrt(pow(start.x - end.x) + pow(start.y - end.y)) / start.speed;
}

double pow(double const x) {
    return x * x;
}
//
//

int main() {
    solve();
}
