/** @file */
#pragma once
/**
 * subarray of matches in `sa`, and example of longest matching prefix of t in s
 */
struct match {
	/**
	 * t is some string defined by the query
	 *
	 * [sa_le, sa_ri) defines subarray of suffix array such that:
	 * - for all i in [sa_le, sa_ri): t == s.substr(sa[i], ssize(t))
	 * - `sa_ri - sa_le` is the # of matches of t in s.
	 *
	 * [str_le, str_ri) defines a substring of s such that:
	 * - s.substr(str_le, str_ri - str_le) == t.substr(0, str_ri - str_le)
	 * - (str_ri - str_le) is maximized, if there are multiple answers, str_le is arbitrary
	 *
	 * - note if sa_le < sa_ri, i.e. at least one match, then str_ri - str_le == ssize(t)
	 * - note if sa_le == sa_ri, i.e. no matches, then str_ri - str_le < ssize(t)
	 * @{
	 */
	int sa_le, sa_ri, str_le, str_ri;
	/** @} */
};
