#pragma once
const int b = 318; //!< sqrt(1e5)
//! https://noshi91.hatenablog.com/entry/2020/10/26/140105
struct mode_query {
  int n;
  vi a, cnt, index_into_index;
  vector<vi> index;
  vector<vector<pii>>
    mode_blocks; //!< {mode, cnt} of range of blocks
  //! @param a_a compressed array: 0 <= a_a[i] < n
  //! @time O(n * sqrt(n))
  //! @space O(n)
  mode_query(const vi& a_a):
    n(sz(a_a)), a(a_a), cnt(n), index_into_index(n),
    index(n), mode_blocks((n + b - 1) / b,
                vector<pii>((n + b - 1) / b)) {
    rep(i, 0, n) {
      index_into_index[i] = sz(index[a[i]]);
      index[a[i]].push_back(i);
    }
    for (int start = 0; start < n; start += b) {
      int mode = a[start];
      rep(i, start, n) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
        if (
          mode_blocks[start / b][i / b].second < cnt[mode])
          mode_blocks[start / b][i / b] = {
            mode, cnt[mode]};
      }
      rep(i, start, n) cnt[a[i]]--;
    }
  }
  //! @param l,r defines range [l, r)
  //! @returns {mode, cnt of mode}
  //! @time O(sqrt(n))
  //! @space O(1)
  pii query(int l, int r) {
    assert(l < r);
    if (l / b >= (r - 1) / b - 1) {
      int mode = a[l];
      rep(i, l, r) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
      }
      int cnt_mode = cnt[mode];
      rep(i, l, r) cnt[a[i]]--;
      return {mode, cnt_mode};
    }
    pii res = mode_blocks[l / b + 1][(r - 1) / b - 1];
    for (int i = l / b * b + b - 1; i >= l; i--)
      cnt[a[i]]++;
    for (int i = l / b * b + b - 1; i >= l; i--) {
      int idx = index_into_index[i];
      if (idx + res.second < sz(index[a[i]]) &&
        index[a[i]][idx + res.second] < r)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    rep(i, (r - 1) / b * b, r) cnt[a[i]]++;
    rep(i, (r - 1) / b * b, r) {
      int idx = index_into_index[i];
      if (idx >= res.second &&
        index[a[i]][idx - res.second] >= l)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    return res;
  }
};
