#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<vector<long long> > states;
vector<bool> acceptStates;
vector<vector<long long> > E;
int n, l;
const int MOD = 1000000007;

vector<vector<long long> > multiply(vector<vector<long long> > &a, vector<vector<long long> > &b) {
    vector<vector<long long> > tmp(n, vector<long long> (n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                tmp[i][j] += a[i][k] * b[k][j];
            }
            tmp[i][j] %= MOD;
        }
    }
    return tmp;
}

vector<vector<long long> > binpow(vector<vector<long long> > &states, int n) {
    if (n == 0)
        return E;
    if (n % 2 == 1) {
        vector<vector<long long> > b = binpow(states, n - 1);
        return multiply(b, states);
    } else {
        vector<vector<long long> > b = binpow(states, n / 2);
        return multiply(b, b);
    }
}

void print(vector<vector<long long> > &ans) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
}
int main() {
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
    int m, k;
    scanf("%d %d %d %d", &n, &m, &k, &l);
    states.resize(n, vector<long long> (n, 0));
    E.resize(n, vector<long long> (n, 0));
    for (int i = 0; i < n; i++) {
        E[i][i] = 1;
    }
    acceptStates.resize(n, false);
    int pos;
    for (int i = 0; i < k; ++i) {
        scanf("%d", &pos);
        acceptStates[pos - 1] = true;
    }
    int from, to;
    char sym;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %c", &from, &to, &sym);
        states[from - 1][to - 1]++;
    }

    vector<vector<long long> > ans = binpow(states, l);
    long long result = 0;
    for (int i = 0; i < n; i++) {
        if (acceptStates[i])
            result += ans[0][i];
    }
    result %= MOD;
    printf("%lld", result);
    return 0;
}