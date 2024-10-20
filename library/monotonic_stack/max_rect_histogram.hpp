#pragma once
#include "monotonic_range.hpp"
//! returns largest integer x such that there exists a
//! subarray a[l,r) with: (r-l) * min(a[l,r)) == x
//! @time O(n)
//! @space O(n)
ll max_rect_histogram(const vi& a) {
  vi l(mono_st(a, less())), r(mono_range(l));
  ll max_area = 0;
  rep(i, 0, sz(a)) max_area =
    max(max_area, ll(a[i]) * (r[i] - l[i] - 1));
  return max_area;
}
