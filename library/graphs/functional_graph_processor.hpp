#pragma once
//! https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
//! @code
//!   // 0 <= a[i] < n
//!   auto [t, cycle] = func_graph(a);
//!   if (auto id = t[v].cyc_pos)
//!     assert(v == cycle[id->first][id->second]);
//! @endcode
//! t[v].root_of = first reachable node in a cycle
//! t[v].childs = forest of reversed edges not in cycles
//! @time O(n)
//! @space O(n)
struct func_graph {
  struct node {
    int root_of;
    optional<pii> cyc_pos;
    vi childs;
  };
  vector<node> t;
  vector<vi> cycle;
  func_graph(const vi &a): t(sz(a)) {
    vi state(sz(a));
    rep(i, 0, sz(a)) {
      if (state[i] == 0) {
        int v = i;
        while (state[v] == 0) {
          state[v] = 1;
          v = a[v];
        }
        if (state[v] == 1) {
          cycle.emplace_back();
          while (state[v] == 1) {
            t[v].root_of = v;
            t[v].cyc_pos = {
              sz(cycle) - 1, sz(cycle.back())};
            cycle.back().push_back(v);
            state[v] = 2;
            v = a[v];
          }
        }
        int curr_root_of = t[v].root_of;
        v = i;
        while (state[v] == 1) {
          t[v].root_of = curr_root_of;
          t[a[v]].childs.push_back(v);
          state[v] = 2;
          v = a[v];
        }
      }
    }
  }
};
