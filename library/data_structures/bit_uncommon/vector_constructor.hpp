/** @file */
#pragma once
BIT() {} /**< allows late initialization */
/**
 * @param a initial array
 * @time O(n)
 * @space O(n) for `s` vector
 */
BIT(const vector<T>& a) : s(a) {
  rep(i, 0, sz(a)) {
    int j = i | (i + 1);
    if (j < sz(a)) s[j] += s[i];
  }
}
