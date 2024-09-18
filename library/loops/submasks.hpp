#pragma once
//! loops over submasks in decreasing order
//! @param mask a submask of 2^n-1
//! @time O(3^n) to iterate every submask of every mask of size n
//! @space O(1)
for (int submask = mask; submask;
     submask = (submask - 1) & mask)
