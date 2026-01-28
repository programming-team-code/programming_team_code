//! loops over supermasks in increasing order
//! @param mask a submask of (2^n)-1
//! @param n total number of bits
//! @time O(3^n) to iterate every supermask
//!   of every mask of size n
//! @space O(1)
for (int supermask = mask; supermask < (1 << n);
  supermask = (supermask + 1) | mask)
