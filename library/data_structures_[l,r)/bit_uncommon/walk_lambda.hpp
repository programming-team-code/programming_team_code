//! @code
//!   bit.walk([&](int r, ll sum) -> bool {
//!     // sum = a[0] + a[1] + ... + a[r - 1]
//!   });
//! @endcode
void walk(const auto& f) {
  ll sum = 0;
  for (int i = bit_floor(size(s)), r = 0; i; i /= 2)
    if (r + i <= sz(s) && f(r + i, sum + s[r + i - 1]))
      sum += s[(r += i) - 1];
}
