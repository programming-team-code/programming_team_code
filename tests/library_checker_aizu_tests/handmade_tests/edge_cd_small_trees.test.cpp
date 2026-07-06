#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../kactl/stress-tests/utilities/genTree.h"
#include "../../../library/trees/edge_cd.hpp"
int main() {
  {
    vector<vi> adj;
    edge_cd(adj, [&](int, int) -> void { assert(false); });
  }
  {
    vector<vi> adj(1);
    edge_cd(adj, [&](int, int) -> void { assert(false); });
  }
  for (int n = 2; n <= 7; n++) {
    int num_codes = 1;
    rep(k, 0, n - 2) num_codes *= n;
    // int num_codes = mpow(n, n - 2).x;
    vector<vi> pruf_codes(num_codes, vi(n - 2));
    rep(i, 0, num_codes) {
      int val = i;
      rep(j, 0, n - 2) {
        int digit = val % n;
        val /= n;
        pruf_codes[i][j] = digit + 1;
      }
    }
    for (vi& code : pruf_codes) {
      auto edges = pruferCodeToTree(code);
      assert(sz(edges) == n - 1);
      vector<vi> adj(n);
      for (auto [u, v] : edges) {
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
#include "../edge_cd_asserts.hpp"
      edge_cd(adj, edge_cd_asserts);
    }
  }
  cout << "Hello World\n";
  return 0;
}
