//! https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Hashing.h
//! https://codeforces.com/blog/entry/60442
//! https://codeforces.com/blog/entry/129538
//! probability of collision ~= 1/((1e9+7)*(1e9+9)) = 1/p
//! probability of no collision over q comparisons ~=
//!   (1 - (1/p))^q ~= 1 - q/p
//! checking if n hashes are pairwise distinct is the same
//!   as doing q = (n choose 2) ~= n^2 comparisons
//! use random base to avoid getting hacked on codeforces
//! @time O(n + q)
//! @space O(n)
using hsh = array<int64_t, 2>;
constexpr hsh md = {int64_t(1e9 + 7), int64_t(1e9 + 9)};
const int64_t base = 239017;
struct str_hash {
  vector<hsh> ha, pw;
  str_hash(const auto& s): ha(ssize(s) + 1), pw(ha) {
    pw[0] = {1, 1};
    for (int i = 0; i < ssize(s); i++)
      for (int j = 0; j < 2; j++) {
        pw[i + 1][j] = pw[i][j] * base % md[j];
        ha[i + 1][j] =
          (ha[i][j] * base + s[i] + 1) % md[j];
      }
  }
  hsh substr(int l, int r) { // [l, r)
    hsh res;
    for (int j = 0; j < 2; j++) {
      res[j] = ha[r][j] - ha[l][j] * pw[r - l][j] % md[j];
      if (res[j] < 0) res[j] += md[j];
    }
    return res;
  }
};
