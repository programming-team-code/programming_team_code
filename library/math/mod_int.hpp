#pragma once
const int mod = 998244353;
//! https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModularArithmetic.h
//! https://codeforces.com/blog/entry/122714
struct mint {
  int x;
  mint(int xx = 0): x(xx < 0 ? xx + mod : xx) {}
  mint operator+(mint b) { return x - mod + b.x; }
  mint operator-(mint b) { return x - b.x; }
  mint operator*(mint b) { return ll(x) * b.x % mod; }
#include "mod_int_division.hpp"
};
