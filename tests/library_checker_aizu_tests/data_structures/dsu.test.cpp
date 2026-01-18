#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "../template.hpp"
#include "../../../library/dsu/dsu.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int type, u, v;
    cin >> type >> u >> v;
    if (type == 0) dsu.join(u, v);
    else cout << (dsu.f(u) == dsu.f(v)) << '\n';
  }
  return 0;
}
