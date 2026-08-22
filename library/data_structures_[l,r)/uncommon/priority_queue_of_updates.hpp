#pragma once
#include "../../../kactl/content/data-structures/UnionFindRollback.h"
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
using H = pii;
template<class F, class G> struct pq_updates {
  F upd;
  G undo;
  vector<pair<multimap<int, int>::iterator, H>> st;
  multimap<int, int> mp;
  pq_updates(F upd, G undo): upd(upd), undo(undo) {}
  void push(int pri, H upd_params) {
    upd(upd_params);
    st.emplace_back(mp.emplace(pri, sz(st)), upd_params);
  }
  void pop() {
    int r = sz(st), l = r - 1;
    for (auto it = rbegin(mp); r - l > sz(st) - r; it++) {
      l = min(l, it->second);
      if (--r != it->second) {
        swap(st[r], st[it->second]);
        swap(it->second, st[it->second].first->second);
      }
    }
    rep(i, l, sz(st)) undo();
    mp.erase(st.back().first);
    st.pop_back();
    rep(i, l, sz(st)) upd(st[i].second);
  }
};
