#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include "../template.hpp"

#include "../../../library/data_structures/binary_trie/binary_trie.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  {
    binary_trie<int64_t> bt_ll;
    assert(bt_ll.mx_bit == 62);
    bt_ll.update(61238612412983LL, 5);
    int cnt = bt_ll.count(61238612412983LL);
    assert(cnt == 5);
    cnt = bt_ll.count(54289162783746217LL);
    assert(cnt == 0);
    int64_t res = bt_ll.walk(54289162783746217LL);
    assert(res == 61238612412983LL);
  }
  binary_trie<int> bt_int;
  assert(bt_int.mx_bit == 30);
  while (q--) {
    int type, x;
    cin >> type >> x;
    if (type == 0) {
      if (bt_int.count(x) == 0)
        bt_int.update(x, 1);
    } else if (type == 1) {
      if (bt_int.count(x) == 1)
        bt_int.update(x, -1);
    } else {
      assert(type == 2);
      int val = bt_int.walk(x);
      cout << (val ^ x) << '\n';
    }
  }
  return 0;
}
