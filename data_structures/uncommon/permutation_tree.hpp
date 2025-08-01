//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq rmq1(a, less());//right-most min
//!   linear_rmq rmq2(a, less_equal());//left-most min
//!   linear_rmq rmq3(a, greater());//right-most max
//!   linear_rmq rmq4(a, greater_equal());//left-most max
//!   linear_rmq rmq5(a, [&](auto& x, auto& y) {
//!     return x < y;
//!   });
//! @endcode
//! @time O(n + q)
//! @space O(n)
template<class T, class F> struct linear_rmq {
  vector<T> a;
  F cmp;
  vector<int> head;
  vector<array<int, 2>> t;
  linear_rmq(const vector<T>& a, F cmp):
    a(a), cmp(cmp), head(ssize(a) + 1), t(ssize(a)) {
    vector<int> st{-1};
    for (int i = 0; i <= ssize(a); i++) {
      int prev = -1;
      while (st.back() != -1 &&
        (i == ssize(a) || !cmp(a[st.back()], a[i]))) {
        if (prev != -1) head[prev] = st.back();
        int pw2 = 1 << __lg((end(st)[-2] + 1) ^ i);
        t[st.back()][0] = prev = i & -pw2;
        st.pop_back();
        t[st.back() + 1][1] |= pw2;
      }
      if (prev != -1) head[prev] = i;
      st.push_back(i);
    }
    for (int i = 1; i < ssize(a); i++)
      t[i][1] =
        (t[i][1] | t[i - 1][1]) & -(t[i][0] & -t[i][0]);
  }
  int query_idx(int l, int r) { // [l, r]
    if (unsigned j = t[l][0] ^ t[r][0]; j) {
      j = t[l][1] & t[r][1] & -bit_floor(j);
      if (unsigned k = t[l][1] ^ j; k)
        k = bit_floor(k), l = head[(t[l][0] & -k) | k];
      if (unsigned k = t[r][1] ^ j; k)
        k = bit_floor(k), r = head[(t[r][0] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[query_idx(l, r)]; }
};
//! https://codeforces.com/blog/entry/78898
//! @code
//!   auto [p, root, ch] = perm_tree(a);
//! @endcode
//! [p[v].mn_idx, p[v].mn_idx+p[v].len) index range
//! [p[v].mn_num, p[v].mn_num+p[v].len) number range
//! indexes [0, n) of ch are leaves
//! indexes [n, sz(ch)) of ch are internal nodes
//! @time O(n)
//! @space O(n)
struct perm_tree {
  struct node {
    int mn_idx, mn_num, len;
    bool is_join;
  };
  vector<node> p;
  int root;
  vector<basic_string<int>> ch;
  bool touches(int u, int v) {
    return p[u].mn_num == p[v].mn_num + p[v].len ||
      p[v].mn_num == p[u].mn_num + p[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join,
    const basic_string<int>& chs) {
    p.push_back({mn_i, mn_v, ln, join});
    ch.push_back(chs);
    return ssize(ch) - 1;
  }
  perm_tree(const vector<int>& a) {
    int n = ssize(a);
    vector<int> mn_i(n), mx_i(n);
    {
      vector<int> a_inv(n, -1);
      for (int i = 0; i < n; i++) a_inv[a[i]] = i;
      linear_rmq rmq_min(a_inv, less());
      linear_rmq rmq_max(a_inv, greater());
      for (int i = 1; i < n; i++) {
        mn_i[i] = a_inv[rmq_min.query_idx(a[i - 1], a[i])];
        mx_i[i] = a_inv[rmq_max.query_idx(a[i - 1], a[i])];
      }
    }
    for (int i = 0; i < n; i++)
      allocate(i, a[i], 1, 0, {});
    vector<array<int, 4>> st;
    for (int i = 0; i < n; i++) {
      int v = i;
      while (!empty(st)) {
        int u = st.back()[0];
        if (!empty(ch[u]) && touches(ch[u].back(), v)) {
          p[u].mn_num = min(p[u].mn_num, p[v].mn_num);
          p[u].len += p[v].len;
          ch[u] += v;
          v = u;
          st.pop_back();
          continue;
        }
        if (touches(v, u)) {
          v = allocate(p[u].mn_idx,
            min(p[v].mn_num, p[u].mn_num),
            p[v].len + p[u].len, 1, {u, v});
          st.pop_back();
          continue;
        }
        int l = min(p[u].mn_idx, mn_i[p[v].mn_idx]),
            r = max(i, mx_i[p[v].mn_idx]),
            idx = ssize(st) - 1;
        while (r == i && l != p[st[idx][0]].mn_idx)
          l = min(l, st[idx][1]), r = max(r, st[idx][2]),
          idx = st[idx][3];
        if (r > i) {
          st.push_back({v, l, r, idx});
          break;
        }
        int min_num = p[v].mn_num;
        basic_string<int> chs(1 + ssize(st) - idx, v);
        for (int j = idx; j < ssize(st); j++)
          min_num = min(min_num,
            p[chs[j - idx] = st[j][0]].mn_num);
        v = allocate(l, min_num, i - l + 1, 0, chs);
        st.resize(idx);
      }
      if (empty(st)) st.push_back({v, -1, -1, -1});
    }
    assert(ssize(st) == 1);
    root = st[0][0];
  }
};
