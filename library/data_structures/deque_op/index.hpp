//! @file
#pragma once
/**
 * @param i index
 * @returns deq[i]
 * @time O(1)
 * @space O(1)
 */
T operator[](int i) {
  return (i < sz(le) ? le[sz(le) - i - 1] : ri[i - sz(le)])[0];
}
