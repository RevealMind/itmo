#include <bits/stdc++.h>

using namespace std;

struct DFA {
    int n, m, k;
    vector<vector<int> > states;
    vector<bool> acceptStates;
    vector<bool> visited;

    DFA(int n, int m, int k) : n(n), m(m), k(k) {
        states.resize(n + 1, vector<int>('z' - 'a' + 1, 0));
        acceptStates.resize(n + 1, false);
        visited.resize(n + 1, false);
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


bool bfs() {
    queue<pair<int, int> > que;
    pair<int, int> t = make_pair(1, 1);
    que.push(t);
    arr[0].visited[1] = true;
    arr[1].visited[1] = true;
    while (!que.empty()) {
        pair<int, int> curPair = que.front();
        que.pop();
        if (curPair.first != 0)
            arr[0].visited[curPair.first] = true;
        if (curPair.second != 0)
            arr[1].visited[curPair.second] = true;
        if (arr[0].acceptStates[curPair.first] != arr[1].acceptStates[curPair.second])
            return false;
        for (int i = 0; i < 'z' - 'a' + 1; i++) {
            int u = arr[0].states[curPair.first][i];
            int v = arr[1].states[curPair.second][i];
            if (!arr[0].visited[u] || !arr[1].visited[v])
                if (v != 0 || u != 0)
                    que.push(make_pair(u, v));
        }
    }
    return true;
}

int main() {
    freopen("equivalence.in", "r", stdin);
    freopen("equivalence.out", "w", stdout);
    int n, m, k, pos, from, to;
    char sym;
    for (int i = 0; i < 2; i++) {
        scanf("%d %d %d", &n, &m, &k);
        arr.emplace_back(n, m, k);
        for (int j = 0; j < arr[i].k; j++) {
            scanf("%d", &pos);
            arr[i].setAcceptState(pos);
        }

        for (int j = 0; j < arr[i].m; j++) {
            scanf("%d %d %c", &from, &to, &sym);
            arr[i].addTransition(from, to, (int) (sym - 'a'));
        }
    }
    if (bfs()) {
        printf("YES");
    } else
        printf("NO");
    return 0;
}