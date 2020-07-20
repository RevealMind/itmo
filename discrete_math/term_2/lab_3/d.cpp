#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

int main() {
    const int mod = 1000000007;
    std::ios_base::sync_with_stdio(0);
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);
    int n;
    char start;
    std::cin >> n >> start;
    std::vector<std::pair<char, char>> term;
    std::vector<std::pair<char, std::string>> not_term;
    std::string word;

    for (int i = 0; i < n; i++) {
        std::string left, arrow, right;

        std::cin >> left >> arrow >> right;

        if (right.size() == 1) {
            term.push_back(std::make_pair(left[0], right[0]));
        } else {
            not_term.push_back(std::make_pair(left[0], right));
        }

    }

    std::cin >> word;
    std::vector<std::vector<std::vector<long long>>> dp(26, std::vector<std::vector<long long>>(word.size(),
                                                                                                std::vector<long long>(
                                                                                                        word.size())));

    for (int i = 0; i < word.size(); i++) {
        for (auto x = term.begin(); x != term.end(); x++) {
            if (x->second == word[i])
                dp[x->first - 'A'][i][i] = true;
        }
    }

    for (int len = 1; len < word.size(); len++) {
        for (int i = 0; i < word.size() - len; i++) {
            for (int k = 0; k < len; k++) {
                for (auto x = not_term.begin(); x != not_term.end(); ++x) {
                    dp[x->first - 'A'][i][i + len] = (dp[x->first - 'A'][i][i + len] + dp[x->second[0] - 'A'][i][i + k] * dp[x->second[1] - 'A'][i + k + 1][i + len]) % mod;
                }
            }
        }
    }

    std::cout << (dp[start - 'A'][0][word.size() - 1] % mod);
    return 0;
}