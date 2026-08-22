//! https://codeforces.com/blog/entry/111117
//! @code
//!   RollbackUF uf(n);
//!   vector<int> hist;
//!   pq_updates pq([&](H& upd) {
//!     hist.push_back(uf.time());
//!     uf.join(upd.first, upd.second);
//!   }, [&]() {
//!     uf.rollback(hist.back());
//!     hist.pop_back();
//!   });
//!   pq.push(pri, {u, v});
//! @endcode
//! @time O(n log n)
//! @space O(n)
using H = pair<int, int>;
template<class F, class G> struct pq_updates {
  F upd;
  G undo;
  multimap<int, int> mp;
  vector<pair<decltype(end(mp)), H>> st;
  pq_updates(F upd, G undo): upd(upd), undo(undo) {}
  void push(int pri, H upd_params) {
    upd(upd_params);
    st.emplace_back(mp.emplace(pri, ssize(st)), upd_params);
  }
  void pop_min() {
    int l = ssize(st), r = l;
    for (auto& [_, i] : mp) {
      l = min(l, i);
      swap(st[i], st[--r]);
      swap(st[i].first->second, i);
      if (r - l <= ssize(st) - r) break;
    }
    for (int i = l; i < ssize(st); i++) undo();
    mp.erase(st.back().first);
    st.pop_back();
    for (int i = l; i < ssize(st); i++) upd(st[i].second);
  }
};
/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
struct RollbackUF {
  vector<int> e;
  vector<pair<int, int>> st;
  RollbackUF(int n): e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return ssize(st); }
  void rollback(int t) {
    for (int i = time(); i-- > t;) e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
