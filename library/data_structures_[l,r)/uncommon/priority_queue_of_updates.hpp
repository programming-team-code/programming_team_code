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
  multimap<int, int> mp;
  vector<pair<decltype(end(mp)), H>> st;
  pq_updates(F upd, G undo): upd(upd), undo(undo) {}
  void push(int pri, H upd_params) {
    upd(upd_params);
    st.emplace_back(mp.emplace(pri, sz(st)), upd_params);
  }
  void pop_min() {
    int l = sz(st), r = l;
    for (auto& [_, i] : mp) {
      l = min(l, i);
      swap(st[i], st[--r]);
      swap(st[i].first->second, i);
      if (r - l <= sz(st) - r) break;
    }
    rep(i, l, sz(st)) undo();
    mp.erase(st.back().first);
    st.pop_back();
    rep(i, l, sz(st)) upd(st[i].second);
  }
};
