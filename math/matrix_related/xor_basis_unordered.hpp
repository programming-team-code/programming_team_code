//! https://codeforces.com/blog/entry/68953
//! https://codeforces.com/blog/entry/100066?#comment-887897
//! properties:
//! - shrink(v) == shrink(shrink(v))
//! - for x in b: (bit_floor(x) & shrink(v)) == 0
//! - for 0 <= i < j < sz(b): (bit_floor(b[i]) & b[j]) == 0
//! @time O(32)
//! @space O(32)
struct basis {
  vector<int> b;
  int shrink(int v) {
    for (int x : b) v = min(v, v ^ x);
    return v;
  }
  bool insert(int v) {
    return (v = shrink(v)) ? b.push_back(v), 1 : 0;
  }
};
