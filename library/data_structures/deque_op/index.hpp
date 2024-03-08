/** @file */
#pragma once
/**
 * @param i index
 * @returns deq[i]
 * @time O(1)
 * @space O(1)
 */
inline T operator[](int i) {
	assert(0 <= i && i < siz());
	return (i < ssize(le) ? le[ssize(le) - i - 1] : ri[i - ssize(le)])[0];
}
