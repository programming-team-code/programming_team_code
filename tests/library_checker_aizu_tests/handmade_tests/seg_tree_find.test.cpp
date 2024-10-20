#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/bit.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"
const int mx_n = 100'000;
int rv(int i) { return mx_n - i - 1; }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  BIT bit(mx_n);
  seg_tree seg(mx_n), rev(mx_n);
  for (int i = 0; i < mx_n; i++)
    bit.update(i, 1), seg.update(i, i + 1, 1),
      rev.update(i, i + 1, 1);
  for (int q = 0; q < 100'000; q++) {
    int i = rnd(0, mx_n - 1);
    int add = rnd(0, 100'000);
    bit.update(i, add);
    seg.update(i, i + 1, add);
    rev.update(rv(i), rv(i) + 1, add);
    int l = rnd(0, mx_n - 1);
    int r = rnd(l + 1, mx_n);
    int64_t in_tree = seg.query(l, r);
    auto sum = rnd<int64_t>(1, in_tree);
    int64_t need;
    vector<array<int, 3>> rngs;
    auto reset = [&] {
      need = sum;
      rngs = {};
    };
    auto f = [&](int64_t x, int tl, int tr) -> bool {
      if (x < need) {
        rngs.push_back({tl, tr, 0});
        need -= x;
        return 0;
      }
      rngs.push_back({tl, tr, 1});
      return 1;
    };
    int pos = min(bit.lower_bound(bit.query(l) + sum), r);
    reset();
    assert(pos == seg.find_first(l, r, f));
    assert(!empty(rngs));
    assert(rngs[0][0] == l);
    for (auto [tl, tr, _] : rngs)
      assert(l <= tl && tl < tr && tr <= r);
    for (int it = 1; it < sz(rngs); it++) {
      auto [prv_le, prv_ri, prv] = rngs[it - 1];
      auto [cur_le, cur_ri, cur] = rngs[it];
      if (prv) assert(cur_le == prv_le && cur_ri < prv_ri);
      else assert(cur_le == prv_ri);
    }
    sort(begin(rngs), end(rngs));
    assert(unique(begin(rngs), end(rngs)) == end(rngs));
    reset();
    assert(
      pos == rv(rev.find_last(rv(r - 1), rv(l) + 1, f)));
    assert(!empty(rngs));
    assert(rngs[0][1] == rv(l) + 1);
    for (auto [tl, tr, _] : rngs)
      assert(
        rv(r - 1) <= tl && tl < tr && tr <= rv(l) + 1);
    for (int it = 1; it < sz(rngs); it++) {
      auto [prv_le, prv_ri, prv] = rngs[it - 1];
      auto [cur_le, cur_ri, cur] = rngs[it];
      if (prv) assert(cur_ri == prv_ri && cur_le > prv_le);
      else assert(prv_le == cur_ri);
    }
    sort(begin(rngs), end(rngs));
    assert(unique(begin(rngs), end(rngs)) == end(rngs));
  }
  cout << "Hello World\n";
  return 0;
}
