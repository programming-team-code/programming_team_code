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
    n((int)size(a)), mask(n / 64 + 1),
    presum((int)size(mask)) {
    for (int i = 0; i < (n); i++)
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
    for (int i = 0; i < ((int)size(mask) - 1); i++)
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
//! @code
//!   BIT<int> bit1(n);
//!   BIT<ll> bit2(n);
//! @endcode
//! @time O(n + q log n)
//! @space O(n)
template<class T> struct BIT {
  vector<T> s;
  BIT(int n): s(n) {}
  BIT(const vector<T>& a): s(a) {
    for (int i = 0; i < ((int)size(a)); i++) {
      int j = i | (i + 1);
      if (j < (int)size(a)) s[j] += s[i];
    }
  }
  void update(int i, T d) {
    for (; i < (int)size(s); i |= i + 1) s[i] += d;
  }
  T query(int ri) { // [0, ri)
    T ret = 0;
    for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
    return ret;
  }
  T query(int le, int ri) { // [le, ri)
    return query(ri) - query(le);
  }
  //! Requires bit.query(i,i+1) >= 0
  //! @returns max pos such that sum of [0,pos) < sum
  int lower_bound(T sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << __lg((int)size(s) | 1); pw;
         pw >>= 1)
      if (
        pos + pw <= (int)size(s) && s[pos + pw - 1] < sum)
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
  BIT<int> presum = {0};
  //! @param a boolean array
  //! @time O(n)
  //! @space O(n / 64)
  bool_bit(const vector<bool>& a):
    n((int)size(a)), mask(n / 64 + 1) {
    vector<int> init((n + 63) / 64);
    for (int i = 0; i < (n); i++) {
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
  //! @param le,ri defines range [le, ri)
  //! @returns a[le] + a[le + 1] + ... + a[ri - 1]
  //! @time O(log(n / 64))
  //! @space O(1)
  int popcount(int le, int ri) {
    return popcount(ri) - popcount(le);
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
//! @returns split point of range which makes the merge
//! sort tree a complete binary tree
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
//! merge sort tree with toggle element active point update
struct merge_sort_tree_updates {
  int n;
  vector<int> sorted, perm;
  vector<bool_presum> bool_presums;
  vector<bool_bit> bool_bits;
  //! @param a array
  //! @param active active[i] == 1 iff index i is initially
  //! active
  //! @time O(n log n)
  //! @space O(n + (n log n) / 64) for `bool_presums`
  //! vector
  //!        O(n + (n log n) / 64) for `bool_bits` vector
  merge_sort_tree_updates(const vector<int>& a,
    const vector<bool>& active):
    n((int)size(a)), sorted(n), perm(n),
    bool_presums(n, vector<bool>()),
    bool_bits(2 * n, vector<bool>()) {
    if (!n) return;
    vector<pair<int, bool>> cpy(n);
    for (int i = 0; i < (n); i++) cpy[i].first = i;
    build(a, active, cpy, 0, n, 1);
    for (int i = 0; i < (n); i++) {
      perm[cpy[i].first] = i;
      sorted[i] = a[cpy[i].first];
    }
  }
  void build(const vector<int>& a,
    const vector<bool>& active,
    vector<pair<int, bool>>& cpy, int tl, int tr, int v) {
    if (tr - tl == 1) {
      bool_bits[v] = bool_bit(vector<bool>(1, active[tl]));
      return;
    }
    int tm = split(tl, tr);
    build(a, active, cpy, tl, tm, 2 * v);
    build(a, active, cpy, tm, tr, 2 * v + 1);
    for (int i = tl; i < (tr); i++) cpy[i].second = i < tm;
    inplace_merge(begin(cpy) + tl, begin(cpy) + tm,
      begin(cpy) + tr, [&](auto& i, auto& j) {
        return a[i.first] < a[j.first];
      });
    vector<bool> bools(tr - tl);
    transform(begin(cpy) + tl, begin(cpy) + tr,
      begin(bools), [](auto& num) { return num.second; });
    bool_presums[v] = bool_presum(bools);
    transform(begin(cpy) + tl, begin(cpy) + tr,
      begin(bools),
      [&](auto& num) { return active[num.first]; });
    bool_bits[v] = bool_bit(bools);
  }
  //! @param i index
  //! @param is_active we want to set active[i] = is_active
  //! @time O(log(n) * log(n / 64))
  //! @space O(log(n)) for recursive stack
  void set_active(int i, bool is_active) {
    if (bool_bits[1].on(perm[i]) == is_active) return;
    set_active_impl(perm[i], is_active, 0, n, 1);
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
  //! @param le,ri,x,y defines rectangle: indexes in [le,
  //! ri), numbers in [x, y)
  //! @returns number of active indexes i such that le <= i
  //! < ri and x <= a[i] < y
  //! @time O(log(n))
  //! @space O(log(n)) for recursive stack
  int rect_count(int le, int ri, int x, int y) {
    int xi = lower_bound(begin(sorted), end(sorted), x) -
      begin(sorted);
    int yi = lower_bound(begin(sorted), end(sorted), y) -
      begin(sorted);
    return rect_count_impl(le, ri, xi, yi, 0, n, 1);
  }
  int rect_count_impl(int le, int ri, int xi, int yi,
    int tl, int tr, int v) {
    if (ri <= tl || tr <= le) return 0;
    if (le <= tl && tr <= ri)
      return bool_bits[v].popcount(xi, yi);
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(xi),
        pr = bool_presums[v].popcount(yi);
    return rect_count_impl(le, ri, pl, pr, tl, tm, 2 * v) +
      rect_count_impl(le, ri, xi - pl, yi - pr, tm, tr,
        2 * v + 1);
  }
  //! @param x,y defines range of numbers [x, y)
  //! @param k must satisfy 1 <= k <= number of active
  //! indexes i such that x <= a[i] < y
  //! @returns the kth smallest active index i such that x
  //! <= a[i] < y
  //!     - kth_smallest(x,y,1) returns the smallest active
  //!     index i such that x <= a[i] < y
  //!     - kth_smallest(x,y,rect_count(0,n,x,y)) returns
  //!     the largest active index i such that x <= a[i] <
  //!     y
  //! @time O(log(n))
  //! @space O(log(n)) for recursive stack
  int kth_smallest(int x, int y, int k) {
    int xi = lower_bound(begin(sorted), end(sorted), x) -
      begin(sorted);
    int yi = lower_bound(begin(sorted), end(sorted), y) -
      begin(sorted);
    return kth_smallest_impl(xi, yi, k, 0, n, 1);
  }
  int kth_smallest_impl(int xi, int yi, int k, int tl,
    int tr, int v) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr),
        pl = bool_presums[v].popcount(xi),
        pr = bool_presums[v].popcount(yi);
    int cnt_left = bool_bits[2 * v].popcount(pl, pr);
    if (k <= cnt_left)
      return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
    return kth_smallest_impl(xi - pl, yi - pr,
      k - cnt_left, tm, tr, 2 * v + 1);
  }
};
