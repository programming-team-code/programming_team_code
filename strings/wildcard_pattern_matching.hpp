//! https://codeforces.com/blog/entry/111380
//! @code
//!   vl s_vec, t_vec;
//!   auto mtch = wildcard_pattern_matching(
//!     s_vec, t_vec, conv);
//! @endcode
//! s_vec[mtch[i],sz(t_vec)) == t_vec
//! s_vec[i]=0 or t_vec[i]=0 for a wildcard
//! @time O((n+m) log (n+m))
//! @space O(n+m)
using vl = vector<int64_t>;
vector<vl> make_powers(const vl& v) {
  int n = ssize(v);
  vector<vl> pws(3, vl(n));
  for (int i = 0; i < n; i++) {
    pws[0][i] = v[i];
    pws[1][i] = v[i] * v[i];
    pws[2][i] = v[i] * v[i] * v[i];
  }
  return pws;
}
vector<bool> wildcard_pattern_matching(const vl& s,
  const vl& t, auto conv) {
  int n = ssize(s), m = ssize(t);
  auto s_pws = make_powers(s);
  auto t_pws = make_powers(t);
  for (auto& t_pw : t_pws) reverse(begin(t_pw), end(t_pw));
  vector<vl> res(3);
  for (int pw_hay = 0; pw_hay < 3; pw_hay++)
    res[pw_hay] = conv(s_pws[pw_hay], t_pws[2 - pw_hay]);
  vector<bool> mtch(n - m + 1);
  for (int i = 0; i < n - m + 1; i++) {
    int id = i + m - 1;
    auto num = res[0][id] - 2 * res[1][id] + res[2][id];
    mtch[i] = num == 0;
  }
  return mtch;
}
