#define PROBLEM \
  "https://judge.yosupo.jp/problem/rectangle_sum"
// since this causes an O(n) partition check for each call
// to `lower_bound`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_uncommon/persistent.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<array<int, 3>> points(n);
  rep(i, 0, n) {
    int x, y, w;
    cin >> x >> y >> w;
    points[i] = {x, y, w};
  }
  ranges::sort(points);
  PST pst(-5, 1'000'000'000);
  for (const auto& point : points)
    pst.update(point[1], point[2], sz(pst.roots) - 1);
  while (q--) {
    int l, down, r, up;
    cin >> l >> down >> r >> up;
    l = int(ranges::lower_bound(points,
              array<int, 3>({l, -1, -1})) -
            begin(points));
    r = int(ranges::lower_bound(points,
              array<int, 3>({r, -1, -1})) -
            begin(points));
    cout << pst.query(down, up, r) - pst.query(down, up, l)
         << '\n';
  }
  return 0;
}
