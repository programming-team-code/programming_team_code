#define PROBLEM \
  "https://judge.yosupo.jp/problem/set_xor_min"
#include "../template.hpp"
#include "../../../library/strings/binary_trie.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  {
    binary_trie bt;
    bt.update(61238612412983LL, 5);
    assert(
      bt.walk(54289162783746217LL) == 61238612412983LL);
  }
  binary_trie bt;
  bt.update(0, 0);
  while (q--) {
    int type, x;
    cin >> type >> x;
    if (type == 0) {
      if (
        bt.t[bt.t[0].next[0]].siz == 0 || bt.walk(x) != x)
        bt.update(x, 1);
    } else if (type == 1) {
      if (bt.t[bt.t[0].next[0]].siz > 0 && bt.walk(x) == x)
        bt.update(x, -1);
    } else {
      assert(type == 2);
      int val = bt.walk(x);
      cout << (val ^ x) << '\n';
    }
  }
  return 0;
}
