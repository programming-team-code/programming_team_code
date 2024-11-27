#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/graphs/functional_graph_processor.hpp"
template<class T> struct graph {
  using Weight_t = T;
  struct Edge_t {
    int from, to;
    T cost;
    Edge_t &inplace_flip() {
      swap(from, to);
      return *this;
    }
    Edge_t flip() const { return (*this).inplace_flip(); }
  };
  int n;
  vector<Edge_t> edge;
  vector<vector<int>> adj;
  function<bool(int)> ignore;
  graph(int n = 1): n(n), adj(n) { assert(n >= 1); }
  graph(const vector<vector<int>> &adj,
    bool undirected = true): n((int)adj.size()), adj(n) {
    assert(n >= 1);
    if (undirected) {
      for (auto u = 0; u < n; ++u)
        for (auto v : adj[u])
          if (u < v) link(u, v);
    } else
      for (auto u = 0; u < n; ++u)
        for (auto v : adj[u]) orient(u, v);
  }
  graph(const vector<vector<pair<int, T>>> &adj,
    bool undirected = true): n((int)adj.size()), adj(n) {
    assert(n >= 1);
    if (undirected) {
      for (auto u = 0; u < n; ++u)
        for (auto [v, w] : adj[u])
          if (u < v) link(u, v, w);
    } else
      for (auto u = 0; u < n; ++u)
        for (auto [v, w] : adj[u]) orient(u, v, w);
  }
  graph(int n, vector<array<int, 2>> &edge,
    bool undirected = true): n(n), adj(n) {
    assert(n >= 1);
    for (auto [u, v] : edge)
      undirected ? link(u, v) : orient(u, v);
  }
  graph(int n, vector<tuple<int, int, T>> &edge,
    bool undirected = true): n(n), adj(n) {
    assert(n >= 1);
    for (auto [u, v, w] : edge)
      undirected ? link(u, v, w) : orient(u, v, w);
  }
  int add_vertex() {
    adj.emplace_back();
    return n++;
  }
  int operator()(int u, int id) const {
#ifdef LOCAL
    assert(0 <= id && id < (int)edge.size());
    assert(edge[id].from == u || edge[id].to == u);
#endif
    return u ^ edge[id].from ^ edge[id].to;
  }
  int link(int u, int v,
    T w = {}) { // insert an undirected edge
    int id = (int)edge.size();
    adj[u].push_back(id), adj[v].push_back(id),
      edge.push_back({u, v, w});
    return id;
  }
  int orient(int u, int v,
    T w = {}) { // insert a directed edge
    int id = (int)edge.size();
    adj[u].push_back(id), edge.push_back({u, v, w});
    return id;
  }
  vector<int> neighbor(int u, int exclude = -1) const {
    vector<int> res;
    for (auto id : adj[u]) {
      if (id == exclude || ignore && ignore(id)) continue;
      res.push_back(operator()(u, id));
    }
    return res;
  }
  vector<array<int, 2>> weighted_neighbor(int u,
    int exclude = -1) const {
    vector<array<int, 2>> res;
    for (auto id : adj[u]) {
      if (id == exclude || ignore && ignore(id)) continue;
      res.push_back({operator()(u, id), edge[id].cost});
    }
    return res;
  }
  void clear() {
    for (auto [u, v, w] : edge) {
      adj[u].clear();
      adj[v].clear();
    }
    edge.clear();
    ignore = {};
  }
  graph transpose()
    const { // the transpose of the directed graph
    graph res(n);
    for (auto id = 0; id < (int)edge.size(); ++id) {
      if (ignore && ignore(id)) continue;
      res.orient(edge[id].to, edge[id].from,
        edge[id].cost);
    }
    return res;
  }
  int degree(
    int u) const { // the degree (outdegree if directed) of
                   // u (without the ignoration rule)
    return (int)adj[u].size();
  }
  // The adjacency list is sorted for each vertex.
  vector<vector<int>> get_adjacency_list() const {
    vector<vector<int>> res(n);
    for (auto u = 0; u < n; ++u)
      for (auto id : adj[u]) {
        if (ignore && ignore(id)) continue;
        res[(*this)(u, id)].push_back(u);
      }
    return res;
  }
  void set_ignoration_rule(const function<bool(int)> &f) {
    ignore = f;
  }
  void reset_ignoration_rule() { ignore = nullptr; }
  friend ostream &operator<<(ostream &out,
    const graph &g) {
    for (auto id = 0; id < (int)g.edge.size(); ++id) {
      if (g.ignore && g.ignore(id)) continue;
      auto &e = g.edge[id];
      out << "{" << e.from << ", " << e.to << ", "
          << e.cost << "}\n";
    }
    return out;
  }
};
struct functional_graph_processor {
  functional_graph_processor() {}
  functional_graph_processor(const vector<int> &next) {
    init((int)next.size());
    build(next);
  }
  template<class Graph_t>
  functional_graph_processor(const Graph_t &g) {
    init(g.n);
    build(g);
  }
  void init(int n) {
    this->n = n;
    cycle.clear();
    cycle_id.assign(n, -1);
    cycle_pos.assign(n, -1);
    cycle_prev.assign(n, -1);
    component_size.assign(n, -1);
    root_of.assign(n, -1);
    depth.assign(n, -1);
    order.clear();
    pos.assign(n, -1);
    end.assign(n, -1);
    size.assign(n, -1);
    abr.assign(n, {});
    was.assign(n, -2);
    was2.assign(n, -2);
    attempt = -1;
  }
  int attempt;
  vector<int> was, was2;
  void build(const vector<int> &next) {
    cycle.clear();
    fill(cycle_id.begin(), cycle_id.end(), -1);
    fill(cycle_pos.begin(), cycle_pos.end(), -1);
    fill(cycle_prev.begin(), cycle_prev.end(), -1);
    ++attempt;
    for (auto u = 0; u < n; ++u) {
      if (was[u] == attempt) continue;
      int v = u;
      while (was[v] != attempt) {
        was[v] = attempt;
        v = next[v];
      }
      if (was2[v] != attempt) {
        int w = v;
        vector<int> c;
        while (was2[w] != attempt) {
          was2[w] = attempt;
          cycle_id[w] = (int)cycle.size();
          cycle_pos[w] = (int)c.size();
          c.push_back(w);
          root_of[w] = w;
          depth[w] = 0;
          w = next[w];
        }
        cycle.push_back(c);
      }
      auto dfs = [&](auto self, int u) -> void {
        if (was2[u] == attempt) return;
        was2[u] = attempt;
        int v = next[u];
        self(self, v);
        root_of[u] = root_of[v];
        depth[u] = depth[v] + 1;
        abr[v].push_back(u);
      };
      dfs(dfs, u);
    }
    for (auto u = 0; u < n; ++u)
      if (~cycle_pos[u]) cycle_prev[next[u]] = u;
    for (auto c : cycle) {
      auto dfs = [&](auto self, int u) -> void {
        size[u] = 1;
        pos[u] = (int)order.size();
        order.push_back(u);
        for (auto v : abr[u]) {
          self(self, v);
          size[u] += size[v];
        }
        end[u] = (int)order.size();
      };
      int csize = 0;
      for (auto u : c) {
        dfs(dfs, u);
        csize += size[u];
      }
      for (auto u : c)
        for (auto i = pos[u]; i < end[u]; ++i) {
          int v = order[i];
          component_size[v] = csize;
        }
    }
  }
  // Requires graph
  template<class Graph> void build(const Graph &g) {
    int n = g.n;
    assert(n == (int)g.edge.size());
    vector<int> pv(n, -1), state(n), on_cycle(n);
    vector<vector<int>> cycle;
    auto dfs = [&](auto self, int u, int p) -> void {
      state[u] = 1;
      for (auto id : g.adj[u]) {
        if (g.ignore && g.ignore(id)) continue;
        auto &e = g.edge[id];
        int v = g(u, id);
        if (v == p) continue;
        if (state[v] == 1) {
          cycle.emplace_back();
          for (auto w = u; w != v; w = pv[w]) {
            cycle.back().push_back(w);
            on_cycle[w] = true;
          }
          cycle.back().push_back(v);
          on_cycle[v] = true;
        } else if (state[v] == 0) {
          pv[v] = u;
          self(self, v, u);
        }
      }
      state[u] = 2;
    };
    for (auto u = 0; u < n; ++u) {
      if (state[u] != 2) {
        assert(state[u] == 0);
        dfs(dfs, u, -1);
      }
    }
    vector<int> next(n, -1);
    auto dfs2 = [&](auto self, int u, int p) -> void {
      for (auto id : g.adj[u]) {
        if (g.ignore && g.ignore(id)) continue;
        auto &e = g.edge[id];
        int v = g(u, id);
        if (v == p || on_cycle[v]) continue;
        next[v] = u;
        self(self, v, u);
      }
    };
    for (auto &c : cycle) {
      for (auto i = 0; i < (int)c.size(); ++i)
        next[c[i]] = c[(i + 1) % (int)c.size()];
      for (auto u : c) dfs2(dfs2, u, -1);
    }
    build(next);
  }
  friend ostream &operator<<(ostream &out,
    const functional_graph_processor &fgp) {
    out << "\nCycles: {\n";
    for (auto i = 0; i < (int)fgp.cycle.size(); ++i) {
      out << " {";
      for (auto j = 0; j < (int)fgp.cycle[i].size(); ++j) {
        out << fgp.cycle[i][j];
        if (j + 1 < (int)fgp.cycle[i].size()) out << ", ";
      }
      out << "}";
      if (i + 1 < (int)fgp.cycle.size()) out << ",";
      out << "\n";
    }
    out << "}\n";
    out << "Abr: {\n";
    for (auto u = 0; u < (int)fgp.abr.size(); ++u) {
      out << u << ": {";
      for (auto i = 0; i < (int)fgp.abr[u].size(); ++i) {
        out << fgp.abr[u][i];
        if (i + 1 < (int)fgp.abr[u].size()) out << ", ";
      }
      out << "}";
      if (u + 1 < (int)fgp.abr.size()) out << ",";
      out << "\n";
    }
    out << "}\n";
    out << "Order: {";
    for (auto i = 0; i < (int)fgp.order.size(); ++i) {
      out << fgp.order[i];
      if (i + 1 < (int)fgp.order.size()) out << ", ";
    }
    out << "}\n";
    return out;
  }
  int n;
  vector<vector<int>> cycle;
  vector<int> cycle_id; // id of the cycle it belongs to,
                        // -1 if not part of one
  vector<int> cycle_pos; // position in its cycle, -1 if
                         // not part of one
  vector<int> cycle_prev; // previous vertex in its cycle,
                          // -1 if not part of one
  vector<int> component_size; // size of its weakly
                              // connected component
  vector<int> root_of; // first reachable node in a cycle
  vector<int> depth; // distance to its root
  vector<vector<int>>
    abr; // forest of arborescences of reversed edges not
         // on the cycles
  vector<int> order; // dfs order of abr
  vector<int> pos; // pos in the dfs order
  vector<int> end; // [pos[u], end[u]) denotes the subtree
  vector<int> size; // size of the subtree in abr
};
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int num_tests = 1000; num_tests--;) {
    int n = rnd(1, 1000);
    cerr << "n: " << n << endl;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd(0, n - 1);
    auto [t, cycle] = func_graph(a);
    functional_graph_processor fgp(a);
    assert(cycle == fgp.cycle);
    for (int i = 0; i < n; i++) {
      assert(t[i].root_of == fgp.root_of[i]);
      assert(t[i].childs == fgp.abr[i]);
      assert(t[i].cyc_pos.has_value() ==
        (fgp.cycle_id[i] != -1));
      if (auto id = t[i].cyc_pos) {
        int cyc_len = ssize(cycle[id->first]);
        assert(i == cycle[id->first][id->second]);
        assert(
          cycle[id->first][(id->second + 1) % cyc_len] ==
          a[i]);
        assert(fgp.cycle_prev[i] ==
          cycle[id->first]
               [(id->second - 1 + cyc_len) % cyc_len]);
      } else {
        assert(fgp.cycle_prev[i] == -1);
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
