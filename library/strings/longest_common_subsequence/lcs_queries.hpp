#pragma once
#include "../../data_structures/bit.hpp"
#include "lcs_dp.hpp"
//! @code
//!   string s,t;
//!   vi lcs_len = lcs_queries(s, t, queries);
//!   vi s_vec,t_vec;
//!   vi lcs_len1 = lcs_queries(s_vec, t_vec, queries);
//! @endcode
//! lcs_len[i] = size(LCS(
//!   s[0,queries[i][0]),
//!   t[queries[i][1],queries[i][2])
//! ))
//! @time O(n*m*log(m) + q*log(m) + q*log(q))
//! @space O(n + m + q)
vi lcs_queries(const auto& s, const auto& t,
  const vector<array<int, 3>>& queries) {
  int n = sz(s), m = sz(t), q = sz(queries);
  vector<vector<array<int, 3>>> qs(n);
  rep(i, 0, q) {
    auto [s_r, t_le, t_ri] = queries[i];
    if (s_r == 0 || t_le == m) continue;
    qs[s_r - 1].push_back({t_le, t_ri, i});
  }
  lcs_dp lcs(t);
  vi res(q);
  rep(i, 0, n) {
    lcs.push_onto_s(s[i]);
    BIT bit(m);
    vi dp_inv(m, -1);
    rep(j, 0, m) {
      if (lcs.dp[j] == -1) bit.update(j, 1);
      else dp_inv[lcs.dp[j]] = j;
    }
    ranges::sort(qs[i]);
    int j = 0;
    rep(t_le, 0, m) {
      while (j < sz(qs[i]) && qs[i][j][0] == t_le)
        res[qs[i][j][2]] = bit.query(t_le, qs[i][j][1]),
        j++;
      if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
    }
  }
  return res;
}
