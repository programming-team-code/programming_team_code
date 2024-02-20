/** @file */
#pragma once
const int mx_n = 1'000'005;
/**
 * mobius[i] = 0 iff there exists a prime p s.t. i%(p^2)=0
 * mobius[i] = -1 iff i has an odd number of distinct prime factors
 * mobius[i] = 1 iff i has an even number of distinct prime factors
 */
int mobius[mx_n];
/**
 * @time O(mx_n log mx_n)
 * @space O(mx_n)
 */
void calc_mobius() {
	mobius[1] = 1;
	for (int i = 1; i < mx_n; i++)
		for (int j = i + i; j < mx_n; j += i)
			mobius[j] -= mobius[i];
}
