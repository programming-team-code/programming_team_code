#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/implicit.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  struct vertical_edge {
    int x, y1, y2, add;
  };
  vector<vertical_edge> edges;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    edges.push_back({x1, y1, y2, 1});
    edges.push_back({x2, y1, y2, -1});
  }
  sort(begin(edges), end(edges),
    [&](const vertical_edge& a, const vertical_edge& b)
      -> bool { return a.x < b.x; });
  const int mn = 0, mx = 1'000'000'001;
  implicit_seg_tree<500'000 * 31 * 2 * 2 + 100> ist(mn,
    mx);
  int64_t area = 0;
  // sweepline
  for (int i = 0; i < sz(edges);) {
    if (i) {
      auto [curr_mn, cnt_mn] = ist.query(mn, mx);
      int64_t num_pos = mx - mn;
      if (curr_mn == 0) num_pos -= cnt_mn;
      area += (edges[i].x - edges[i - 1].x) * num_pos;
    }
    int j = i;
    while (j < sz(edges) && edges[i].x == edges[j].x) {
      ist.update(edges[j].y1, edges[j].y2, edges[j].add);
      j++;
    }
    i = j;
  }
  cout << area << '\n';
  return 0;
}
