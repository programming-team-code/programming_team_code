#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../edge_cd_asserts.hpp"

#include "../../../kactl/stress-tests/utilities/genTree.h"

#include "../../../library/math/binary_exponentiation_mod.hpp"
#include "../../../library/trees/edge_centroid_decomp/edge_cd.hpp"

int main() {
  {
    vector<vector<int>> adj;
    edge_cd(adj, [&](const vector<vector<int>>&, int, int) -> void {
      assert(false);
    });
  }
  {
    vector<vector<int>> adj(1);
    edge_cd(adj, [&](const vector<vector<int>>&, int, int) -> void {
      assert(false);
    });
  }
  for (int n = 2; n <= 8; n++) {
    int num_codes = int(bin_exp(n, n - 2));
    vector<vector<int>> pruf_codes(num_codes, vector<int>(n - 2));
    for (int i = 0; i < num_codes; i++) {
      int val = i;
      for (int j = 0; j < n - 2; j++) {
        int digit = val % n;
        val /= n;
        pruf_codes[i][j] = digit + 1;
      }
    }
    for (vector<int>& code : pruf_codes) {
      auto edges = pruferCodeToTree(code);
      assert(ssize(edges) == n - 1);
      vector<vector<int>> adj(n);
      for (auto [u, v] : edges) {
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
      edge_cd(adj, edge_cd_asserts);
    }
  }
  cout << "Hello World\n";
  return 0;
}
