#pragma once
//! https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
//! @code
//!   // 0 <= a[i] < n
//!   auto [t2, cycle] = func_graph(a);
//!   auto [cyc_id, cyc_pos] = t2[v].root_of;
//!   int root = cycle[cyc_id][cyc_pos];
//!   bool is_on_cycle = (v == root);
//! @endcode
//! root = first reachable node on cycle from v
//! t[v].childs = forest of reversed edges not in cycles
//! @time O(n)
//! @space O(n)
struct func_graph {
  struct node {
    pii root_of;
    vi childs;
  };
  vector<node> t;
  vector<vi> cycle;
  func_graph(const vi& a): t(sz(a)) {
    vi state(sz(a));
    rep(i, 0, sz(a)) {
      if (state[i] == 0) {
        int u = i;
        while (state[u] == 0) {
          state[u] = 1;
          u = a[u];
        }
        if (state[u] == 1) {
          cycle.emplace_back();
          while (state[u] == 1) {
            t[u].root_of = {
              sz(cycle) - 1, sz(cycle.back())};
            cycle.back().push_back(u);
            state[u] = 2;
            u = a[u];
          }
        }
        int v = i;
        while (state[v] == 1) {
          t[v].root_of = t[u].root_of;
          t[a[v]].childs.push_back(v);
          state[v] = 2;
          v = a[v];
        }
      }
    }
  }
};
