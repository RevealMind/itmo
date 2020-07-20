#include"binpow.hpp"

int binpow(int a, int n) {
    if (n < 0) {
        return -1;
    }
    int out = 1LL;
    while (n) {
        if (n & 1) {
            out *= a;
        }
        a *= a;
        n >>= 1;
    }
    return out;
}