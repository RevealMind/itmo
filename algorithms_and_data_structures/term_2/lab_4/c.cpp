#include <iostream>
#include <vector>
#include <limits>
#include <cstdio>

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long ans = std::numeric_limits<long long>::max();
std::vector<std::pair<long long, long long> > a(7);
long long max_sum = 2000000000;
void gen(long long n, long long sum) {
    if (sum > max_sum || sum < 0)
        return;
    if (n == 0) {
        ans = min(ans, sum);
        return;
    }
    for (int i = 0; i < 7; i++) {
        long long add = (n / a[i].second) * a[i].first;
        if (add > max_sum || add < 0)
            continue;
        if (n % a[i].second == n)
            gen(0, sum + a[i].first);
        else
            gen(n % a[i].second, sum + (n / a[i].second) * a[i].first);
    }
}

int main() {
    freopen("printing.in", "r", stdin);
    freopen("printing.out", "w", stdout);
    int n;
    std::cin >> n;
    int paper = 1;
    for (int i = 0; i < 7; i++) {
        std::cin >> a[i].first;
        a[i].second = paper;
        paper *= 10;
    }
    gen(n, 0LL);
    std::cout << ans;
}