#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    std::ifstream in("shooter.in");
    std::ofstream out("shooter.out");
    int n, m, k, z;
    in >> n >> m >> k;
    double k_ver, all_ver = 0, x;
    for(int i = 0; i < n; i++) {
        in >> x;
        all_ver += (std::pow(1 - x, m));
        if(i == k - 1)
            k_ver = std::pow(1 - x, m);
    }
    out.precision(13);
    out << k_ver / all_ver;
    return 0;
}
