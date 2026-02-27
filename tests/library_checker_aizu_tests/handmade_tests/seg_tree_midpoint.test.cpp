#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_midpoint.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n < 5000; n++) {
    auto dfs = [&](auto&& self, int tl, int tr,
                 int v) -> void {
      assert((v >= n) == ((tr - tl) == 1));
      if (v >= n) { // leaf node
        const int depth_leaf = __lg(v),
                  max_depth = __lg(2 * n - 1);
        if (tl == 0) { // left-most leaf
          assert(v == (1 << max_depth));
          assert(depth_leaf == max_depth);
        }
        assert(n <= v && v < 2 * n);
        assert(depth_leaf == max_depth ||
          depth_leaf == max_depth - 1);
        if ((n & (n - 1)) == 0)
          assert(depth_leaf == max_depth);
      } else {
        assert(1 <= v && v < n);
        if (((tr - tl) & (tr - tl - 1)) == 0)
          assert(split(tl, tr) == (tl + tr) / 2);
        {
          int pow_2 = 1 << __lg(tr - tl);
          if (tl + pow_2 < tr - pow_2 / 2) {
            assert(pow_2 != tr - tl);
            assert(pow_2 / 2 < tr - tl - pow_2 &&
              tr - tl - pow_2 < pow_2);
            assert(pow_2 <= 2 * (tr - tl - pow_2) - 1 &&
              2 * (tr - tl - pow_2) - 1 < 2 * pow_2 - 1);
            assert(__lg(pow_2) ==
                __lg(2 * ((tr - tl) - pow_2) - 1) &&
              __lg(pow_2) == __lg(2 * pow_2 - 1));
          } else if (pow_2 < tr - tl) {
            assert(pow_2 / 2 < tr - tl - pow_2 / 2 &&
              tr - tl - pow_2 / 2 <= pow_2);
            assert(
              pow_2 <= 2 * ((tr - tl) - pow_2 / 2) - 1 &&
              2 * ((tr - tl) - pow_2 / 2) - 1 <=
                2 * pow_2 - 1);
            assert(__lg(2 * (tr - tl - pow_2 / 2) - 1) ==
              __lg(2 * pow_2 - 1));
            assert(__lg(2 * ((tr - tl) - pow_2 / 2) - 1) ==
              __lg(pow_2));
            assert(__lg(pow_2) ==
              1 + __lg(2 * (pow_2 / 2) - 1));
          }
        }
        int tm = split(tl, tr);
        // in particular, this tests that split works with
        // negatives
        assert(split(tl - 1234, tr - 1234) == tm - 1234);
        assert(split(tl - 1, tr - 1) == tm - 1);
        assert(split(tl + 50, tr + 50) == tm + 50);
        self(self, tl, tm, 2 * v);
        self(self, tm, tr, 2 * v + 1);
      }
    };
    dfs(dfs, 0, n, 1);
  }
  cout << "Hello World\n";
  return 0;
}
