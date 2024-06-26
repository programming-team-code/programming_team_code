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
