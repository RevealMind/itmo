#include <bits/stdc++.h>

using namespace std;

vector<bool> use;
vector<vector<int> > states;
vector<int> acceptStates;
vector<vector<int> > backStates;
vector<int> visited;
int n;
const int MOD = 1000000007;

void pushAll(int v) {
    if (use[v])
        return;
    use[v] = true;
    for (auto u : backStates[v]) {
        if (!use[u])
            pushAll(u);
    }
}

bool dfsCycle(int v) {
    if (!use[v])
        return false;
    if (visited[v])
        return true;
    visited[v] = true;
    for (auto u : states[v]) {
        if (u == -1) {
            continue;
        }
        if (dfsCycle(u)) {
            visited[v] = false;
            return true;
        }
    }
    visited[v] = false;
    return false;
}

bool isCycle() {
    visited.resize(n, false);
    return dfsCycle(0);
}

long long int sum(int v) {
    if (!use[v])
        return 0;
    long long int ans = acceptStates[v] ? 1 : 0;
    for (auto u : states[v]) {
        if (u == -1)
            continue;
        ans += sum(u);
        ans %= MOD;
    }
    return ans;
}

int main() {
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
    int m, k;
    scanf("%d %d %d", &n, &m, &k);
    use.resize(n, false);
    states.resize(n, vector<int>('z' - 'a' + 1, -1));
    acceptStates.resize(n, false);
    backStates.resize(n);

    int pos;
    for (int i = 0; i < k; ++i) {
        scanf("%d", &pos);
        acceptStates[pos - 1] = true;
    }

    int from, to;
    char sym;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %c", &from, &to, &sym);
        states[from - 1][(int) (sym - 'a')] = to - 1;
        backStates[to - 1].push_back(from - 1);
    }

    for (int i = 0; i < n; ++i) {
        if (acceptStates[i]) {
            pushAll(i);
        }
    }

    if (isCycle()) {
        printf("-1");
        return 0;
    }
    printf("%lld", sum(0));
    return 0;
}