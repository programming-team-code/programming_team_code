/** @file */
#pragma once
#include "count_paths_rectangle.hpp"
vl divide_and_conquer(vl h, vl bottom) {
  assert(sz(h) == sz(bottom) && is_sorted(all(h)) && !empty(h) && h[0] >= 0);
  {
    int start = find_if(all(h), [](ll x) { return x; }) - begin(h);
    h.erase(begin(h), begin(h) + start);
    bottom.erase(begin(bottom), begin(bottom) + start);
  }
  int n = sz(h);
  if (n == 0) return {};
  if (n == 1) return vl(h[0], bottom[0]);
  int mid = n / 2;
  auto left = divide_and_conquer(vl(begin(h), begin(h) + mid),
                                 vl(begin(bottom), begin(bottom) + mid));
  auto [right, top] = get_right_and_top(left, vl(mid + all(bottom)));
  vl h_right(mid + all(h));
  for (ll& hh : h_right) hh -= h[mid - 1];
  auto upper_right = divide_and_conquer(h_right, top);
  right.insert(end(right), all(upper_right));
  return right;
}
