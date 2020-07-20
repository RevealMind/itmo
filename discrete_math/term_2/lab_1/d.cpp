#include <iostream>
#include <fstream>

int main() {
    std::ifstream in("markchain.in");
    std::ofstream out("markchain.out");
    int n;
    in >> n;
    double ans[n], ans_tmp[n], arr[n][n], tmp[n][n], sum;
    for (int i = 0; i < n; i++) {
        ans[i] = 1 / (double) n;
        for (int j = 0; j < n; j++)
            in >> arr[i][j];
    }

    for (int k = 0; k < 15; k++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                sum = 0;
                for (int m = 0; m < n; m++) {
                    sum += arr[i][m] * arr[m][j];
                }
                tmp[i][j] = sum;
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                arr[i][j] = tmp[i][j];
    }

    for (int i = 0; i < n; i++) {
        ans_tmp[i] = 0;
        for (int k = 0; k < n; k++)
            ans_tmp[i] += ans[i] * arr[k][i];

    }
    out.precision(5);
    for (int i = 0; i < n; i++)
        out << ans_tmp[i] << "\n";
    return 0;
}