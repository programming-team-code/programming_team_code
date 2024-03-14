#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"
#include "../template.hpp"

#include "../../../library/convolution/lcm_convolution.hpp"

istream& operator>>(istream& is, vector<int>& v) {
  for (int i = 1; i < ssize(v); i++)
    is >> v[i];
  return is;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n + 1), b(n + 1);
  cin >> a >> b;
  auto c = lcm_convolution(a, b);
  for (int i = 1; i <= n; i++)
    cout << c[i] << ' ';
  cout << '\n';
  return 0;
}
