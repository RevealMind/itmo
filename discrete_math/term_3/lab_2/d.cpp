#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

using std::vector;
using namespace boost;

//a class to hold the coordinates of the straight line embedding
struct coord_t
{
    std::size_t x;
    std::size_t y;
};


vector<int> check_k33{ 4060, 13242, 15481, 15751, 21878, 23221, 23371, 26323, 26413, 26862}; // all masks of k33 graph with 6 vertexes
vector<int> check_k5{ 5871, 11127, 19899, 29149, 32286, 32736};                             // all masks of k5 graph with 6 vertexes

int mask_to_int(std::string &mask) {
    int ans = 0;
    for (auto c : mask) {
        ans <<= 1;
        if (c == '1')
            ans += 1;
    }
    return ans;
}
bool hard_check_k5(std::string mask) {
    vector<int> deg(6, 0);
    int cur = 0;
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < i; j++) {
            if (mask[cur] == '1') {
                deg[i]++;
                deg[j]++;
            }
            cur++;
        }
    }

    int counter = 0;
    for(auto v : deg) {
        if (v == 4) 
            counter++;
    }
    if (counter == 5) {
        return true;
    }  else
        return false;
}

bool chek_k5_or_k33(int mask) {
    for (int check_mask : check_k5) {
        if ((check_mask & mask) == check_mask)
            return true;
    }
    for (int check_mask : check_k33) {
        if ((check_mask & mask) == check_mask)
            return true;
    }
    return false;
}

void boost_foo(std::string mask, int size, bool &flag);

void solve() {
    int t;
    bool flag, flag1;
    std::string mask, tmp;
    std::getline(std::cin, tmp);
    t = atoi(tmp.c_str());
    for (int i = 0; i < t; ++i) {
        std::getline(std::cin, mask);
        size_t size = mask.size();
        boost_foo(mask, 6, flag);
        if (size < 10) { // less then 5 vertex
            //std::cout << "YES\n";
        } else if (size == 10) {  // when 5 vertex
            if (mask_to_int(mask) == 1023) { // 1111111111 -- K_{5}
                //std::cout << "NO\n";
            } else {
                //std::cout << "YES\n";
            }
        } else if (size == 15) { // when 6 vertex
            if (chek_k5_or_k33(mask_to_int(mask))) {
                flag1 = false;//std::cout << "NO\n";
            } else {
                flag1 = true;//std::cout << "YES\n";
            }
        }
        if (flag != flag1) {
            std::cout << "Error in mask: " << mask << "\n";
            std::cout << "Expected: ";
            if (flag)
                std::cout << "YES";
            else
                std::cout << "NO";
            std::cout << "\n";
        }
    }
}

void boost_foo(std::string mask, int size, bool &flag) {
    typedef adjacency_list<vecS,
            vecS,
            undirectedS,
            property<vertex_index_t, int>
    > graph;

    graph g(size);
    int k = 0;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (mask[k] == '1') {
                add_edge(i, j, g);
            }
            k++;
        }
    }


    if (boyer_myrvold_planarity_test(g))
        flag = true;//std::cout << "YES --- ";
    else
        flag = false;//std::cout << "NO --- ";
}
int main() {
    freopen("planaritycheck.in", "r", stdin);
    freopen("planaritycheck.out", "w", stdout);
    solve();

    return 0;
}


