#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  dsu uf(n);
  while (q--) {
    int type, u, v;
    cin >> type >> u >> v;
    if (type == 0) uf.join(u, v);
    else cout << (uf.go(u) == uf.go(v)) << '\n';
  }
  return 0;
}
