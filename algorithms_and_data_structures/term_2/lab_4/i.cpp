#include <iostream>
#include <vector>
#include <cstdio>

std::vector<std::vector<int> > matrix(4, std::vector<int>(4)), ans(4, std::vector<int>(4)), mul(4, std::vector<int>(4));
std::vector<int> arr;

void to_matrix() {
    int ind = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ans[i][j] = arr[ind];
            ind++;
        }
    }
}

void multiply() {
    to_matrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mul[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                mul[i][j] += ans[i][k] * ans[k][j];
            }
            mul[i][j] %= 2;
        }
    }
}

bool equals() {
    multiply();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mul[i][j] != matrix[i][j])
                return false;
        }
    }
    return true;
}

bool end = false;

void gen(int n) {
    if (end)
        return;
    if (n == 0) {
        if (equals()) {
            end = true;
        }
        return;
    }
    arr.push_back(0);
    gen(n - 1);
    arr.pop_back();
    if (end)
        return;
    arr.push_back(1);
    gen(n - 1);
    arr.pop_back();
    if (end)
        return;
}

int main() {
    freopen("sqroot.in", "r", stdin);
    freopen("sqroot.out", "w", stdout);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cin >> matrix[i][j];
        }
    }

    gen(16);

    if (end) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                std::cout << ans[i][j] << " ";
            std::cout << "\n";
        }
    } else
        std::cout << "NO SOLUTION";
    return 0;
}