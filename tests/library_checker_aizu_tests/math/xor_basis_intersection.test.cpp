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
void check_condition_ordered(
  const basis_ordered<int>& basis2,
  const basis_ordered<ll>& basis3,
  const basis_ordered<bitset<lg>>& basis4) {
  int or_bits2 = 0;
  ll or_bits3 = 0;
  bitset<lg> or_bits4 = 0;
  for (int i = 0; i < lg; i++) {
    assert(
      (bit_floor(uint64_t(basis2.b[i])) & or_bits2) == 0);
    assert(
      (bit_floor(uint64_t(basis3.b[i])) & or_bits3) == 0);
    assert((bit_floor(uint64_t(basis4.b[i].to_ullong())) &
             or_bits4.to_ullong()) == 0);
    or_bits2 |= basis2.b[i];
    or_bits3 |= basis3.b[i];
    or_bits4 |= basis4.b[i];
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
    basis_ordered<int> basis2;
    basis_ordered<ll> basis3;
    basis_ordered<bitset<lg>> basis4;
    for (int i = 0; i < n; i++) {
      int val;
      cin >> val;
      assert(basis1.insert(val));
      assert(!basis1.insert(val));
      assert(basis2.insert(val));
      assert(!basis2.insert(val));
      assert(basis3.insert(val));
      assert(!basis3.insert(val));
      assert(basis4.insert(val));
      assert(!basis4.insert(val));
    }
    check_condition_unordered(basis1);
    check_condition_ordered(basis2, basis3, basis4);
    int m;
    cin >> m;
    basis basis5;
    basis_ordered<int> basis6;
    basis_ordered<ll> basis7;
    basis_ordered<bitset<lg>> basis8;
    for (int j = 0; j < m; j++) {
      int val;
      cin >> val;
      assert(basis5.insert(val));
      assert(!basis5.insert(val));
      assert(basis6.insert(val));
      assert(!basis6.insert(val));
      assert(basis7.insert(val));
      assert(!basis7.insert(val));
      assert(basis8.insert(val));
      assert(!basis8.insert(val));
    }
    check_condition_unordered(basis5);
    check_condition_ordered(basis6, basis7, basis8);
    basis inter = intersection(basis1, basis5);
    check_condition_unordered(inter);
    cout << sz(inter.b) << " ";
    for (int val : inter.b) cout << val << " ";
    cout << '\n';
  }
  return 0;
}
