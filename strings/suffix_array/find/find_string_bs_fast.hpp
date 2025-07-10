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
//! https://stackoverflow.com/a/11374737
//! https://codeforces.com/blog/entry/133051
//! @time O(log(|s|) + |t|)
//! @space O(1)
match find_str_fast(const T& t) {
  int s_l = n, s_len = 0;
  auto cmp = [&](int i, int) -> bool {
    if (int lcp_len = s_l == n ? 0 : len_lcp(s_l, i);
      lcp_len != s_len)
      return (lcp_len < s_len) ^ (cmp_sufs(s_l, i) < 0);
    auto [it_s, it_t] = mismatch(i + s_len + begin(s),
      end(s), s_len + begin(t), end(t));
    s_l = i, s_len = it_t - begin(t);
    return lexicographical_compare(it_s, end(s), it_t,
      end(t));
  };
  int sa_le = lower_bound(begin(sa), end(sa), 0, cmp) -
    begin(sa),
      sa_ri = sa_le;
  if (s_len == ssize(t))
    sa_ri = lower_bound(sa_le + begin(sa), end(sa), 0,
              [&](int i, int) -> bool {
                return len_lcp(s_l, i) >= ssize(t);
              }) -
      begin(sa);
  return {sa_le, sa_ri, s_l, s_l + s_len};
}
