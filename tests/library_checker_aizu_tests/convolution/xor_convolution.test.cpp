#define PROBLEM \
  "https://judge.yosupo.jp/problem/bitwise_xor_convolution"
#include "../template.hpp"
#include "../../../library/convolution/xor_convolution.hpp"
istream& operator>>(istream& is, vector<int>& v) {
  for (int i = 0; i < sz(v); i++) is >> v[i];
  return is;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vi a(1 << n), b(1 << n);
  cin >> a >> b;
  vi c = xor_conv(a, b);
  for (int i = 0; i < (1 << n); i++) cout << c[i] << ' ';
  cout << '\n';
  return 0;
}
