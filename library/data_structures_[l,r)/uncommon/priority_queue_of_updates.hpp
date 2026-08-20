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
  vector<pair<multimap<int, int>::iterator, H>> st, buf;
  multimap<int, int> mp;
  pq_updates(F upd, G undo): upd(upd), undo(undo) {}
  void push(int pri, H upd_params) {
    upd(upd_params);
    st.emplace_back(mp.emplace(pri, sz(st)), upd_params);
  }
  void pop() {
    buf.clear();
    int t = sz(st) - 1;
    for (auto it = rbegin(mp); 2 * sz(buf) < sz(st) - t;
      it++) {
      buf.push_back(st[it->second]);
      t = min(t, it->second);
      it->second = -1;
    }
    rep(i, t, sz(st)) undo();
    ranges::reverse_copy(buf,
      remove_if(t + all(st),
        [](auto& x) { return x.first->second == -1; }));
    st.pop_back();
    mp.erase(buf[0].first);
    rep(i, t, sz(st)) {
      upd(st[i].second);
      st[i].first->second = i;
    }
  }
};
