//! https://codeforces.com/blog/entry/125371?#comment-1173604
//! @code
//!   linear_rmq rmq1(a, less());          //right-most min
//!   linear_rmq rmq2(a, less_equal());    //left-most min
//!   linear_rmq rmq3(a, greater());       //right-most max
//!   linear_rmq rmq4(a, greater_equal()); //left-most max
//!   linear_rmq rmq5(a, [&](auto& x, auto& y) {
//!     return x < y;
//!   });
//! @endcode
//! @time O(n + q)
//! @space O(n)
template<class T, class F> struct linear_rmq {
  int n;
  vector<T> a;
  F cmp;
  vector<int> in, asc, head;
  linear_rmq(const vector<T>& a, F cmp):
    n(ssize(a)), a(a), cmp(cmp), in(n), asc(n),
    head(n + 1) {
    vector<int> st{-1};
    for (int i = 0; i < n + 1; i++) {
      int prev = 0;
      while (ssize(st) > 1 &&
        (i == n || !cmp(a[st.back()], a[i]))) {
        head[prev] = st.back();
        auto j = end(st)[-2] + 1u, k = bit_floor(i ^ j);
        in[st.back()] = prev = i & -k, asc[j] |= k;
        st.pop_back();
      }
      st.push_back(head[prev] = i);
    }
    for (int i = 1; i < n; i++)
      asc[i] = (asc[i] | asc[i - 1]) & -(in[i] & -in[i]);
  }
  int idx(int l, int r) {
    if (unsigned j = in[l] ^ in[r]; j) {
      j = asc[l] & asc[r] & -bit_floor(j);
      if (unsigned k = asc[l] ^ j; k)
        k = bit_floor(k), l = head[(in[l] & -k) | k];
      if (unsigned k = asc[r] ^ j; k)
        k = bit_floor(k), r = head[(in[r] & -k) | k];
    }
    return cmp(a[l], a[r]) ? l : r;
  }
  T query(int l, int r) { return a[idx(l, r)]; }
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
  vector<vector<int>> ch;
  bool touches(int u, int v) {
    return p[u].mn_num == p[v].mn_num + p[v].len ||
      p[v].mn_num == p[u].mn_num + p[u].len;
  }
  int allocate(int mn_i, int mn_v, int ln, bool join,
    const vector<int>& chs) {
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
        mn_i[i] = a_inv[rmq_min.idx(a[i - 1], a[i])];
        mx_i[i] = a_inv[rmq_max.idx(a[i - 1], a[i])];
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
          ch[u].push_back(v);
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
        vector<int> chs(1 + ssize(st) - idx, v);
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
