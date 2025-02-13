//! https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
//! @code
//!   // 0 <= a[i] < n
//!   auto [t, cycle] = func_graph(a);
//!   auto [cyc_id, cyc_pos] = t[v].root_of;
//!   int root = cycle[cyc_id][cyc_pos];
//!   bool is_on_cycle = (v == root);
//! @endcode
//! root = first reachable node on cycle from v
//! t[v].childs = forest of reversed edges not in cycles
//! @time O(n)
//! @space O(n)
struct func_graph {
  struct node {
    pair<int, int> root_of;
    basic_string<int> childs;
  };
  vector<node> t;
  vector<vector<int>> cycle;
  func_graph(const vector<int>& a): t(ssize(a)) {
    vector<int> state(ssize(a));
    for (int i = 0; i < ssize(a); i++) {
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
              ssize(cycle) - 1, ssize(cycle.back())};
            cycle.back().push_back(u);
            state[u] = 2;
            u = a[u];
          }
        }
        int v = i;
        while (state[v] == 1) {
          t[v].root_of = t[u].root_of;
          t[a[v]].childs += v;
          state[v] = 2;
          v = a[v];
        }
      }
    }
  }
};
