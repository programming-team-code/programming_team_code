#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/math/matrix_related/xor_basis_ordered.hpp"
const int B = 18;
vector<bitset<B>> get_all(const vector<bitset<B>>& basis) {
  int n = ssize(basis);
  vector<bitset<B>> span;
  for (int mask = 0; mask < (1 << n); mask++) {
    bitset<B> curr_xor;
    assert(curr_xor.none());
    for (int bit = 0; bit < n; bit++)
      if ((mask >> bit) & 1) curr_xor ^= basis[bit];
    span.push_back(curr_xor);
  }
  ranges::sort(span, {}, [&](const bitset<B>& x) -> long {
    return x.to_ulong();
  });
  return span;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int num_tests = 0; num_tests < 10000; num_tests++) {
    xor_basis<B> b;
    int n = rnd(1, 18);
    vector<bitset<B>> naive_basis;
    for (int i = 0; i < n; i++) {
      bitset<B> val = rnd(0, (1 << n) - 1);
      if (b.insert(val)) naive_basis.push_back(val);
      assert(b.npivot + b.nfree == i + 1);
    }
    vector<bitset<B>> fast_basis;
    for (int i = 0; i < B; i++)
      if (b.basis[i][i]) fast_basis.push_back(b.basis[i]);
    vector<bitset<B>> naive_span = get_all(naive_basis);
    vector<bitset<B>> fast_span = get_all(fast_basis);
    assert(naive_span == fast_span);
    for (int i = 0; i < ssize(naive_span); i++)
      assert(naive_span[i] == b.walk(i));
  }
  cout << "Hello World\n";
}
