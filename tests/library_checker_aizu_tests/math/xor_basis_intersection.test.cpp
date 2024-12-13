#define PROBLEM \
  "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"
#include "../template.hpp"
#include "../../../library/math/matrix_related/xor_basis_unordered_intersection.hpp"
// checking the condition: for 0 <= i < j < sz(b):
// (bit_floor(b[i]) & b[j]) == 0
void check_condition(const basis<int>& b) {
  int n = sz(b.b);
  int or_bits = 0;
  for (int i = n - 1; i >= 0; i--) {
    int bit_i = 1 << __lg(b.b[i]);
    assert((bit_i & or_bits) == 0);
    or_bits |= b.b[i];
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    basis<int> basis1;
    for (int i = 0; i < n; i++) {
      int val;
      cin >> val;
      assert(basis1.insert(val));
    }
    check_condition(basis1);
    int m;
    cin >> m;
    basis<int> basis2;
    for (int j = 0; j < m; j++) {
      int val;
      cin >> val;
      assert(basis2.insert(val));
    }
    check_condition(basis2);
    basis<int> inter = intersection<int>(basis1, basis2);
    check_condition(inter);
    cout << sz(inter.b) << " ";
    for (int val : inter.b) cout << val << " ";
    cout << '\n';
  }
  return 0;
}
