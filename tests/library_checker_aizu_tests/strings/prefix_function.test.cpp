#define PROBLEM \
  "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/strings/prefix_function.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = sz(s);
  vi pi = prefix_function(vi(all(s)));
  // prefix -> z func conversion
  // source:
  // https://codeforces.com/blog/entry/9612#comment-217621
  vi z(n, 0);
  rep(i, 1, n) if (pi[i]) z[i - pi[i] + 1] = pi[i];
  for (int i = 1; i < n;) {
    int j, v;
    for (j = 1;
      j < z[i] && (v = min(z[j], z[i] - j)) >= z[i + j];
      j++)
      z[i + j] = v;
    i += j;
  }
  z[0] = n;
  rep(i, 0, n) cout << z[i] << " ";
  cout << '\n';
  return 0;
}
