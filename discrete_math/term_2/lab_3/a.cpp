#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>

bool accepted(char cur, int cur_pos, std::string &word, std::unordered_map<char, std::vector<std::string>> ksg) {
    if (cur_pos == word.length()) {
        return false;
    }
    bool answer = false;
    for (auto prod : ksg[cur]) {
        if (prod.length() == 1) {
            answer |= (cur_pos + 1 == word.length() && word[word.length() - 1] == prod[0]);
        } else {
            if (prod[0] == word[cur_pos]) {
                answer |= accepted(prod[1], cur_pos + 1, word, ksg);
            }
        }
    }
    return answer;
}

int main() {
    std::string file_name = "automaton";
    std::ios_base::sync_with_stdio(false);
    std::unordered_map<char, std::vector<std::string>> ksg;

    int n;
    char start;
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
    std::cin >> n >> start;

    for (int i = 0; i < n; i++) {
        char left;
        std::string arrow, right;
        std::cin >> left >> arrow >> right;
        ksg[left].push_back(right);
    }

    int m;

    std::cin >> m;

    for (int i = 0; i < m; i++) {
        std::string word;
        std::cin >> word;
        if (accepted(start, 0, word, ksg)) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }
}