#pragma once
//! https://codeforces.com/blog/entry/111117
//! @code
//!   RollbackUF uf(n);
//!   vector<int> hist;
//!   vector<pair<int, int>> updates;
//!   pq_updates pq([&](int id) {
//!     hist.push_back(uf.time());
//!     uf.join(updates[id].first, updates[id].second);
//!   }, [&]() {
//!     uf.rollback(hist.back());
//!     hist.pop_back();
//!   });
//!   updates.push_back({u, v});
//!   pq.push(pri, ssize(updates) - 1);
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F, class G> struct pq_updates {
  F update;
  G undo;
  vector<pair<multimap<int, int>::iterator, int>> st, buf;
  multimap<int, int> mp;
  pq_updates(F update, G undo):
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
  void push(int pri, int update_id) {
    update(update_id);
    st.emplace_back(mp.emplace(pri, sz(st)), update_id);
  }
};
