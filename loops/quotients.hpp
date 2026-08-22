//! https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Math/DivisionTrick.cpp
//! i-th iteration gives an interval [l_i, r_i]:
//!   - for all i in [l_i, r_i]: n / i is the same
//!   - l_0 = 1
//!   - r_last = n
//!   - r_i + 1 = l_(i+1)
//! @time O(sqrt(n))
//! @space O(1)
for (int64_t l = 1, r; l <= n && (r = n / (n / l)); l = r + 1) 