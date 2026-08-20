#pragma once
//! https://codeforces.com/blog/entry/111117
//! @code
//!   vector<pair<int, int>> updates;
//!   pq_updates pq([&](int update_id) {},
//!                 [&]() {});
//!   updates.push_back({u, v});
//!   pq.push(pri, ssize(updates) - 1);
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F, class G> struct pq_updates {
  F update;
  G undo;
  using upd = pair<multimap<int, int>::iterator, int>;
  vector<upd> st;
  multimap<int, int> mp;
  pq_updates(F update, G undo):
    update(update), undo(undo) {}
  void pop() {
    vector<upd> extra;
    int t = sz(st) - 1;
    for (auto it = rbegin(mp); 2 * sz(extra) < sz(st) - t;
      it++) {
      extra.push_back(st[it->second]);
      t = min(t, it->second);
      it->second = -1;
    }
    rep(i, t, sz(st)) undo();
    ranges::reverse_copy(extra,
      remove_if(t + all(st),
        [](upd& x) { return x.first->second == -1; }));
    st.pop_back();
    mp.erase(extra[0].first);
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
