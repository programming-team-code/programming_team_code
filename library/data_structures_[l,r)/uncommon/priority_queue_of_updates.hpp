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
    int j = sz(st), t = j - 1;
    for (auto it = rbegin(mp);
      2 * (sz(st) - j) < sz(st) - t; it++) {
      int k = it->second;
      t = min(t, k);
      auto a = st[--j], b = st[k];
      st[j] = b, st[j].first->second = j;
      st[k] = a, st[k].first->second = k;
    }
    rep(i, t, sz(st)) undo();
    mp.erase(st.back().first);
    st.pop_back();
    rep(i, t, sz(st)) upd(st[i].second);
  }
};
