#pragma once
//! https://codeforces.com/blog/entry/134777
//!
//! lambda(lo) -> T
//! lambda(lo+1) -> T
//! ...
//! lambda(i-1) -> T
//! lambda(i) -> F       <---- returns i
//! ...
//! lambda(hi-1) -> F
//! lambda(hi) -> F
//!
//! @time O(log(hi-lo))
//! @space O(1)
ll res = *ranges::partition_point(views::iota(lo, hi),
  [&](ll x) -> bool { return x < 0; });
