#define PROBLEM \
  "https://judge.yosupo.jp/problem/number_of_subsequences"
#include "../template.hpp"
#include "../../../library/math/num_distinct_subsequences.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  const int mod = 998244353;
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  cout << (num_subsequences(arr, mod) - 1 + mod) % mod
       << '\n';
  return 0;
}
