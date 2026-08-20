#pragma once
//! https://codeforces.com/blog/entry/111117
//! @code
//!   RollbackUF uf(n);
//!   vector<int> hist;
//!   pq_updates pq([&](auto upd) {
//!     hist.push_back(uf.time());
//!     uf.join(upd.first, upd.second);
//!   }, [&]() {
//!     uf.rollback(hist.back());
//!     hist.pop_back();
//!   }, pair<int, int>{});
//!   pq.push(pri, {u, v});
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F, class G, class H> struct pq_updates {
  F update;
  G undo;
  vector<pair<multimap<int, int>::iterator, H>> st, buf;
  multimap<int, int> mp;
  pq_updates(F update, G undo, H):
    update(update), undo(undo) {}
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
      update(st[i].second);
      st[i].first->second = i;
    }
  }
  void push(int pri, H upd_params) {
    update(upd_params);
    st.emplace_back(mp.emplace(pri, sz(st)), upd_params);
  }
};
