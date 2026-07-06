#define PROBLEM \
  "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"
#include "../../../library/monotonic_stack/cartesian_binary_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  auto l = mono_st(a, less()), p = cart_binary_tree(l);
  rep(i, 0, n) cout << (p[i] == -1 ? i : p[i]) << " ";
  return 0;
}
