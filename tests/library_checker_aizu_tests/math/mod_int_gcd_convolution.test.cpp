#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "gcd_convolution"
#include "../template.hpp"

#include "../../../library/math/mod_int.hpp"

istream& operator>>(istream& is, vector<int>& v) {
  for (int i = 1; i < sz(v); i++) is >> v[i];
  return is;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n + 1), b(n + 1);
  cin >> a >> b;
  n++;
  vector<mint> c(n);
  for (int g = n - 1; g >= 1; g--) {
    mint sum_a = 0, sum_b = 0;
    for (int i = g; i < n; i += g) {
      sum_a = sum_a + a[i];
      sum_b = sum_b + b[i];
      c[g] = c[g] - c[i];
    }
    c[g] = c[g] + sum_a * sum_b;
  }
  for (int i = 1; i < n; i++) cout << c[i].x << ' ';
  cout << '\n';
  return 0;
}
