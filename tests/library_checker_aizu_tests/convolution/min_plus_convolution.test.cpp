#define PROBLEM \
  "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"
#include "../template.hpp"
#include "../../../library/convolution/min_plus_convolution_convex_and_arbitrary.hpp"
istream& operator>>(istream& is, vi& v) {
  for (int& e : v) is >> e;
  return is;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  vi convex(n), arbitrary(m);
  cin >> convex >> arbitrary;
  auto res = min_plus(convex, arbitrary);
  for (int r : res) cout << r << ' ';
  cout << '\n';
  return 0;
}
