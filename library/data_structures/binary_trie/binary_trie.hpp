#pragma once
//! @code
//!   binary_trie<int> bt1; //mx_bit = 30
//!   binary_trie<ll> bt2; //mx_bit = 62
//! @endcode
//! @time O(mx_bit)
//! @space O(1)
template<class T> struct binary_trie {
  int mx_bit;
  struct node {
    int sub_sz = 0;
    array<int, 2> next = {-1, -1};
  };
  vector<node> t;
  binary_trie(): mx_bit(8 * sizeof(T) - 2), t(1) {}
  void update(T num, int delta) {
    t[0].sub_sz += delta;
    for (int v = 0, bit = mx_bit; bit >= 0; bit--) {
      bool b = (num >> bit) & 1;
      if (t[v].next[b] == -1) {
        t[v].next[b] = sz(t);
        t.emplace_back();
      }
      v = t[v].next[b];
      t[v].sub_sz += delta;
    }
  }
#include "count.hpp"
#include "walk.hpp"
};
