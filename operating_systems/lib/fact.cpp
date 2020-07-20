#include"fact.hpp"

long long fact(int n) {
    if (n < 0) {
        return -1; 
    }
    long long out = 1;
    for (long long i = 2; i <= n; i++) {
        out *= i;
    }
    return out;
}