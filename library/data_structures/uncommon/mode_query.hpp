//! @file
#pragma once
const int b = 318; /**< sqrt(1e5) */
/**
 * @see https://noshi91.hatenablog.com/entry/2020/10/26/140105
 */
struct mode_query {
  int n;
  vi a, cnt, index_into_index;
  vector<vi> index;
  vector<vector<pii>> mode_blocks; /**< {mode, cnt} of range of blocks */
  /**
   * @param a_a compressed array: 0 <= a_a[i] < n
   * @time O(n * sqrt(n))
   * @space O(n)
   */
  mode_query(const vi& a_a) : n(sz(a_a)), a(a_a), cnt(n), index_into_index(n), index(n), mode_blocks((n + b - 1) / b, vector<pii>((n + b - 1) / b)) {
    rep(i, 0, n) {
      index_into_index[i] = sz(index[a[i]]);
      index[a[i]].push_back(i);
    }
    for (int start = 0; start < n; start += b) {
      int mode = a[start];
      rep(i, start, n) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
        if (mode_blocks[start / b][i / b].second < cnt[mode])
          mode_blocks[start / b][i / b] = {mode, cnt[mode]};
      }
      rep(i, start, n) cnt[a[i]]--;
    }
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns {mode, cnt of mode}
   * @time O(sqrt(n))
   * @space O(1)
   */
  pii query(int le, int ri) {
    assert(le < ri);
    if (le / b >= (ri - 1) / b - 1) {
      int mode = a[le];
      rep(i, le, ri) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
      }
      int cnt_mode = cnt[mode];
      rep(i, le, ri) cnt[a[i]]--;
      return {mode, cnt_mode};
    }
    pii res = mode_blocks[le / b + 1][(ri - 1) / b - 1];
    for (int i = le / b * b + b - 1; i >= le; i--)
      cnt[a[i]]++;
    for (int i = le / b * b + b - 1; i >= le; i--) {
      int idx = index_into_index[i];
      if (idx + res.second < sz(index[a[i]]) && index[a[i]][idx + res.second] < ri)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    rep(i, (ri - 1) / b * b, ri)
        cnt[a[i]]++;
    rep(i, (ri - 1) / b * b, ri) {
      int idx = index_into_index[i];
      if (idx >= res.second && index[a[i]][idx - res.second] >= le)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    return res;
  }
};
