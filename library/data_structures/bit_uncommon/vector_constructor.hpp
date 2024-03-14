/** @file */
#pragma once
BIT() {} /**< allows late initialization */
/**
 * @param a initial array
 * @time O(n)
 * @space O(n) for `s` vector
 */
BIT(const vector<T>& a) : s(a) {
  for (int i = 0; i < ssize(a); i++) {
    int j = i | (i + 1);
    if (j < ssize(a)) s[j] += s[i];
  }
}
