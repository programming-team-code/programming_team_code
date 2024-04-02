/** @file */
#pragma once
#include "monotonic_range.hpp"
/**
 * @param a contains positive integers
 * @returns largest integer x such that there exists a subarray a[le,ri)
 * with: (ri-le) * min(a[le,ri)) == x
 * @time O(n)
 * @space besides O(n) param `a`, O(n) extra space is allocated temporarily
 */
ll max_rect_histogram(const vi& a) {
  auto le(mono_st(a, less())), ri(mono_range(le));
  auto max_area = 0LL;
  rep(i, 0, sz(a))
      max_area = max(max_area, 1LL * a[i] * (ri[i] - le[i] - 1));
  return max_area;
}
