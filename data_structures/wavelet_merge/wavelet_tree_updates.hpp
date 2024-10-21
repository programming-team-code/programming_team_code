//! https://github.com/dacin21/dacin21_codebook/blob/master/trees/wavelet_matrix.cpp
//! space efficient boolean array with prefix sum query
//! note `>> 6` is the same as `/ 64`
//! note `& 63` is the same as `% 64`
struct bool_presum {
  int n;
  vector<uint64_t> mask;
  vector<int> presum;
  //! @param a boolean array
  //! @time O(n)
  //! @space O(n / 64)
  bool_presum(const vector<bool>& a):
    n(ssize(a)), mask(n / 64 + 1), presum(ssize(mask)) {
    for (int i = 0; i < n; i++)
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
    for (int i = 0; i < ssize(mask) - 1; i++)
      presum[i + 1] =
        __builtin_popcountll(mask[i]) + presum[i];
  }
  //! @param i defines range [0, i)
  //! @returns a[0] + a[1] + ... + a[i - 1]
  //! @time O(1)
  //! @space O(1)
  int popcount(int i) {
    return presum[i >> 6] +
      __builtin_popcountll(
        mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  //! @param i index
  //! @returns 1 iff a[i] was on
  //! @time O(1)
  //! @space O(1)
  bool on(int i) { return (mask[i >> 6] >> (i & 63)) & 1; }
};
//! @time O(n + q log n)
//! @space O(n)
struct BIT {
  vector<int64_t> s;
  BIT(int n): s(n) {}
  BIT(const vector<int64_t>& a): s(a) {
    for (int i = 0; i < ssize(a); i++) {
      int j = i | (i + 1);
      if (j < ssize(a)) s[j] += s[i];
    }
  }
  void update(int i, int64_t d) {
    for (; i < ssize(s); i |= i + 1) s[i] += d;
  }
  int64_t query(int r) { // [0, r)
    int64_t ret = 0;
    for (; r > 0; r &= r - 1) ret += s[r - 1];
    return ret;
  }
  int64_t query(int l, int r) { // [l, r)
    return query(r) - query(l);
  }
  //! Requires bit.query(i,i+1) >= 0
  //! @returns max pos such that sum of [0,pos) < sum
  int lower_bound(int64_t sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << __lg(ssize(s) | 1); pw; pw >>= 1)
      if (pos + pw <= ssize(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
//! https://github.com/dacin21/dacin21_codebook/blob/master/trees/wavelet_matrix_updates.cpp
//! space efficient boolean array with range sum query, and
//! point update note `>> 6` is the same as `/ 64` note `&
//! 63` is the same as `% 64`
struct bool_bit {
  int n;
  vector<uint64_t> mask;
  BIT presum = {0};
  //! @param a boolean array
  //! @time O(n)
  //! @space O(n / 64)
  bool_bit(const vector<bool>& a):
    n(ssize(a)), mask(n / 64 + 1) {
    vector<int64_t> init((n + 63) / 64);
    for (int i = 0; i < n; i++) {
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
      init[i >> 6] += a[i];
    }
    presum = {init};
  }
  //! @param i defines range [0, i)
  //! @returns a[0] + a[1] + ... + a[i - 1]
  //! @time O(log(n / 64))
  //! @space O(1)
  int popcount(int i) {
    return presum.query(i >> 6) +
      __builtin_popcountll(
        mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  //! @param l,r defines range [l, r)
  //! @returns a[l] + a[l + 1] + ... + a[r - 1]
  //! @time O(log(n / 64))
  //! @space O(1)
  int popcount(int l, int r) {
    return popcount(r) - popcount(l);
  }
  //! @param i index
  //! @returns 1 iff index i is active
  //! @time O(1)
  //! @space O(1)
  bool on(int i) { return (mask[i >> 6] >> (i & 63)) & 1; }
  //! @param i index
  //! @param new_num we want to set a[i] = new_num
  //! @time O(log(n / 64))
  //! @space O(1)
  void set(int i, bool new_num) {
    if (on(i) != new_num) {
      mask[i >> 6] ^= 1ULL << (i & 63);
      presum.update(i >> 6, new_num ? 1 : -1);
    }
  }
};
//! https://codeforces.com/blog/entry/112755
//! @param tl,tr defines range [tl, tr)
//! @returns split point of range which makes the wavelet
//! tree a complete binary tree
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
//! https://ioinformatics.org/journal/v10_2016_19_37.pdf
//! https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/waveletTree.cpp
struct wavelet_tree_updates {
  int n, minv, maxv;
  vector<bool_presum> bool_presums;
  vector<bool_bit> bool_bits;
  //! @code
  //!     vi a;
  //!     ...
  //!     vi sorted(a);
  //!     sort(all(sorted));
  //!     sorted.erase(unique(all(sorted)), end(sorted));
  //!     for (int& num : a) num = lower_bound(all(sorted),
  //!     num) - begin(sorted); wavelet_tree_updates wtu(a,
  //!     0, sz(sorted), vector<bool>(sz(a), 1));
  //! @endcode
  //! @param a,a_minv,a_maxv must satisfy minv <= a[i] <
  //! maxv
  //! @param active active[i] == 1 iff index i is initially
  //! active
  //! @time O((maxv - minv) + n * log(maxv - minv))
  //! @space O((maxv - minv) + n * log(maxv - minv) / 64)
  //! for `bool_presums` and for `bool_bits`
  wavelet_tree_updates(const vector<int>& a, int a_minv,
    int a_maxv, const vector<bool>& active):
    n(ssize(a)), minv(a_minv), maxv(a_maxv),
    bool_presums(maxv - minv, vector<bool>()),
    bool_bits(2 * (maxv - minv), vector<bool>()) {
    vector<pair<int, bool>> cpy(n);
    transform(begin(a), end(a), begin(active), begin(cpy),
      [](int x, bool y) { return pair(x, y); });
    build(cpy, 0, n, minv, maxv, 1);
  }
  void build(vector<pair<int, bool>>& cpy, int l, int r,
    int tl, int tr, int v) {
    vector<bool> bools(r - l);
    transform(begin(cpy) + l, begin(cpy) + r, begin(bools),
      [](auto& p) { return p.second; });
    bool_bits[v] = bool_bit(bools);
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    auto low = [&](auto& p) { return p.first < tm; };
    transform(begin(cpy) + l, begin(cpy) + r, begin(bools),
      low);
    bool_presums[v] = bool_presum(bools);
    int mi = stable_partition(begin(cpy) + l,
               begin(cpy) + r, low) -
      begin(cpy);
    build(cpy, l, mi, tl, tm, 2 * v);
    build(cpy, mi, r, tm, tr, 2 * v + 1);
  }
  //! @param i index
  //! @param is_active we want to set active[i] = is_active
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  void set_active(int i, bool is_active) {
    if (bool_bits[1].on(i) == is_active) return;
    set_active_impl(i, is_active, minv, maxv, 1);
  }
  void set_active_impl(int i, bool is_active, int tl,
    int tr, int v) {
    bool_bits[v].set(i, is_active);
    if (tr - tl == 1) return;
    int tm = split(tl, tr),
        pi = bool_presums[v].popcount(i);
    if (bool_presums[v].on(i))
      return set_active_impl(pi, is_active, tl, tm, 2 * v);
    set_active_impl(i - pi, is_active, tm, tr, 2 * v + 1);
  }
  //! @param l,r,x,y defines rectangle: indexes in [l,
  //! r), numbers in [x, y)
  //! @returns number of active indexes i such that l <= i
  //! < r and x <= a[i] < y
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  int rect_count(int l, int r, int x, int y) {
    return rect_count_impl(l, r, x, y, minv, maxv, 1);
  }
  int rect_count_impl(int l, int r, int x, int y, int tl,
    int tr, int v) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y)
      return bool_bits[v].popcount(l, r);
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(l),
        pr = bool_presums[v].popcount(r);
    return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
      rect_count_impl(l - pl, r - pr, x, y, tm, tr,
        2 * v + 1);
  }
  //! @param l,r defines range [l, r)
  //! @param k must satisfy 1 <= k <= # active indexes in
  //! [l, r)
  //! @returns kth smallest active number in range.
  //!     - kth_smallest(l,r,1) returns the smallest
  //!     active number
  //!     - kth_smallest(l,r,rect_count(l,r,-INF,INF))
  //!     returns the largest active number
  //! @time O(log(maxv - minv) * log(n / 64))
  //! @space O(log(maxv - minv)) for recursive stack
  int kth_smallest(int l, int r, int k) {
    return kth_smallest_impl(l, r, k, minv, maxv, 1);
  }
  int kth_smallest_impl(int l, int r, int k, int tl,
    int tr, int v) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(l),
        pr = bool_presums[v].popcount(r);
    int cnt_left = bool_bits[2 * v].popcount(pl, pr);
    if (k <= cnt_left)
      return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
    return kth_smallest_impl(l - pl, r - pr, k - cnt_left,
      tm, tr, 2 * v + 1);
  }
};
