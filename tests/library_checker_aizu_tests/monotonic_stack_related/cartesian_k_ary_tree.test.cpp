#define PROBLEM \
  "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "../../../library/monotonic_stack/cartesian_k_ary_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vi a(n);
  rep(i, 0, n) cin >> a[i];
  mono_st_asserts(a);
  auto l = mono_st(a, less()), r = mono_range(l),
       p = cart_k_ary_tree(a, l);
  assert(*ranges::min_element(p) == -1);
  assert(*ranges::max_element(p) < n);
  vi a_neg(n);
  ranges::transform(a, begin(a_neg),
    [](int x) { return -x; });
  auto le_neg = mono_st(a_neg, greater()),
       ri_neg = mono_range(le_neg),
       p_neg = cart_k_ary_tree(a_neg, le_neg);
  assert(r == ri_neg);
  assert(p == p_neg);
  rep(i, 0, n) {
    if (p[i] != -1)
      assert(a[p[i]] < a[i]); // because distinct numbers
    cout << (p[i] == -1 ? i : p[i]) << " ";
  }
  return 0;
}
