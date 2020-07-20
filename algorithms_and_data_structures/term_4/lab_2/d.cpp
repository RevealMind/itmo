#include <iostream>

using std::max;
using std::min;
int ans,r1, r2, s1, s2, p1, p2;

void init() {
    std::cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
}


void process() {
    ans = max(0, max(p1 - p2 - s2, max(r1 - r2 - p2, s1 - s2 - r2)));
}

void out() {
    std::cout << ans;
}

void solve() {
    init();
    process();
    out();
}


int main() {
    freopen("rps2.in", "r", stdin);
    freopen("rps2.out", "w", stdout);
    solve();
}