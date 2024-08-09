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
  int popcount(int i) {
    return presum[i >> 6] + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
  }
  /**
   * @param i index
   * @returns 1 iff a[i] was on
   * @time O(1)
   * @space O(1)
   */
  bool on(int i) {
    return (mask[i >> 6] >> (i & 63)) & 1;
  }
};
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the wavelet tree a complete
 * binary tree
 */
int split(int tl, int tr) {
  int pw2 = 1 << __lg(tr - tl);
  return min(tl + pw2, tr - pw2 / 2);
}
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree {
  int n, minv, maxv;
  vector<bool_presum> bool_presums;
  vector<vector<int64_t>> presums;
  /**
   * @code{.cpp}
         vi a;
         ...
         vi sorted(a);
         sort(all(sorted));
         sorted.erase(unique(all(sorted)), end(sorted));
         for (int& num : a) num = lower_bound(all(sorted), num) - begin(sorted);
         wavelet_tree wt(a, 0, sz(sorted));
   * @endcode
   * @param a,a_minv,a_maxv must satisfy minv <= a[i] < maxv
   * @time O((maxv - minv) + n * log(maxv - minv))
   * @space O((maxv - minv) + n * log(maxv - minv) / 64) for `bool_presums`
   *        O((maxv - minv) + n * log(maxv - minv))      for `presums`
   */
  wavelet_tree(vector<int> a, int a_minv, int a_maxv) : n((int)size(a)), minv(a_minv), maxv(a_maxv), bool_presums(maxv - minv, vector<bool>()), presums(maxv - minv) {
    build(a, 0, n, minv, maxv, 1);
  }
  void build(vector<int>& a, int le, int ri, int tl, int tr, int v) {
    if (tr - tl <= 1) return;
    int tm = split(tl, tr);
    auto low = [&](int num) { return num < tm; };
    vector<bool> bools(ri - le);
    transform(begin(a) + le, begin(a) + ri, begin(bools), low);
    bool_presums[v] = bool_presum(bools);
    presums[v].resize(ri - le + 1);
    inclusive_scan(begin(a) + le, begin(a) + ri, begin(presums[v]) + 1, plus<int64_t>(), 0LL);
    int mi = stable_partition(begin(a) + le, begin(a) + ri, low) - begin(a);
    build(a, le, mi, tl, tm, 2 * v);
    build(a, mi, ri, tm, tr, 2 * v + 1);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), numbers in [x, y)
   * @returns number of indexes i such that le <= i < ri and x <= a[i] < y
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int rect_count(int le, int ri, int x, int y) {
    return rect_count_impl(le, ri, x, y, minv, maxv, 1);
  }
  int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y) return ri - le;
    int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
    return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
           rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
  }
  /**
   * @param le,ri,x,y defines rectangle: indexes in [le, ri), numbers in [x, y)
   * @returns sum of numbers a[i] such that le <= i < ri and x <= a[i] < y
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int64_t rect_sum(int le, int ri, int x, int y) {
    return rect_sum_impl(le, ri, x, y, minv, maxv, 1);
  }
  int64_t rect_sum_impl(int le, int ri, int x, int y, int tl, int tr, int v) {
    if (y <= tl || tr <= x) return 0;
    if (x <= tl && tr <= y) return (tr - tl == 1 ? int64_t(tl) * (ri - le) : presums[v][ri] - presums[v][le]);
    int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
    return rect_sum_impl(pl, pr, x, y, tl, tm, 2 * v) +
           rect_sum_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
  }
  /**
   * @param le,ri defines range [le, ri)
   * @param k must satisfy 1 <= k <= ri - le
   * @returns kth smallest number in range.
   *     - kth_smallest(le,ri,1) returns the min
   *     - kth_smallest(le,ri,(ri-le)) returns the max
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int kth_smallest(int le, int ri, int k) {
    return kth_smallest_impl(le, ri, k, minv, maxv, 1);
  }
  int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) {
    if (tr - tl == 1) return tl;
    int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
    if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
    return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
  }
  /**
   * @param le,ri defines range [le, ri)
   * @param k must satisfy 0 <= k <= ri - le
   * @returns the sum of the k smallest numbers in range.
   *     - kth_sum(le,ri,0) returns 0
   *     - kth_sum(le,ri,1) returns the min
   *     - kth_sum(le,ri,(ri-le)) returns the sum
   * @time O(log(maxv - minv))
   * @space O(log(maxv - minv)) for recursive stack
   */
  int64_t kth_sum(int le, int ri, int k) {
    return kth_sum_impl(le, ri, k, minv, maxv, 1);
  }
  int64_t kth_sum_impl(int le, int ri, int k, int tl, int tr, int v) {
    if (tr - tl == 1) return int64_t(k) * tl;
    int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
    if (k <= pr - pl) return kth_sum_impl(pl, pr, k, tl, tm, 2 * v);
    int64_t sum_left = (tm - tl == 1 ? int64_t(tl) * (pr - pl) : presums[2 * v][pr] - presums[2 * v][pl]);
    return sum_left + kth_sum_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
  }
};
/**
 * @see https://codeforces.com/blog/entry/12143#comment-324162
 *
 * subarray [le, ri] has "center" i = le + ri
 *
 * center 0 2 4 6 8
 * string b a a b a
 * center  1 3 5 7
 *
 * man = {0, 1, 1, 0, 2, 3, 2, 4, 4}
 *
 * for "center" `i`, man[i] stores minimum index `le` such that [le, i - le] is a palindrome
 *
 * @param s string/vector
 * @returns see above
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T> vector<int> manacher(const T& s) {
  int n = (int)size(s), p = 0;
  vector<int> man(max(0, 2 * n - 1));
  for (int i = 0; i < (2 * n - 1); i++) {
    int ri = i <= 2 * (p - man[p]) ? p - max(man[2 * p - i], man[p]) : i / 2;
    man[i] = i - ri;
    while (man[i] > 0 && ri + 1 < n && s[man[i] - 1] == s[ri + 1])
      man[i]--, ri++, p = i;
  }
  return man;
}
/**
 * @param le,ri defines range [le, ri)
 * @returns le + (le + 1) + ... + (ri - 1)
 * @time O(1)
 * @space O(1)
 */
