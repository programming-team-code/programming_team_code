/** @file */
#pragma once
/**
 * Trie on bits. Can be thought of as a multiset of integers.
 */
template <class T> struct binary_trie {
  int mx_bit;
  struct node {
    int sub_sz = 0;
    array<int, 2> next = {-1, -1};
  };
  vector<node> t;
  /**
   * @code{.cpp}
         binary_trie<int> bt; //mx_bit = 30
         binary_trie<ll> bt; //mx_bit = 62
   * @endcode
   */
  binary_trie() : mx_bit(8 * sizeof(T) - 2), t(1) {}
  /**
   * @param num integer
   * @param delta 1 to insert num, -1 to remove num
   * @time O(mx_bit)
   * @space O(mx_bit) new nodes are pushed back onto `t`
   */
  void update(T num, int delta) {
    t[0].sub_sz += delta;
    for (int u = 0, bit = mx_bit; bit >= 0; bit--) {
      bool b = (num >> bit) & 1;
      if (t[u].next[b] == -1) {
        t[u].next[b] = sz(t);
        t.emplace_back();
      }
      u = t[u].next[b];
      t[u].sub_sz += delta;
    }
  }
#include "count.hpp"
#include "walk.hpp"
};
