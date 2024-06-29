/**
 * Trie on bits. Can be thought of as a multiset of integers.
 */
template <class T> struct binary_trie {
  int mx_bit;
  struct node {
    int sub_sz = 0;
    array<int, 2> next = {-1, -1};
  };
  vector<node> t;
  /**
   * @code{.cpp}
         binary_trie<int> bt; //mx_bit = 30
         binary_trie<ll> bt; //mx_bit = 62
   * @endcode
   */
  binary_trie() : mx_bit(8 * sizeof(T) - 2), t(1) {}
  /**
   * @param num integer
   * @param delta 1 to insert num, -1 to remove num
   * @time O(mx_bit)
   * @space O(mx_bit) new nodes are pushed back onto `t`
   */
  void update(T num, int delta) {
    t[0].sub_sz += delta;
    for (int u = 0, bit = mx_bit; bit >= 0; bit--) {
      bool b = (num >> bit) & 1;
      if (t[u].next[b] == -1) {
        t[u].next[b] = (int)size(t);
        t.emplace_back();
      }
      u = t[u].next[b];
      t[u].sub_sz += delta;
    }
  }
  /**
   * @param num integer
   * @returns number of occurances of num in the multiset
   * @time O(mx_bit)
   * @space O(1)
   */
  int count(T num) {
    int u = 0;
    for (int bit = mx_bit; bit >= 0; bit--) {
      bool b = (num >> bit) & 1;
      if (t[u].next[b] == -1) return 0;
      u = t[u].next[b];
    }
    return t[u].sub_sz;
  }
  /**
   * @param num integer
   * @returns integer x such that x is in this multiset, and the number of
   * (x^num) is minimum.
   * @time O(mx_bit)
   * @space O(1)
   */
  T min_xor(T num) {
    assert(t[0].sub_sz > 0);
    T res = 0;
    for (int u = 0, bit = mx_bit; bit >= 0; bit--) {
      bool b = (num >> bit) & 1;
      int v = t[u].next[b];
      if (v != -1 && t[v].sub_sz > 0)
        u = v, res |= T(b) << bit;
      else
        u = t[u].next[!b], res |= T(!b) << bit;
    }
    return res;
  }
};
