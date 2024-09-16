#define PROBLEM \
  "https://judge.yosupo.jp/problem/rectangle_sum"
// since this causes an O(n) partition check for
// each call to `lower_bound`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/seg_tree_uncommon/persistent.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;
  vector<array<int, 3>> points(n);
  for (int i = 0; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    points[i] = {x, y, w};
  }
  sort(begin(points), end(points));
  PST pst(-5, 1'000'000'000);
  for (const auto& point : points)
    pst.update(
      point[1], point[2], sz(pst.roots) - 1);
  while (q--) {
    int le, down, ri, up;
    cin >> le >> down >> ri >> up;
    le = int(lower_bound(begin(points), end(points),
               array<int, 3>({le, -1, -1})) -
             begin(points));
    ri = int(lower_bound(begin(points), end(points),
               array<int, 3>({ri, -1, -1})) -
             begin(points));
    cout << pst.query(down, up, ri) -
              pst.query(down, up, le)
         << '\n';
  }
  return 0;
}
