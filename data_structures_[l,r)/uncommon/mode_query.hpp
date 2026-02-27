const int b = 318; //!< sqrt(1e5)
//! https://noshi91.hatenablog.com/entry/2020/10/26/140105
struct mode_query {
  int n;
  vector<int> a, cnt, index_into_index;
  vector<vector<int>> index;
  vector<vector<pair<int, int>>>
    mode_blocks; //!< {mode, cnt} of range of blocks
  //! @param a compressed array: 0 <= a[i] < n
  //! @time O(n * sqrt(n))
  //! @space O(n)
  mode_query(const vector<int>& a):
    n(ssize(a)), a(a), cnt(n), index_into_index(n),
    index(n), mode_blocks((n + b - 1) / b,
                vector<pair<int, int>>((n + b - 1) / b)) {
    for (int i = 0; i < n; i++) {
      index_into_index[i] = ssize(index[a[i]]);
      index[a[i]].push_back(i);
    }
    for (int start = 0; start < n; start += b) {
      int mode = a[start];
      for (int i = start; i < n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
        if (
          mode_blocks[start / b][i / b].second < cnt[mode])
          mode_blocks[start / b][i / b] = {
            mode, cnt[mode]};
      }
      for (int i = start; i < n; i++) cnt[a[i]]--;
    }
  }
  //! @param l,r defines range [l, r)
  //! @returns {mode, cnt of mode}
  //! @time O(sqrt(n))
  //! @space O(1)
  pair<int, int> query(int l, int r) {
    assert(l < r);
    if (l / b >= (r - 1) / b - 1) {
      int mode = a[l];
      for (int i = l; i < r; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] > cnt[mode]) mode = a[i];
      }
      int cnt_mode = cnt[mode];
      for (int i = l; i < r; i++) cnt[a[i]]--;
      return {mode, cnt_mode};
    }
    pair<int, int> res =
      mode_blocks[l / b + 1][(r - 1) / b - 1];
    for (int i = l / b * b + b - 1; i >= l; i--)
      cnt[a[i]]++;
    for (int i = l / b * b + b - 1; i >= l; i--) {
      int idx = index_into_index[i];
      if (idx + res.second < ssize(index[a[i]]) &&
        index[a[i]][idx + res.second] < r)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    for (int i = (r - 1) / b * b; i < r; i++) cnt[a[i]]++;
    for (int i = (r - 1) / b * b; i < r; i++) {
      int idx = index_into_index[i];
      if (idx >= res.second &&
        index[a[i]][idx - res.second] >= l)
        res = {a[i], cnt[a[i]] + res.second};
      cnt[a[i]]--;
    }
    return res;
  }
};
