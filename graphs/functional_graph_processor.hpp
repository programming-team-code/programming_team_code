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
  vector<pair<int, int>> root_of;
  vector<basic_string<int>> cycle, childs;
  func_graph(const vector<int>& a):
    root_of(ssize(a)), childs(ssize(a)) {
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
            root_of[u] = {
              ssize(cycle) - 1, ssize(cycle.back())};
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
  }
};
