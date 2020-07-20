#include <iostream>
#include <bits/stdc++.h>

int main() {
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
    std::string word;
    std::cin >> word;
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<std::unordered_set<int> >> states(n, std::vector<std::unordered_set<int> >('z' - 'a' + 1));

    std::vector<bool> acceptedStates(n, false);
    for (int i = 0; i < k; i++) {
        int pos;
        std::cin >> pos;
        acceptedStates[pos - 1] = true;
    }

    for (int i = 0; i < m; i++) {
        int from, to;
        char symbol;
        std::cin >> from >> to >> symbol;
        states[from - 1][(int)symbol - 'a'].insert(to - 1);
    }

    std::unordered_set<int> current;
    current.insert(0);
    for (int i = 0; i < word.size(); i++) {
        std::unordered_set<int> next;
        for (const int &from: current) {
            next.insert(states[from][(int)word[i] - 'a'].begin(), states[from][(int)word[i] - 'a'].end());
        }
        current = next;
        if(current.empty()) {
            std::cout << "Rejects";
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        std::unordered_set<int>::const_iterator got = current.find (i);
        std::unordered_set<int>::const_iterator e = current.end();
        if (current.find (i) != current.end())
            if(acceptedStates[i]) {
                std::cout << "Accepts";
                return 0;
            }
    }
    std::cout << "Rejects";
    return 0;
}