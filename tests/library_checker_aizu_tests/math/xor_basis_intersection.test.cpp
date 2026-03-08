#define PROBLEM \
  "https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces"
#include "../template.hpp"
#include "../../../library/math/matrix_related/xor_basis_unordered_intersection.hpp"
#include "../../../library/math/matrix_related/xor_basis_ordered.hpp"
// checking the condition: for 0 <= i < j < sz(b):
// (bit_floor(b[i]) & b[j]) == 0
void check_condition_unordered(const basis& b) {
  int n = sz(b.b);
  int or_bits = 0;
  for (int i = n - 1; i >= 0; i--) {
    int bit_i = bit_floor(unsigned(b.b[i]));
    assert((bit_i & or_bits) == 0);
    or_bits |= b.b[i];
  }
}
const int B = 30;
void check_condition_ordered(const xor_basis<B>& basis2) {
  bitset<B> or_bits2;
  for (int i = 0; i < B; i++) {
    assert(basis2.basis[i].none() ||
      bit_floor(basis2.basis[i].to_ulong()) ==
        (1ULL << i));
    assert((bit_floor(basis2.basis[i].to_ulong()) &
             or_bits2.to_ulong()) == 0);
    or_bits2 |= basis2.basis[i];
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    basis basis1;
    xor_basis<B> basis2;
    for (int i = 0; i < B; i++)
      assert(basis2.basis[i].none());
    for (int i = 0; i < n; i++) {
      int val;
      cin >> val;
      bitset<B> v = val;
      assert(basis1.insert(val));
      assert(!basis1.insert(val));
      assert(basis2.insert(v));
      assert(!basis2.insert(v));
    }
    check_condition_unordered(basis1);
    check_condition_ordered(basis2);
    int m;
    cin >> m;
    basis basis3;
    xor_basis<B> basis4;
    for (int j = 0; j < m; j++) {
      int val;
      cin >> val;
      bitset<B> v = val;
      assert(basis3.insert(val));
      assert(!basis3.insert(val));
      assert(basis4.insert(v));
      assert(!basis4.insert(v));
    }
    check_condition_unordered(basis3);
    check_condition_ordered(basis4);
    basis inter = intersection(basis1, basis3);
    check_condition_unordered(inter);
    cout << sz(inter.b) << " ";
    for (int val : inter.b) cout << val << " ";
    cout << '\n';
  }
  return 0;
}
