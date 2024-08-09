/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 * @see https://codeforces.com/blog/entry/125371?#comment-1173604
 */
template <class T, class F> struct linear_rmq {
  vector<T> a;
  F cmp;
  vector<int> head;
  vector<array<int, 2>> t;
  /**
   * @code{.cpp}
         vector<ll> a(n);
         linear_rmq rmq(a, less()); // right-most min
         linear_rmq rmq(a, less_equal()); // left-most min
         linear_rmq rmq(a, greater()); // right-most max
         linear_rmq rmq(a, greater_equal()); // left-most max
   * @endcode
   * @param a_a,a_cmp array and a compare operator
   * @time O(n)
   * @space O(n)
   */
  linear_rmq(const vector<T>& a_a, F a_cmp) : a(a_a), cmp(a_cmp), head((int)size(a) + 1), t((int)size(a)) {
    vector<int> st{-1};
    for (int i = 0; i <= (int)size(a); i++) {
      int prev = -1;
      while (st.back() != -1 && (i == (int)size(a) || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        t[st.back()][0] = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1][1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    for (int i = 1; i < ((int)size(a)); i++)
      t[i][1] = (t[i][1] | t[i - 1][1]) & -(t[i][0] & -t[i][0]);
  }
  /**
   * @param le,ri defines range [le, ri]
   * @returns index of min/max of range
   * @time O(1)
   * @space O(1)
   */
  int query_idx(int le, int ri) {
    if (int j = t[le][0] ^ t[ri][0]; j) {
      j = t[le][1] & t[ri][1] & -(1 << __lg(j));
      if (int k = t[le][1] ^ j; k) k = 1 << __lg(k), le = head[(t[le][0] & -k) | k];
      if (int k = t[ri][1] ^ j; k) k = 1 << __lg(k), ri = head[(t[ri][0] & -k) | k];
    }
    return cmp(a[le], a[ri]) ? le : ri;
  }
  /**
   * @param le,ri defines range [le, ri]
   * @returns min/max of range
   * @time O(1)
   * @space O(1)
   */
  T query(int le, int ri) { return a[query_idx(le, ri)]; }
};
/**
 * @see https://codeforces.com/blog/entry/78898
 * @code{.cpp}
       auto [data, root, adj] = perm_tree(a);
 * @endcode
 */
struct perm_tree {
  struct node {
    /**
     * [mn_idx[v], mn_idx[v] + len[v]) is range of indexes
     * [mn_num[v], mn_num[v] + len[v]) is range of numbers
     * @{
     */
    int mn_idx, mn_num, len;
    /** @} */
    bool is_join;
  };
  vector<node> t;
  int root;
  vector<vector<int>> adj; /**< [0, n) are leaves, [n, sz(adj)) are internal nodes */
  bool touches(int u, int v) {
    return t[u].mn_num == t[v].mn_num + t[v].len || t[v].mn_num == t[u].mn_num + t[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join, const vector<int>& ch) {
    t.push_back({mn_i, mn_v, ln, join});
    adj.push_back(ch);
    return (int)size(adj) - 1;
  }
  /**
   * @param a permutation
   * @time O(n)
   * @space O(n)
   */
  perm_tree(const vector<int>& a) {
    int n = (int)size(a);
    vector<int> mn_i(n), mx_i(n);
    {
      vector<int> a_inv(n, -1);
      for (int i = 0; i < (n); i++) a_inv[a[i]] = i;
      linear_rmq rmq_min(a_inv, less());
      linear_rmq rmq_max(a_inv, greater());
      for (int i = 1; i < (n); i++) {
        mn_i[i] = a_inv[rmq_min.query_idx(a[i - 1], a[i])];
        mx_i[i] = a_inv[rmq_max.query_idx(a[i - 1], a[i])];
      }
    }
    for (int i = 0; i < (n); i++) allocate(i, a[i], 1, 0, {});
    vector<array<int, 4>> st;
    for (int i = 0; i < (n); i++) {
      int v = i;
      while (!empty(st)) {
        int u = st.back()[0];
        if (!empty(adj[u]) && touches(adj[u].back(), v)) {
          t[u].mn_num = min(t[u].mn_num, t[v].mn_num);
          t[u].len += t[v].len;
          adj[u].push_back(v);
          v = u;
          st.pop_back();
          continue;
        }
        if (touches(v, u)) {
          v = allocate(t[u].mn_idx, min(t[v].mn_num, t[u].mn_num), t[v].len + t[u].len, 1, {u, v});
          st.pop_back();
          continue;
        }
        int le = min(t[u].mn_idx, mn_i[t[v].mn_idx]), ri = max(i, mx_i[t[v].mn_idx]), idx = (int)size(st) - 1;
        while (ri == i && le != t[st[idx][0]].mn_idx)
          le = min(le, st[idx][1]), ri = max(ri, st[idx][2]), idx = st[idx][3];
        if (ri > i) {
          st.push_back({v, le, ri, idx});
          break;
        }
        int min_num = t[v].mn_num;
        vector<int> ch(1 + (int)size(st) - idx, v);
        for (int j = idx; j < ((int)size(st)); j++)
          min_num = min(min_num, t[ch[j - idx] = st[j][0]].mn_num);
        v = allocate(le, min_num, i - le + 1, 0, ch);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({v, -1, -1, -1});
    }
    assert((int)size(st) == 1);
    root = st[0][0];
  }
};
