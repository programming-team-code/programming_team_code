#pragma once
#include "is_palindrome.hpp"
//! https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/manacher.cpp
//! @code
//!   auto r = longest_from_index(pq);
//! @endcode
//! r[i] = max index such that [i, r[i]]
//!   is a palindrome
//! @time O(n)
//! @space O(n)
template<class T> vi longest_from_index(pal_query<T>& pq) {
  int n = (sz(pq.man) + 1) / 2;
  vector longest(n, n - 1);
  for (int i = n - 2; i >= 0; i--) {
    longest[i] = min(longest[i + 1] + 1, n - 1);
    while (!pq.is_pal(i, longest[i])) longest[i]--;
  }
  return longest;
}
