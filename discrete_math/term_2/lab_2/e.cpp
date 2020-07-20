#include <bits/stdc++.h>


using namespace std;

vector<vector<vector<long long>>> NFAstates;
vector<vector<long long> > DFAstates;
vector<int> acceptNFAStates;
vector<int> acceptDFAStates;
vector<vector<long long> > E;
int n, l, ind = 0;
const int MOD = 1000000007;
const int ALPHABET = 'z' - 'a' + 1;
const int MAX_STATES = 100;


inline vector<vector<long long> > multiply(vector<vector<long long> > &a, vector<vector<long long> > &b) {
    vector<vector<long long> > tmp(MAX_STATES, vector<long long>(MAX_STATES, 0));
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_STATES; j++) {
            for (int k = 0; k < MAX_STATES; k++) {
                tmp[i][j] += a[i][k] * b[k][j];
                tmp[i][j] %= MOD;
            }
        }
    }
    return tmp;
}

inline vector<vector<long long> > binpow(vector<vector<long long> > &states, int n) {
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

inline void print(vector<vector<long long> > &ans) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
}

inline void init() {
    int m, k;
    scanf("%d %d %d %d", &n, &m, &k, &l);
    DFAstates.resize(MAX_STATES, std::vector<long long> (MAX_STATES, 0));
    NFAstates.resize(n, vector<vector<long long> >(ALPHABET));
    E.resize(MAX_STATES, vector<long long>(MAX_STATES, 0));
    for (int i = 0; i < MAX_STATES; i++) {
        E[i][i] = 1;
    }

    int pos;
    for (int i = 0; i < k; ++i) {
        scanf("%d", &pos);
        acceptNFAStates.push_back(pos - 1);
    }

    int from, to;
    char sym;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %c", &from, &to, &sym);
        NFAstates[from - 1][(int)(sym - 'a')].push_back(to - 1);
    }
}

inline void printResult() {
    vector<vector<long long> > ans = binpow(DFAstates, l);
    long long result = 0;
    for (int i = 0; i < acceptDFAStates.size(); i++) {
        result += ans[0][acceptDFAStates[i]];
    }
    result %= MOD;
    printf("%lld", result);
}

int main() {
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
    init();
    queue<set<int> > arr;
    set<set<int> > useSet;
    map<set<int>, int> mapT;
    arr.push({0});
    useSet.insert({0});
    mapT[{0}] = ind++;
    for (int i = 0; i < acceptNFAStates.size(); ++i) {
        if (acceptNFAStates[i] == 0)
            acceptDFAStates.push_back(0);
    }
    while (!arr.empty()) {
        set<int> cur_set = arr.front();
        arr.pop();
        for (int sym = 0; sym < ALPHABET; ++sym) {
            set<int> new_set;
            for (auto from : cur_set) {
                for (auto to : NFAstates[from][sym]) {
                    new_set.insert(to);
                }
            }
            if (new_set.empty())
                continue;

            if (useSet.count(new_set) == 0) {
                arr.push(new_set);
                useSet.insert(new_set);
                mapT[new_set] = ind++;
                for (int i = 0; i < acceptNFAStates.size(); i++) {
                    if (new_set.find(acceptNFAStates[i]) != new_set.end()) {
                        acceptDFAStates.push_back(mapT[new_set]);
                        break;
                    }
                }
            }
            DFAstates[mapT[cur_set]][mapT[new_set]]++;
        }
    }
    printResult();
    return 0;
}