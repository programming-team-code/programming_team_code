/** @file */
#pragma once
/**
 * @param mask represents a bitmask
 * @param f called on all submasks of mask
 * @time O(3^n) to iterate every submask of every mask of size n
 * @space O(1)
 */
template <class F> void submasks(int mask, F f) {
	for (int submask = mask; submask; submask = (submask - 1) & mask)
		f(submask);
}
