//! https://codeforces.com/blog/entry/111117
//! @code
//!     dsu_restorable dsu_r(n);
//!     pq_updates<dsu_restorable, int, int> pq(dsu_r);
//!     rep (i, 0, n) pq.ds.add(i, initial_nums[i]);
//!     //or
//!     pq.ds.subtree = initial_nums;
//!     pq.push_update(u, v, curr_pri);
//!     cout << pq.ds.sum(v) << '\n';
//! @endcode
//! @time n interweaved calls to pop_update, push_update
//! take O(T(n)*nlogn) where O(T(n)) = time complexity of
//! DS::join and DS::undo
//! @space n interweaved calls to pop_update, push_update
//! uses O(n) space
template<class DS, class... ARGS> struct pq_updates {
  DS ds;
  using upd =
    pair<tuple<ARGS...>, map<int, int>::iterator>;
  vector<upd> upd_st;
  map<int, int>
    mp; //!< priority -> index into update stack
  //! @param ds any data structure with member functions
  //! `join` and `undo`
  pq_updates(DS& ds): ds(ds) {}
  //! Remove update with max priority
  //! @time O(log(n) + k*T(n)) where k = # of pops off the
  //! update stack
  //! @space a temporary vector of size O(k) is used to
  //! store popped updates; size of `upd_st`, `mp` member
  //! variables decreases by 1
  void pop_update() {
    vector<upd> extra;
    int idx = ssize(upd_st) - 1, lowest_pri = INT_MAX;
    for (auto it = rbegin(mp);
      2 * ssize(extra) < ssize(upd_st) - idx; it++) {
      auto [pri, idx_sk] = *it;
      extra.push_back(upd_st[idx_sk]);
      idx = min(idx, idx_sk), lowest_pri = pri;
    }
    auto it = remove_if(idx + begin(upd_st), end(upd_st),
      [&](auto& curr) {
        return curr.second->first >= lowest_pri;
      });
    reverse_copy(begin(extra), end(extra), it);
    for (int i = idx; i < ssize(upd_st); i++) ds.undo();
    upd_st.pop_back();
    mp.erase(prev(end(mp)));
    for (int i = idx; i < ssize(upd_st); i++) {
      apply(&DS::join,
        tuple_cat(make_tuple(&ds), upd_st[i].first));
      upd_st[i].second->second = i;
    }
  }
  //! @param args arguments to DS::join
  //! @param priority must be distinct, can be negative
  //! @time O(log(n) + T(n))
  //! @space an new update is allocated, inserted into
  //! `upd_st`, `mp` member variables
  void push_update(ARGS... args, int priority) {
    ds.join(args...);
    auto [it, ins] = mp.emplace(priority, ssize(upd_st));
    assert(ins);
    upd_st.emplace_back(make_tuple(args...), it);
  }
};