int64_t sum_consecutive(int le, int ri) {
  return int64_t(ri - le) * (le + ri - 1) / 2;
}
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
template <class T> struct count_pal_query {
  int n;
  vector<int> man;
  wavelet_tree wt_le, wt_ri;
  /**
   * @param s string/vector
   * @time O(n log n)
   * @space O(n log n) for wavelet trees
   */
  count_pal_query(const T& s) : n((int)size(s)), man(manacher(s)), wt_le(man, 0, n), wt_ri(init()) {}
  wavelet_tree init() {
    vector<int> right((int)size(man));
    for (int i = 0; i < ((int)size(man)); i++)
      right[i] = i - man[i] + 1;
    return {right, 1, n + 1};
  }
  /**
   * @param le,ri defines substring [le, ri) of s
   * @returns number of palindromic substrings of s.substr(le, ri - le)
   * @time O(log n)
   * @space O(1)
   */
  int64_t count_pals(int le, int ri) {
    assert(le < ri);
    int man_le = 2 * le, man_ri = 2 * ri - 1, man_mi = (man_le + man_ri) / 2;
    // sum over range [man_le, man_mi) of:
    //     i / 2 - max(man[i], le) + 1
    int64_t cnt = -1LL * wt_le.rect_count(man_le, man_mi, 0, le) * le;
    cnt -= wt_le.rect_sum(man_le, man_mi, le, n);
    cnt += sum_consecutive(le, man_mi / 2) + sum_consecutive(le, (man_mi + 1) / 2);
    cnt += man_mi - man_le;
    // sum over range [man_mi, man_ri) of:
    //     min(right[i], ri) - (i + 1) / 2
    cnt += int64_t(wt_ri.rect_count(man_mi, man_ri, ri, n + 1)) * ri;
    cnt += wt_ri.rect_sum(man_mi, man_ri, 1, ri);
    cnt -= sum_consecutive((man_mi + 1) / 2, ri) + sum_consecutive(man_mi / 2 + 1, ri);
    return cnt;
  }
};
