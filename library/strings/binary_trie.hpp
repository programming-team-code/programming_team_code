#pragma once
//! @code
//!   binary_trie bt;
//!   bt.update(num, 1); // insert
//!   bt.update(num, -1); // erase
//! @endcode
//! @time O(q * mx_bit)
//! @space O(q * mx_bit)
const ll mx_bit = 1LL << 60;
struct binary_trie {
  struct node {
    int siz = 0;
    array<int, 2> next = {-1, -1};
  };
  deque<node> t;
  binary_trie(): t(1) {}
  void update(ll num, int delta) {
    int v = 0;
    for (ll bit = mx_bit; bit; bit /= 2) {
      bool b = num & bit;
      if (t[v].next[b] == -1) {
        t[v].next[b] = sz(t);
        t.emplace_back();
      }
      v = t[v].next[b];
      t[v].siz += delta;
    }
  }
  ll walk(ll num) {
    int v = 0;
    ll res = 0;
    for (ll bit = mx_bit; bit; bit /= 2) {
      bool b = num & bit;
      int u = t[v].next[b];
      if (u != -1 && t[u].siz > 0) v = u, res |= num & bit;
      else v = t[v].next[!b], res |= (~num) & bit;
    }
    return res;
  }
};
