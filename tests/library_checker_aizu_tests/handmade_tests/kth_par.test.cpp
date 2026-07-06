#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/trees/uncommon/hagerup_kth_par.hpp"
#include "../../../library/trees/uncommon/linear_kth_par.hpp"
int main() {
  for (int n = 1; n <= 100; n++) {
    rep(param, 1, 20) {
      vi par(n);
      vector<vi> adj(n);
      rep(i, 1, n) {
        if (param == 19) par[i] = rnd(0, i - 1);
        else par[i] = rnd(max(0, i - param), i - 1);
        adj[par[i]].push_back(i);
        adj[i].push_back(par[i]);
      }
      hagerup<2> hagerup_kth_par(adj);
      linear_kth_par lin_kth_par(adj);
      rep(i, 0, n) {
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
