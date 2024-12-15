//! for all i in [sa_le,sa_ri):
//!   - t==s.substr(sa[i],sz(t))
//!   - `sa_ri-sa_le` is the # of matches of t in s.
//!
//! if sa_le==sa_ri then:
//!   s[s_l,s_r) is longest substring such that:
//!   s[s_l,s_r) == t[0,s_r-s_l)
struct match {
  int sa_le, sa_ri, s_l, s_r;
};
//! @param substrs this defines query string t as:
//!     s.substr(substrs[0][0], substrs[0][1] -
//!     substrs[0][0]) + s.substr(substrs[1][0],
//!     substrs[1][1] - substrs[1][0]) +
//!     ...
//!     s.substr(substrs.back()[0], substrs.back()[1] -
//!     substrs.back()[0])
//!     - doesn't work when substrs[i][0] == n
//! @returns see match
//! @time O(sz(substrs) * log(|s|))
//! @space O(1)
match find_substrs_concated(
  const vector<pair<int, int>>& substrs) {
  using dt = array<int, 3>;
  int sa_le = 0, sa_ri = n, s_l = 0, s_r = 0, sum_len = 0;
  auto cmp = [&](int i, const dt& x) -> bool {
    int j = i + sum_len,
        lcp_len = j == n ? 0 : min(len_lcp(j, x[0]), x[1]);
    if (lcp_len + sum_len > s_r - s_l)
      s_l = i, s_r = j + lcp_len;
    if (lcp_len < min(n - j, x[1]))
      return sa_inv[j] - sa_inv[x[0]] < x[2];
    return x[2] ^ (n - j < x[1]);
  };
  for (auto [l, r] : substrs) {
    sa_le = lower_bound(begin(sa) + sa_le,
              begin(sa) + sa_ri, dt{l, r - l, 0}, cmp) -
      begin(sa);
    sa_ri = lower_bound(begin(sa) + sa_le,
              begin(sa) + sa_ri, dt{l, r - l, 1}, cmp) -
      begin(sa);
    sum_len += r - l;
  }
  return {sa_le, sa_ri, s_l, s_r};
}
