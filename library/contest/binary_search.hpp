//! https://codeforces.com/blog/entry/134777
//!
//! returns first x in [lo, hi) such that lambda returns 0,
//! or hi if it doesn't exist. Be careful to make sure the
//! lo and hi are both integers of the same type, otherwise
//! there is weird behavior.
//!
//! @time O(log(hi-lo))
//! @space O(1)
ll res = *ranges::partition_point(views::iota(lo, hi),
  [&](ll x) -> bool { return x < 0; });
