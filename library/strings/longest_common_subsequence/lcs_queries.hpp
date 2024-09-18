#pragma once
#include "../../data_structures/bit.hpp"
#include "lcs_dp.hpp"
//! Given strings s, t handle queries for:
//!     given s_ri, t_le, t_ri; calculate size(LCS(s[0,
//!     s_ri), t[t_le, t_ri)))
//!
//! @param s,t strings/arrays
//! @param queries queries[i] = {s_ri, t_le, t_ri}
//! @returns res[i] = size(LCS(s.substr(0, queries[i][0]),
//! t.substr(queries[i][1], queries[i][2] - queries[i][1])))
//! @time O(n*m*log(m) + q*log(m) + q*log(q))
//! @space this allocates/returns a O(q) vector, and various
//! vectors are allocated temporarily which are O(n + m + q)
template<class T>
vi lcs_queries(const T& s, const T& t,
  const vector<array<int, 3>>& queries) {
  int n = sz(s), m = sz(t), q = sz(queries);
  vector<vector<array<int, 3>>> qs(n);
  rep(i, 0, q) {
    auto [s_ri, t_le, t_ri] = queries[i];
    if (s_ri == 0 || t_le == m) continue;
    qs[s_ri - 1].push_back({t_le, t_ri, i});
  }
  lcs_dp lcs(t);
  vi res(q);
  rep(i, 0, n) {
    lcs.push_onto_s(s[i]);
    vi init(m), dp_inv(m, -1);
    rep(j, 0, m) {
      if (lcs.dp[j] == -1) init[j] = 1;
      else dp_inv[lcs.dp[j]] = j;
    }
    BIT<int> bit(init);
    sort(all(qs[i]));
    int j = 0;
    rep(t_le, 0, m) {
      while (j < sz(qs[i]) && qs[i][j][0] == t_le)
        res[qs[i][j][2]] = bit.query(t_le, qs[i][j][1]), j++;
      if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
    }
  }
  return res;
}
