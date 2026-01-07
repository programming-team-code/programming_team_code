#pragma once
//! https://codeforces.com/blog/entry/61203?#comment-1064868
//! @code
//!   vector<pii> queries;
//!   ranges::sort(queries, {}, [&](pii& x) {
//!     return hilbert(x.first, x.second);
//!   });
//! @endcode
//! @time O(log(n))
//! @space O(1)
ll hilbert(int x, int y) {
  ll d = 0, mx = 1;
  while(mx <= max(x, y)) mx *= 4;
  for (int s = mx / 2; s; s /= 2) {
    bool rx = x & s, ry = y & s;
    d = d * 4 | (ry * 3 ^ rx);
    if (!rx) {
      if (ry) x ^= mx - 1, y ^= mx - 1;
      swap(x, y);
    }
  }
  return d;
}
