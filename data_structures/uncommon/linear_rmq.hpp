/**
 * @code{.cpp}
       vector<ll> a;
       vi le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp transitive compare operator
 * @returns vector le where le[i] = max index such that: le[i] < i and
 *          cmp(a[le[i]], a[i]). If no index exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
  vector<int> le((int)size(a));
  for (int i = 0; i < ((int)size(a)); i++)
    for (le[i] = i - 1; le[i] >= 0 && !cmp(a[le[i]], a[i]);) le[i] = le[le[i]];
  return le;
}
/**
 * @code{.cpp}
       vector<ll> a;
       auto le = mono_st(a, less()), ri = mono_range(le); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param le monotonic stack array of a
 * @returns vector ri where ri[i] = min index such that: i < ri[i] and
 *          !cmp(a[i], a[ri[i]]). If no index exists, ri[i] = n
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> mono_range(const vector<int>& le) {
  vector<int> ri((int)size(le), (int)size(le));
  for (int i = 0; i < ((int)size(le)); i++)
    for (int j = i - 1; j != le[i]; j = le[j]) ri[j] = i;
  return ri;
}
/**
 *   when cmp is less():
 *   a = {2, 1, 3, 1, 1, 0, 2, 2, 1, 0, 2}
 *       (---------------------------x---)
 *       (---------------x---------)   (x)
 *       (------------x) | (------x)    |
 *       (---------x)    | (---x) |     |
 *       (---x---)       | (x) |  |     |
 *       (x) | (x)       |  |  |  |     |
 *        |  |  |        |  |  |  |     |
 * index: 0  1  2  3  4  5  6  7  8  9  10
 *
 * @code{.cpp}
       auto le = mono_st(a, less()), p = cart_binary_tree(le); // right-most min is root
       auto le = mono_st(a, less_equal()), p = cart_binary_tree(le); // left-most min is root
       auto le = mono_st(a, greater()), p = cart_binary_tree(le); // right-most max is root
       auto le = mono_st(a, greater_equal()), p = cart_binary_tree(le); // left-most max is root
 * @endcode
 * @param le monotonic stack of array `a`
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> cart_binary_tree(const vector<int>& le) {
  vector<int> p(le);
  for (int i = 0; i < ((int)size(p)); i++)
    for (int j = i - 1; j != le[i]; j = le[j])
      if (le[j] == le[i]) p[j] = i;
  return p;
}
inline int bit_floor(unsigned x) { return x ? 1 << __lg(x) : 0; }
/**
 * @see On Finding Lowest Common Ancestors: Simplification and Parallelization
 * by Baruch Schieber, Uzi Vishkin, April 1987
 */
template <class T, class F> struct linear_rmq {
  int n;
  F cmp;
  vector<T> a;
  vector<int> head;
  vector<unsigned> label, asc;
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
  linear_rmq(const vector<T>& a_a, F a_cmp) : n((int)size(a_a)), cmp(a_cmp), a(a_a), head(n + 1), label(n), asc(n) {
    vector<int> le(mono_st(a, cmp)), ri(mono_range(le)), p(cart_binary_tree(le));
    for (int i = 0; i < (n); i++)
      label[i] = ri[i] & -bit_floor(unsigned((le[i] + 1) ^ ri[i]));
    for (int i = 0; i < (n); i++)
      if (p[i] == -1 || label[p[i]] != label[i]) {
        head[label[i]] = p[i];
        int to_add = label[i] & -label[i];
        asc[le[i] + 1] += to_add;
        if (ri[i] < n) asc[ri[i]] -= to_add;
      }
    partial_sum(begin(asc), end(asc), begin(asc));
  }
  inline int lift(int u, unsigned j) {
    auto k = bit_floor(asc[u] ^ j);
    return k == 0 ? u : head[(label[u] & -k) | k];
  }
  /**
   * @param le,ri defines range [min(le, ri), max(le, ri)]
   * @returns index of min/max of range
   * @time O(1)
   * @space O(1)
   */
  inline int query_idx(int le, int ri) {
    auto [x, y] = minmax(label[le], label[ri]);
    auto j = asc[le] & asc[ri] & -bit_floor((x - 1) ^ y);
    return cmp(a[le = lift(le, j)], a[ri = lift(ri, j)]) ? le : ri;
  }
};
