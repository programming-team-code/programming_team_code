#define PROBLEM \
  "https://judge.yosupo.jp/problem/persistent_queue"
#include "../template.hpp"
#include "../../../library/data_structures/seg_tree_uncommon/persistent.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  PST pst(0, q);
  vector<pair<int, int>> bounds(q + 1);
  // bounds[version] = [left index, right index) represents
  // subarray range of queue
  for (int curr_version = 1; curr_version <= q;
    curr_version++) {
    int type;
    cin >> type;
    if (type == 0) {
      int version, x;
      cin >> version >> x;
      version++;
      pst.update(bounds[version].second, x, version);
      bounds[curr_version] = bounds[version];
      bounds[curr_version].second++;
    } else {
      assert(type == 1);
      int version;
      cin >> version;
      version++;
      int idx = bounds[version].first;
      int val_removed =
        int(pst.query(idx, idx + 1, version));
      cout << val_removed << '\n';
      pst.update(idx, -val_removed, version);
      bounds[curr_version] = bounds[version];
      bounds[curr_version].first++;
    }
  }
  return 0;
}
