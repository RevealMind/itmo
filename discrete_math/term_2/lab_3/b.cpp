#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

inline bool is_letter(char c, bool is_small) {
    return is_small ? ('a' <= c && c <= 'z') : ('A' <= c && c <= 'Z');
}

int main() {
    //--------------------КАК ЖЕ ГОРИИИИИТ----------------
    std::ios_base::sync_with_stdio(0);
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);
    //----------------------------------------------------

    int n;
    char start;
    std::cin >> n >> start;

    std::string rule;
    std::getline(std::cin, rule);

    std::vector<std::vector<int>> concerned_rules(26);
    std::vector<std::pair<int, int>> counter(n);
    std::queue<int> q;
    std::vector<bool> isEpsilon(26), use(26);

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, rule);
        if (rule == "")
            continue;
        int left = rule[0] - 'A';
        counter[i].first = left;
        //counter[i].second = 0;
        for (int j = 5; j < rule.size(); j++) {
            if (is_letter(rule[j], false) || is_letter(rule[j], true)) {
                if (is_letter(rule[j], false))
                    concerned_rules[rule[j] - 'A'].push_back(i);
                counter[i].second++;
            }
        }

        if (rule.size() == 4 || !(is_letter(rule[5], false) || is_letter(rule[5], true))) {
            q.push(left);
            isEpsilon[left] = true;
        }
    }


    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (use[cur])
            continue;
        use[cur] = true;
        for (auto x : concerned_rules[cur]) {
            counter[x].second--;
            if (counter[x].second == 0) {
                q.push(counter[x].first);
                isEpsilon[counter[x].first] = true;
            }
        }
    }

    for (int i = 0; i < isEpsilon.size(); ++i)
        if (isEpsilon[i])
            std::cout << char('A' + i) << " ";

    return 0;

}