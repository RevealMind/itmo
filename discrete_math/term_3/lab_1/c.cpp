#include <iostream>
#include <list>

using std::list;
using std::string;
list<int> ans;

void bin_search(int left, int right, int key) {
    while (right - left > 1) {
        int middle_pos = (right + left) / 2;
        list<int>::iterator middle = ans.begin();
        std::advance(middle, middle_pos);
        std::cout << "1 "  <<  *middle << " " << key << "\n";
        std::cout.flush();
        string out;
        std::cin >> out;
        if (out == "YES") {
            left = middle_pos;
        } else
            right = middle_pos;
    }
    list<int>::iterator position = ans.begin();
    std::advance(position, right);
    ans.insert(position, key);
}
int main() {
    int n;
    std::cin >> n;
    ans.push_back(1);
    for (int i = 2; i <= n; i++) {
        bin_search(-1, i - 1, i);
    }
    std::cout << "0 ";
    for (int out : ans) {
        std::cout << out << " ";
    }
    return 0;
}