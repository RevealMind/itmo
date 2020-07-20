#include<bits/stdc++.h>
std::vector<int> a(100000);
int n;
bool ifheap() {
    for (int i = 0; i < n; i++) {
        if ((((2 * i + 1) < n) && !(a[i] <= a[2 * i + 1])) || (((2 * i + 2) < n) && !(a[i] <= a[2 * i + 2])))
            return 0;
    }
    return 1;
}
int main() {
    freopen("isheap.out", "w", stdout);
    freopen("isheap.in", "r", stdin);
    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    if (ifheap()) std::cout << "YES";
    else std::cout << "NO";
}