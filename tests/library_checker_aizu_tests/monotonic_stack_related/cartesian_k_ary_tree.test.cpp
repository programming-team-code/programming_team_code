#define PROBLEM \
  "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/monotonic_stack/cartesian_k_ary_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  mono_st_asserts(a);
  auto le = mono_st(a, less()), ri = mono_range(le),
       p = cart_k_ary_tree(a, le);
  assert(*min_element(begin(p), end(p)) == -1);
  assert(*max_element(begin(p), end(p)) < n);
  vector<int> a_neg(n);
  transform(begin(a), end(a), begin(a_neg),
            [](int x) { return -x; });
  auto le_neg = mono_st(a_neg, greater()),
       ri_neg = mono_range(le_neg),
       p_neg = cart_k_ary_tree(a_neg, le_neg);
  assert(ri == ri_neg);
  assert(p == p_neg);
  for (int i = 0; i < n; i++) {
    if (p[i] != -1)
      assert(a[p[i]] < a[i]);  // because distinct numbers
    cout << (p[i] == -1 ? i : p[i]) << " ";
  }
  return 0;
}
