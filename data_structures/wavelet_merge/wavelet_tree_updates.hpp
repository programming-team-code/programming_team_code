/**
 * @see https://github.com/dacin21/dacin21_codebook /blob/master/trees/wavelet_matrix.cpp
 *
 * space efficient boolean array with prefix sum query
 * note `>> 6` is the same as `/ 64`
 * note `& 63` is the same as `% 64`
 */
struct bool_presum {
  int n;
  vector<uint64_t> mask;
  vector<int> presum;
  /**
   * @param a boolean array
   * @time O(n)
   * @space O(n / 64)
   */
  bool_presum(const vector<bool>& a) : n((int)size(a)), mask(n / 64 + 1), presum((int)size(mask)) {
    for (int i = 0; i < (n); i++)
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
    for (int i = 0; i < ((int)size(mask) - 1); i++)
      presum[i + 1] = __builtin_popcountll(mask[i]) + presum[i];
  }
  /**
   * @param i defines range [0, i)
   * @returns a[0] + a[1] + ... + a[i - 1]
   * @time O(1)
   * @space O(1)
   */
  inline int popcount(int i) {
    assert(0 <= i && i <= n);
    return presum[i >> 6] + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  /**
   * @param i index
   * @returns 1 iff a[i] was on
   * @time O(1)
   * @space O(1)
   */
  inline bool on(int i) {
    assert(0 <= i && i < n);
    return (mask[i >> 6] >> (i & 63)) & 1;
  }
};
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
    for (int i = 0; i < ((int)size(a)); i++) {
      int j = i | (i + 1);
      if (j < (int)size(a)) s[j] += s[i];
    }
  }
  /**
   * @param i index
   * @param d delta
   * @time O(log n)
   * @space O(1)
   */
  inline void update(int i, T d) {
    assert(0 <= i && i < (int)size(s));
    for (; i < (int)size(s); i |= i + 1) s[i] += d;
  }
  /**
   * @param ri defines range [0, ri)
   * @returns a[0] + a[1] + ... + a[ri - 1]
   * @time O(log n)
   * @space O(1)
   */
  inline T query(int ri) {
    assert(0 <= ri && ri <= (int)size(s));
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
    for (int pw = 1 << __lg((int)size(s) | 1); pw; pw >>= 1)
      if (pos + pw <= (int)size(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos + 1;
  }
};
/**
 * @see https://github.com/dacin21/dacin21_codebook /blob/master/trees/wavelet_matrix_updates.cpp
 *
 * space efficient boolean array with range sum query, and point update
 * note `>> 6` is the same as `/ 64`
 * note `& 63` is the same as `% 64`
 */
struct bool_bit {
  int n;
  vector<uint64_t> mask;
  BIT<int> presum;
  /**
   * @param a boolean array
   * @time O(n)
   * @space O(n / 64)
   */
  bool_bit(const vector<bool>& a) : n((int)size(a)), mask(n / 64 + 1) {
    vector<int> init((n + 63) / 64);
    for (int i = 0; i < (n); i++) {
      mask[i >> 6] |= (uint64_t(a[i]) << (i & 63));
      init[i >> 6] += a[i];
    }
    presum = {init};
  }
  /**
   * @param i defines range [0, i)
   * @returns a[0] + a[1] + ... + a[i - 1]
   * @time O(log(n / 64))
   * @space O(1)
   */
  inline int popcount(int i) {
    assert(0 <= i && i <= n);
    return presum.query(i >> 6) + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  /**
   * @param le,ri defines range [le, ri)
   * @returns a[le] + a[le + 1] + ... + a[ri - 1]
   * @time O(log(n / 64))
   * @space O(1)
   */
  inline int popcount(int le, int ri) {
    assert(le <= ri);
    return popcount(ri) - popcount(le);
  }
  /**
   * @param i index
   * @returns 1 iff index i is active
   * @time O(1)
   * @space O(1)
   */
  inline bool on(int i) {
    assert(0 <= i && i < n);
    return (mask[i >> 6] >> (i & 63)) & 1;
  }
  /**
   * @param i index
   * @param new_num we want to set a[i] = new_num
   * @time O(log(n / 64))
   * @space O(1)
   */
  void set(int i, bool new_num) {
    assert(0 <= i && i < n);
    if (on(i) != new_num) {
      mask[i >> 6] ^= 1ULL << (i & 63);
      presum.update(i >> 6, new_num ? 1 : -1);
    }
  }
};
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the wavelet tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree_updates {
  int n, minv, maxv;
  vector<bool_presum> bool_presums;
  vector<bool_bit> bool_bits;
  /**
   * @code{.cpp}
         vi a;
         ...
         vi sorted(a);
         sort(all(sorted));
         sorted.erase(unique(all(sorted)), end(sorted));
         for (int& num : a) num = lower_bound(all(sorted), num) - begin(sorted);
         wavelet_tree_updates wtu(a, 0, sz(sorted), vector<bool>(sz(a), 1));
   * @endcode
   * @param a,a_minv,a_maxv must satisfy minv <= a[i] < maxv
   * @param active active[i] == 1 iff index i is initially active
   * @time O((maxv - minv) + n * log(maxv - minv))
   * @space O((maxv - minv) + n * log(maxv - minv) / 64) for `bool_presums` and for `bool_bits`
   */
  wavelet_tree_updates(const vector<int>& a, int a_minv, int a_maxv, const vector<bool>& active) : n((int)size(a)), minv(a_minv), maxv(a_maxv), bool_presums(maxv - minv, vector<bool>()), bool_bits(2 * (maxv - minv), vector<bool>()) {
    assert(minv < maxv && (int)size(active) == n);
    vector<pair<int, bool>> cpy(n);
    transform(begin(a), end(a), begin(active), begin(cpy), [](int x, bool y) { return pair(x, y); });
    build(cpy, 0, n, minv, maxv, 1);
  }
  void build(vector<pair<int, bool>>& cpy, int le, int ri, int tl, int tr, int u) {
    vector<bool> bools(ri - le);
    transform(begin(cpy) + le, begin(cpy) + ri, begin(bools), [](auto& p) { return p.second; });
    bool_bits[u] = bool_bit(bools);
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    auto low = [&](auto& p) { return p.first < tm; };
    transform(begin(cpy) + le, begin(cpy) + ri, begin(bools), low);
    bool_presums[u] = bool_presum(bools);
    int mi = stable_partition(begin(cpy) + le, begin(cpy) + ri, low) - begin(cpy);
    build(cpy, le, mi, tl, tm, 2 * u);
    build(cpy, mi, ri, tm, tr, 2 * u + 1);
  }
  /**
   * @param i index
   * @param is_active we want to set active[i] = is_active
   * @time O(log(maxv - minv) * log(n / 64))
   * @space O(log(maxv - minv)) for recursive stack
   */
  void set_active(int i, bool is_active) {
    assert(0 <= i && i < n);
    if (bool_bits[1].on(i) == is_active) return;
    set_active_impl(i, is_active, minv, maxv, 1);
  }
  void set_active_impl(int i, bool is_active, int tl, int tr, int u) {
    bool_bits[u].set(i, is_active);
    if (tr - tl == 1) return;
    int tm = split(tl, tr), pi = bool_presums[u].popcount(i);
    if (bool_presums[u].on(i)) return set_active_impl(pi, is_active, tl, tm, 2 * u);
    set_active_impl(i - pi, is_active, tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), numbers in [x, y)
   * @returns number of active indexes i such that le <= i < ri and x <= a[i] < y
   * @time O(log(maxv - minv) * log(n / 64))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int rect_count(int le, int ri, int x, int y) {
    assert(0 <= le && le <= ri && ri <= n && x <= y);
    return rect_count_impl(le, ri, x, y, minv, maxv, 1);
  }
  int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int u) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y) return bool_bits[u].popcount(le, ri);
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    return rect_count_impl(pl, pr, x, y, tl, tm, 2 * u) +
           rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * u + 1);
  }
  /**
   * @param le,ri defines range [le, ri)
   * @param k must satisfy 1 <= k <= # active indexes in [le, ri)
   * @returns kth smallest active number in range.
   *     - kth_smallest(le,ri,1) returns the smallest active number
   *     - kth_smallest(le,ri,rect_count(le,ri,-INF,INF)) returns the largest active number
   * @time O(log(maxv - minv) * log(n / 64))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int kth_smallest(int le, int ri, int k) {
    assert(0 <= le && ri <= n);
    assert(1 <= k && k <= bool_bits[1].popcount(le, ri));
    return kth_smallest_impl(le, ri, k, minv, maxv, 1);
  }
  int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int u) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr), pl = bool_presums[u].popcount(le), pr = bool_presums[u].popcount(ri);
    int cnt_left = bool_bits[2 * u].popcount(pl, pr);
    if (k <= cnt_left) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * u);
    return kth_smallest_impl(le - pl, ri - pr, k - cnt_left, tm, tr, 2 * u + 1);
  }
};
