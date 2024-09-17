//! @file
#pragma once
//! @see https://github.com/kth-competitive-programming/kactl/blob/main/content/various/chapter.tex
//! @param mask a number with k bits set
//! @returns the smallest number x such that:
//! - x has k bits set
//! - x > mask
//! @time O(1)
//! @space O(1)
int next_subset(int mask) {
  int c = mask & -mask, r = mask + c;
  return r | (((r ^ mask) >> 2) / c);
}
