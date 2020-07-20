#include <iostream>
#include <fstream>

int main() {
    std::ifstream in("exam.in");
    std::ofstream out("exam.out");
    double result = 0;
    int k, n, p, m;
    in >> k;
    in >> n;
    for (int i = 0; i < k; i++) {
        in >> p;
        in  >> m;
        result += m * p;
    }
    result /= (100 * n);
    out << result;
    in.close();
    out.close();
    return 0;
}