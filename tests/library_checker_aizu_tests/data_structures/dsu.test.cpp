#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../template.hpp"
#include "../../../library/data_structures/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int type, u, v;
    cin >> type >> u >> v;
    if (type == 0) dsu.join(u, v);
    else cout << (dsu.go(u) == dsu.go(v)) << '\n';
  }
  return 0;
}
