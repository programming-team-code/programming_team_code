#pragma once
//! https://codeforces.com/blog/entry/4898#comment-157965
//! - use random base to avoid getting hacked on codeforces
//! - work mod 1e9+7 if birthday paradox is not a problem
//! @time O(n + q)
//! @space O(n)
using mint = array<ll, 2>;
constexpr mint mod = {ll(1e9 + 7), ll(1e9 + 9)};
const ll base = 239017;
struct str_hash {
  vector<mint> ha, pw;
  str_hash(const auto& s): ha(sz(s) + 1), pw(ha) {
    pw[0] = {1, 1};
    rep(i, 0, sz(s)) rep(j, 0, 2) {
      pw[i + 1][j] = pw[i][j] * base % mod[j];
      ha[i + 1][j] = (ha[i][j] * base + s[i] + 1) % mod[j];
    }
  }
  mint subarray(int l, int r) { // [l, r)
    mint res;
    rep(j, 0, 2) {
      res[j] = ha[r][j] - ha[l][j] * pw[r - l][j] % mod[j];
      if (res[j] < 0) res[j] += mod[j];
    }
    return res;
  }
};
