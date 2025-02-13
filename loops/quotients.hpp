//! https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Math/DivisionTrick.cpp
//! i-th iteration gives an interval [le_i, ri_i]:
//!   - for all i in [le_i, ri_i]: n / i is the same
//!   - le_0 = 1
//!   - ri_last = n
//!   - ri_i + 1 = le_(i+1)
//! @time O(sqrt(n))
//! @space O(1)
for (int64_t l = 1, r; l <= n && (r = n / (n / l));
  l = r + 1)
