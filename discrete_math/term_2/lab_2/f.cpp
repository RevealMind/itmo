#include <bits/stdc++.h>

using namespace std;

struct DFA {
    int n, m, k;
    vector<vector<int> > states;
    vector<bool> acceptStates;

    DFA(int n, int m, int k) : n(n), m(m), k(k) {
        states.resize(n, vector<int>('z' - 'a' + 1, -1));
        acceptStates.resize(n, false);
    }

    void addTransition(int from, int to, int sym) {
        states[from][sym] = to;
    }

    void setAcceptState(int pos) {
        acceptStates[pos] = true;
    }
};

vector<bool> visited;
vector<DFA> arr;


bool dfs(int first, int second) {
    visited[first] = true;
    if (arr[0].acceptStates[first] != arr[1].acceptStates[second])
        return false;
    bool result = true;
    for (int sym = 0; sym < arr[0].states[first].size(); sym++) {
        int to = arr[0].states[first][sym];
        if (to == -1)
            continue;
        if (arr[1].states[second][sym] == -1)
            return false;
        if (!visited[to]) {
            result = result && dfs(to, arr[1].states[second][sym]);
        }
    }
    return result;
}

int main() {
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);
    int n, m, k, pos, from, to;
    char sym;
    for (int i = 0; i < 2; i++) {
        scanf("%d %d %d", &n, &m, &k);
        arr.emplace_back(n, m, k);
        for (int j = 0; j < arr[i].k; j++) {
            scanf("%d", &pos);
            arr[i].setAcceptState(pos - 1);
        }

        for (int j = 0; j < arr[i].m; j++) {
            scanf("%d %d %c", &from, &to, &sym);
            arr[i].addTransition(from - 1, to - 1, (int) (sym - 'a'));
        }
    }
    visited.resize(arr[0].n, false);
    if (dfs(0, 0)) {
        printf("YES");
    } else
        printf("NO");
    return 0;
}