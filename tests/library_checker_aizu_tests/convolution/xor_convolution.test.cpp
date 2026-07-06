#define PROBLEM \
  "https://judge.yosupo.jp/problem/bitwise_xor_convolution"
#include "../template.hpp"
#include "../../../library/convolution/xor_convolution.hpp"
istream& operator>>(istream& is, vi& v) {
  rep(i, 0, sz(v)) is >> v[i];
  return is;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vi a(1 << n), b(1 << n);
  cin >> a >> b;
  vi c = xor_conv(a, b);
  rep(i, 0, (1 << n)) cout << c[i] << ' ';
  cout << '\n';
  return 0;
}
