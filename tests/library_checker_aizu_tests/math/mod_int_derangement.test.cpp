#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "montmort_number_mod"
#include "../template.hpp"

// trick to remove const so I can use arbitrary
// prime mode here
#define const ;
#include "../../../library/math/mod_int.hpp"
#undef const

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n >> mod;
  vector<mint> dp(n + 1);
  dp[0] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = (dp[i - 1] + dp[i - 2]) * (i - 1);
  for (int i = 1; i <= n; i++)
    cout << dp[i].x << " ";
  cout << '\n';
  return 0;
}
