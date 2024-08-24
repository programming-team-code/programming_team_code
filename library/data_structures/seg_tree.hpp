/** @file */
#pragma once
template <class T, class F> struct tree {
  int n;
  vector<T> s;
  T unit;
  F f;
  tree(int n, T unit, F f) : n(n), s(2 * n, unit), unit(unit), f(f) {}
#include "seg_tree_uncommon/tree_vector_constructor.hpp"
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};
