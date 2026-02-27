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
  vector<vector<int>> cycle, childs;
  func_graph(const vector<int>& a):
    root_of(ssize(a)), childs(ssize(a)) {
    vector<int> vis(ssize(a));
    for (int i = 0; i < ssize(a); i++)
      if (!vis[i]) {
        int u = i;
        for (; !vis[u]; u = a[u]) vis[u] = 1;
        if (vis[u] == 1)
          for (cycle.emplace_back(); vis[u] == 1;
            u = a[u]) {
            root_of[u] = {
              ssize(cycle) - 1, ssize(cycle.back())};
            cycle.back().push_back(u);
            vis[u] = 2;
          }
        for (int v = i; vis[v] == 1; v = a[v]) {
          root_of[v] = root_of[u];
          childs[a[v]].push_back(v);
          vis[v] = 2;
        }
      }
  }
};
