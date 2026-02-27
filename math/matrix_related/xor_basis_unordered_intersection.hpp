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
//! https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
//! @time O(32^2)
//! @space O(32)
basis intersection(const basis& u, const basis& v) {
  vector<pair<int, int>> w(ssize(u.b));
  for (int i = 0; i < ssize(w); i++)
    w[i] = {u.b[i], u.b[i]};
  basis res;
  for (int e : v.b) {
    int s = 0;
    for (auto [x, y] : w)
      if ((e ^ x) < e) e ^= x, s ^= y;
    if (e) w.emplace_back(e, s);
    else res.insert(s);
  }
  return res;
}
