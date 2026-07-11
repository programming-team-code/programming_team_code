//! @code
//!   binary_trie bt;
//!   bt.update(num, 1); // insert
//!   bt.update(num, -1); // erase
//! @endcode
//! requires 0 <= num < 2^61
//! walk requires a non-empty trie
//! @time O(q * mx_bit)
//! @space O(q * mx_bit)
const int64_t mx_bit = 1LL << 60;
struct binary_trie {
  struct node {
    int siz = 0;
    array<int, 2> nxt = {-1, -1};
  };
  deque<node> t;
  binary_trie(): t(1) {}
  void update(int64_t num, int delta) {
    int v = 0;
    for (int64_t bit = mx_bit; bit; bit >>= 1) {
      bool b = num & bit;
      if (t[v].nxt[b] == -1) {
        t[v].nxt[b] = ssize(t);
        t.emplace_back();
      }
      v = t[v].nxt[b];
      t[v].siz += delta;
    }
  }
  int64_t walk(int64_t num) {
    int v = 0;
    int64_t res = 0;
    for (int64_t bit = mx_bit; bit; bit >>= 1) {
      bool b = num & bit;
      int u = t[v].nxt[b];
      if (u != -1 && t[u].siz > 0) v = u, res |= num & bit;
      else v = t[v].nxt[!b], res |= (~num) & bit;
    }
    return res;
  }
};
