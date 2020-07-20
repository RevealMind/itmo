#include<algorithm>
#include"gcd.hpp"

extern "C"
int gcd(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }

    while (b) {
        a %= b;
        int c = a;
        a = b;
        b = c;
    }

    return a;
}