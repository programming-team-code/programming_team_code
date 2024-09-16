#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "predecessor_problem"
#include "../template.hpp"

#include "../../../library/data_structures/bit.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  string s;
  cin >> n >> q >> s;
  vector<int> init(n);
  for (int i = 0; i < n; i++) init[i] = s[i] - '0';
  BIT<int> bit(init);
  seg_tree st(init);
  while (q--) {
    int type, k;
    cin >> type >> k;
    if (type == 0) {
      if (bit.query(k, k + 1) == 0) {
        bit.update(k, 1);
        st.update(k, k + 1, 1);
      }
    } else if (type == 1) {
      if (bit.query(k, k + 1) == 1) {
        bit.update(k, -1);
        st.update(k, k + 1, -1);
      }
    } else if (type == 2) {
      int res = bit.query(k, k + 1);
      auto res_st = st.query(k, k + 1);
      assert(res == res_st);
      cout << res << '\n';
    } else if (type == 3) {
      if (bit.query(k, k + 1) == 1) {
        cout << k << '\n';
        continue;
      }
      int order = bit.query(k);
      int need = order + 1;
      auto f = [&](int64_t x, int tl,
                 int tr) -> bool {
        assert(tl <= tr);
        if (x < need) {
          need -= x;
          return 0;
        }
        return 1;
      };
      int res = bit.lower_bound(order + 1);
      assert(res == st.find_first(0, n, f));
      assert(
        res == st.find_first(k, n,
                 [&](int64_t x, int, int) -> bool {
        return x > 0;
      }));
      if (res == n) res = -1;
      cout << res << '\n';
    } else {
      if (bit.query(k, k + 1) == 1) {
        cout << k << '\n';
        continue;
      }
      int order = bit.query(k);
      int need = order;
      auto f = [&](int64_t x, int tl,
                 int tr) -> bool {
        assert(tl <= tr);
        if (x < need) {
          need -= x;
          return 0;
        }
        return 1;
      };
      int res = bit.lower_bound(order);
      assert(max(res, 0) == st.find_first(0, n, f));
      assert(
        res == st.find_last(0, k + 1,
                 [&](int64_t x, int, int) -> bool {
        return x > 0;
      }));
      cout << res << '\n';
    }
  }
  return 0;
}
