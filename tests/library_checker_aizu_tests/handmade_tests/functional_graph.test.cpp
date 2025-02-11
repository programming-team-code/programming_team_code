#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/graphs/functional_graph_processor.hpp"
// https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Special_Graphs/functional_graph_processor.sublime-snippet
struct functional_graph_processor {
  functional_graph_processor(const vector<int> &next) {
    init(sz(next));
    build(next);
  }
  template <class Graph_t>
  functional_graph_processor(const Graph_t &g) {
    init(g.n);
    build(g);
  }
  void init(int a_n) {
    n = a_n;
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
    for (int i = 0; i < n; i++) {
      cycle_id[i] = -1;
      cycle_pos[i] = -1;
      cycle_prev[i] = -1;
    }
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
          cycle_id[w] = sz(cycle);
          cycle_pos[w] = sz(c);
          c.push_back(w);
          root_of[w] = w;
          depth[w] = 0;
          w = next[w];
        }
        cycle.push_back(c);
      }
      auto dfs = [&](auto self, int u2) -> void {
        if (was2[u2] == attempt) return;
        was2[u2] = attempt;
        int v2 = next[u2];
        self(self, v2);
        root_of[u2] = root_of[v2];
        depth[u2] = depth[v2] + 1;
        abr[v2].push_back(u2);
      };
      dfs(dfs, u);
    }
    for (auto u = 0; u < n; ++u)
      if (~cycle_pos[u]) cycle_prev[next[u]] = u;
    for (const auto &c : cycle) {
      auto dfs = [&](auto self, int u) -> void {
        size[u] = 1;
        pos[u] = sz(order);
        order.push_back(u);
        for (auto v : abr[u]) {
          self(self, v);
          size[u] += size[v];
        }
        end[u] = sz(order);
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
  int n;
  vector<vector<int>> cycle;
  vector<int> cycle_id;        // id of the cycle it belongs to,
                               // -1 if not part of one
  vector<int> cycle_pos;       // position in its cycle, -1 if
                               // not part of one
  vector<int> cycle_prev;      // previous vertex in its cycle,
                               // -1 if not part of one
  vector<int> component_size;  // size of its weakly
                               // connected component
  vector<int> root_of;         // first reachable node in a cycle
  vector<int> depth;           // distance to its root
  vector<vector<int>> abr;     // forest of arborescences of reversed edges not
                               // on the cycles
  vector<int> order;           // dfs order of abr
  vector<int> pos;             // pos in the dfs order
  vector<int> end;             // [pos[u], end[u]) denotes the subtree
  vector<int> size;            // size of the subtree in abr
};

bool equal(const basic_string<int> &a, const vi &b) {
  if (sz(a) != sz(b)) return 0;
  for (int i = 0; i < sz(a); i++)
    if (a[i] != b[i]) return 0;
  return 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int num_tests = 100; num_tests--;) {
    int n = rnd(1, 1000);
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd(0, n - 1);
    auto [t, cycle] = func_graph(a);
    functional_graph_processor fgp(a);
    assert(cycle == fgp.cycle);
    for (int i = 0; i < n; i++) {
      int root = cycle[t[i].root_of.first][t[i].root_of.second];
      assert(root == fgp.root_of[i]);
      assert(equal(t[i].childs, fgp.abr[i]));
      assert((root == i) == (fgp.cycle_id[i] != -1));
      if (root == i) {
        assert(t[i].root_of.first == fgp.cycle_id[i]);
        assert(t[i].root_of.second == fgp.cycle_pos[i]);
        int cyc_len = ssize(cycle[t[i].root_of.first]);
        assert(cycle[t[i].root_of.first][(t[i].root_of.second + 1) % cyc_len] ==
               a[i]);
        assert(fgp.cycle_prev[i] ==
               cycle[t[i].root_of.first]
                    [(t[i].root_of.second - 1 + cyc_len) % cyc_len]);
      } else {
        assert(fgp.cycle_prev[i] == -1);
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
