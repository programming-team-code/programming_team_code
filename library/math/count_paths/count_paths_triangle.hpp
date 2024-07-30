/** @file */
#pragma once
#include "count_paths_rectangle.hpp"
vl divide_and_conquer(vl h, vl bottom) {
  assert(sz(h) == sz(bottom) && is_sorted(all(h)) && !empty(h) && h[0] >= 0);
  {
    int start = 0;
    while (start < sz(h) && h[start] == 0) start++;
    h = vl(begin(h) + start, end(h));
    bottom = vl(begin(bottom) + start, end(bottom));
  }
  int n = sz(h);
  if (n == 0) {
    return {};
  }
  if (n == 1) {
    return vl(h[0], bottom[0]);
  }
  int mid = n / 2;
  //  written in terms of the "blue" square
  auto left = divide_and_conquer(vl(begin(h), begin(h) + mid),
                                 vl(begin(bottom), begin(bottom) + mid));
  auto [right, top] = get_right_and_top(left, vl(begin(bottom) + mid, end(bottom)));
  vl h_right(begin(h) + mid, end(h));
  for (ll& hh : h_right) hh -= h[mid - 1];
  auto upper_right = divide_and_conquer(h_right, top);
  right.insert(end(right), all(upper_right));
  return right;
}
