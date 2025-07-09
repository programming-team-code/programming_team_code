#pragma once
//! https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
//! @code
//!   // 0 <= a[i] < n
//!   auto [root_of, cycle, childs] = func_graph(a);
//!   auto [cyc_id, cyc_pos] = root_of[v];
//!   int root = cycle[cyc_id][cyc_pos];
//!   bool is_on_cycle = (v == root);
//! @endcode
//! root = first reachable node on cycle from v
//! t[v].childs = forest of reversed edges not in cycles
//! @time O(n)
//! @space O(n)
struct func_graph {
  vector<pii> root_of;
  vector<basic_string<int>> cycle, childs;
  func_graph(const vi& a): root_of(sz(a)), childs(sz(a)) {
    vi state(sz(a));
    rep(i, 0, sz(a)) if (!state[i]) {
      int u = i;
      while (!state[u]) {
        state[u] = 1;
        u = a[u];
      }
      if (state[u] == 1) {
        cycle.emplace_back();
        while (state[u] == 1) {
          root_of[u] = {sz(cycle) - 1, sz(cycle.back())};
          cycle.back() += u;
          state[u] = 2;
          u = a[u];
        }
      }
      int v = i;
      while (state[v] == 1) {
        root_of[v] = root_of[u];
        childs[a[v]] += v;
        state[v] = 2;
        v = a[v];
      }
    }
  }
};
