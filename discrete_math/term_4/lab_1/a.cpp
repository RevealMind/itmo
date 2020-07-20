#include <iostream>
#include <vector>

using std::vector;

static const int64_t MOD = 998244353LL;
static const size_t MAXN = 2000;

void init(vector<int64_t> & vec, int border) {
  for (int i = 0; i < border; ++i) {
    std::cin >> vec[i];
  }
}
/*
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  int n, m;

  std::cin >> n >> m;

  int sumDegree = std::max(n, m);
  int powDegree = n + m;
  int divDegree = 1000;
  vector<int64_t> p(MAXN + 1, 0);
  vector<int64_t> q(MAXN + 1, 0);
  vector<int64_t> q_inverse(MAXN + 1, 0);

  init(p, n + 1);
  init(q, m + 1);

  //---- A + B ----

  std::cout << sumDegree << "\n";
  for (int i = 0; i <= sumDegree; i++) {
    std::cout << (p[i] + q[i]) % MOD << " ";
  }
  std::cout << "\n";

  //---- A * B ----

  std::cout << powDegree << "\n";
  for (int k = 0; k <= powDegree; k++) {
    int64_t sum_k = 0;
    for (int i = 0; i <= k; i++) {
      sum_k = (sum_k + p[i] * q[k - i]) % MOD;
    }
    std::cout << sum_k << " ";
  }
  std::cout << "\n";

  //---- A / B ----

  q_inverse[0] = 1;
  for (int k = 1; k < divDegree; k++) {
    int64_t sum_k = 0;
    for (int i = 1; i <= k; i++) {
      sum_k = (sum_k + q[i] * q_inverse[k - i] + MOD) % MOD;
    }
    q_inverse[k] = (-sum_k + MOD) % MOD;
  }

  for (int k = 0; k < divDegree; k++) {
    int64_t sum_k = 0;
    for (int i = 0; i <= k; i++) {
      sum_k = (sum_k + p[i] * q_inverse[k - i]) % MOD;
    }
    std::cout << sum_k << " ";
  }

  return 0;
}
*/