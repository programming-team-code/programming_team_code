//! @file
#pragma once
#include "count_paths_rectangle.hpp"
/**
 * @see https://noshi91.hatenablog.com/entry/2023/07/21/235339
 * @param h,bottom see image
 * @returns see image
 * @time O((n + m)log^2(n + m)): n = sz(h); m = h.back()
 * @space O(n + m)
 */
vl divide_and_conquer(vl h, vl bottom) {
  {
    int start = find_if(all(h), [](ll x) { return x; }) - begin(h);
    h.erase(begin(h), begin(h) + start);
    bottom.erase(begin(bottom), begin(bottom) + start);
  }
  int n = sz(h);
  if (n == 0) return {};
  if (n == 1) return vl(h[0], bottom[0]);
  int mid = n / 2;
  auto rect_left = divide_and_conquer(vl(begin(h), begin(h) + mid),
                                      vl(begin(bottom), begin(bottom) + mid));
  auto [rect_right, rect_top] = get_right_and_top(rect_left, vl(mid + all(bottom)));
  vl h_right(mid + all(h));
  for (ll& hh : h_right) hh -= h[mid - 1];
  auto upper_right = divide_and_conquer(h_right, rect_top);
  rect_right.insert(end(rect_right), all(upper_right));
  return rect_right;
}
