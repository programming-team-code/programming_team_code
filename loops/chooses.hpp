//! https://github.com/kth-competitive-programming/kactl/blob/main/content/various/chapter.tex
//! returns the smallest number x such that:
//! - popcount(x)==popcount(mask)
//! - x > mask
//! @time O(1)
//! @space O(1)
int next_subset(int mask) {
  int c = mask & -mask, r = mask + c;
  return r | (((r ^ mask) >> 2) / c);
}
//! loop over all submasks of 2^n-1 with
//! k bits set, increasing
//! @time O(n choose k)
//! @space O(1)
for (int mask = (1 << k) - 1; mask < (1 << n);
  mask = next_subset(mask))
