#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/problems/DPL_3_A"
#include "../template.hpp"
#include "../../../library/data_structures_[l,r)/bit_uncommon/kd_bit.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_uncommon/kd_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  KD_BIT<2> bit(n, m);
  KD_SEG<2> tree(n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int c;
      cin >> c;
      if (c) {
	      bit.update(i, j, 1);
	      tree.update(i, j, 1);
      }
    }
  }
  int res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int start = 0, end = min(n - i, m - j) + 1;
      while (start + 1 < end) {
        int mid = (start + end) / 2;
	int sum = bit.query(i, i + mid, j, j + mid);
	assert(sum == tree.query(i, i + mid, j, j + mid));
        if (sum == 0)
          start = mid;
        else end = mid;
      }
      res = max(res, start);
    }
  }
  cout << res * res << '\n';
  return 0;
}
