/**
 * Binary Indexed Tree
 */
template <class T> struct BIT {
  vector<T> s;
  /**
   * @param n initial size
   * @time O(n)
   * @space O(n) for `s` vector
   */
  BIT(int n) : s(n) {}
  BIT() {} /**< allows late initialization */
  /**
   * @param a initial array
   * @time O(n)
   * @space O(n) for `s` vector
   */
  BIT(const vector<T>& a) : s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  /**
   * @param i index
   * @param d delta
   * @time O(log n)
   * @space O(1)
   */
  inline void update(int i, T d) {
    assert(0 <= i && i < ssize(s));
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  /**
   * @param ri defines range [0, ri)
   * @returns a[0] + a[1] + ... + a[ri - 1]
   * @time O(log n)
   * @space O(1)
   */
  inline T query(int ri) {
    assert(0 <= ri && ri <= ssize(s));
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] + a[le + 1] + ... + a[ri - 1]
   * @time O(log n)
   * @space O(1)
   */
  inline T query(int le, int ri) {
    assert(le <= ri);
    return query(ri) - query(le);
  }
  /**
   * Requires bit.sum(i, i + 1) >= 0
   * @param sum see return
   * @returns min pos such that sum of range [0, pos) >= sum (or n+1)
   * @time O(log n)
   * @space O(1)
   */
  inline int lower_bound(T sum) {
    if (sum <= 0) return 0;
    int pos = 0;
    for (int pw = 1 << __lg(ssize(s) | 1); pw; pw >>= 1)
      if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos + 1;
  }
};
/**
 * @see https://codeforces.com/blog/entry/111625
 *
 * Given strings s, t (s initially empty):
 *   - append character onto s
 *   - given range [le, ri), calculate size(LCS(s, t.substr(le, ri - le)))
 *       = number of indexes i such that le <= i < ri && dp[i] < le
 *
 * notes:
 *     -1 <= dp[i] <= i < |t|
 *     there can be multiple indexes i such that dp[i] = -1
 *     size(LCS(s, t)) = number of indexes i such that dp[i] = -1
 *     for all index pairs i, j: if i != j && dp[i] != -1 && dp[j] != -1 then dp[i] != dp[j]
 *
 * @time O(|s| * |t|)
 * @space O(|t|)
 */
template <class T> struct lcs_dp {
  T t;
  vector<int> dp;
  lcs_dp(const T& a_t) : t(a_t), dp(ssize(t)) {
    iota(begin(dp), end(dp), 0);
  }
  void push_onto_s(int c) {
    for (int i = 0, v = -1; i < ssize(t); i++)
      if (c == t[i] || dp[i] < v) swap(dp[i], v);
  }
};
/**
 * Given strings s, t handle queries for:
 *     given s_ri, t_le, t_ri; calculate size(LCS(s[0, s_ri), t[t_le, t_ri)))
 *
 * @param s,t strings/arrays
 * @param queries queries[i] = {s_ri, t_le, t_ri}
 * @returns res[i] = size(LCS(s.substr(0, queries[i][0]), t.substr(queries[i][1], queries[i][2] - queries[i][1])))
 * @time O(n*m*log(m) + q*log(m) + q*log(q))
 * @space this allocates/returns a O(q) vector, and various vectors are
 * allocated temporarily which are O(n + m + q)
 */
template <class T> vector<int> lcs_queries(const T& s, const T& t, const vector<array<int, 3>>& queries) {
  int n = ssize(s), m = ssize(t), q = ssize(queries);
  vector<vector<array<int, 3>>> qs(n);
  for (int i = 0; i < q; i++) {
    auto [s_ri, t_le, t_ri] = queries[i];
    assert(0 <= s_ri && s_ri <= n);
    assert(0 <= t_le && t_le <= t_ri && t_ri <= m);
    if (s_ri == 0 || t_le == m) continue;
    qs[s_ri - 1].push_back({t_le, t_ri, i});
  }
  lcs_dp lcs(t);
  vector<int> res(q);
  for (int i = 0; i < n; i++) {
    lcs.push_onto_s(s[i]);
    vector<int> init(m), dp_inv(m, -1);
    for (int j = 0; j < m; j++)
      if (lcs.dp[j] == -1) init[j] = 1;
      else dp_inv[lcs.dp[j]] = j;
    BIT<int> bit(init);
    sort(begin(qs[i]), end(qs[i]));
    for (int t_le = 0, j = 0; t_le < m; t_le++) {
      while (j < ssize(qs[i]) && qs[i][j][0] == t_le)
        res[qs[i][j][2]] = bit.query(t_le, qs[i][j][1]), j++;
      if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
    }
  }
  return res;
}
