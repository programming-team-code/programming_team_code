#define PROBLEM \
  "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/data_structures/bit_uncommon/rupq.hpp"
#include "../../../library/data_structures/bit_uncommon/rurq.hpp"
#include "../../../library/data_structures/lazy_seg_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<ll> arr(n);
  vector<int> arr_int(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    arr_int[i] = int(arr[i]);
  }
  BIT bit(arr);
  seg_tree st(arr_int);
  bit_rurq bit_rr(arr);
  vector<ll> suf_sum(n);
  partial_sum(rbegin(arr), rend(arr), rbegin(suf_sum));
  bit_rupq bit_i(suf_sum);
  for (int i = 0; i < n; i++) {
    assert(arr[i] == bit.query(i, i + 1));
    assert(bit_i.get_index(i) == bit.query(i, n));
    assert(bit_i.get_index(i) == suf_sum[i]);
  }
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int p, x;
      cin >> p >> x;
      bit.update(p, x);
      st.update(p, p + 1, x);
      bit_rr.update(p, p + 1, x);
      bit_i.update(0, p + 1, x);
    } else {
      int l, r;
      cin >> l >> r;
      ll res = bit.query(l, r);
      {
        ll bit_i_result = bit_i.get_index(l);
        if (r < n) bit_i_result -= bit_i.get_index(r);
        assert(res == bit_i_result);
      }
      assert(res == bit_rr.query(l, r));
      cout << res << '\n';
    }
    auto sum = rnd<ll>(0LL, (ll)(1e12));
    auto need = sum;
    auto f = [&](ll x, int tl, int tr) -> bool {
      assert(tl <= tr);
      if (x < need) {
        need -= x;
        return 0;
      }
      return 1;
    };
    assert(bit.lower_bound(sum) == st.find_first(0, n, f));
  }
  return 0;
}
