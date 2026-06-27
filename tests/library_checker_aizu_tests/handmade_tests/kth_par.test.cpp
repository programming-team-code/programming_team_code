#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/uncommon/hagerup_kth_par.hpp"
#include "../../../library/trees/uncommon/linear_kth_par.hpp"
int main() {
  for (int n = 1; n <= 600; n++) {
    for (int param = 1; param < 20; param++) {
      vector<int> par(n);
      vector<vector<int>> adj(n);
      for (int i = 1; i < n; i++) {
        if (param == 19) par[i] = rnd(0, i - 1);
        else par[i] = rnd(max(0, i - param), i - 1);
        adj[par[i]].push_back(i);
        adj[i].push_back(par[i]);
      }
      hagerup<2> hagerup_kth_par(adj);
      linear_kth_par lin_kth_par(adj);
      for (int i = 0; i < n; i++) {
        for (int k = 0, kth_parent_naive = i;
          k <= hagerup_kth_par.d[i];
          k++, kth_parent_naive = par[kth_parent_naive]) {
          assert(kth_parent_naive ==
                 hagerup_kth_par.kth_par(i, k));
          assert(
            kth_parent_naive == lin_kth_par.kth_par(i, k));
        }
      }
    }
  }
  cout << "Hello World\n";
  return 0;
}
