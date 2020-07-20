#include <iostream>
#include <fstream>

int main() {
    std::ifstream in("lottery.in");
    std::ofstream out("lottery.out");
    int n, m;
    in >> n;
    in >> m;
    double *a = new double[m];
    double *b = new double[m];
    double sum = 0, probability = 1;
    for (int i = 0; i < m; i++)
    {
        in >> a[i];
        in >> b[i];
    }
    for(int i = 0; i < m - 1; i++)
    {
        probability /= a[i];
        sum += probability * b[i] * (a[i + 1] - 1) / a[i + 1];
    }
    sum += b[m - 1] * probability / a[m - 1];
    out << n - sum;
    in.close();
    out.close();
    return 0;
}