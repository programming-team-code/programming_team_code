#define PROBLEM \
  "https://judge.yosupo.jp/problem/prefix_substring_lcs"
#include "../template.hpp"
#include "../../../library/strings/longest_common_subsequence/lcs_dp.hpp"
#include "../../../library/data_structures_[l,r)/seg_tree_uncommon/merge_sort_tree.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  string s, t;
  cin >> q >> s >> t;
  vector<merge_sort_tree> msts;
  {
    lcs_dp lcs(vi(all(t)));
    msts.emplace_back(lcs.dp);
    for (char c : s) {
      lcs.push_onto_s(c);
      {
        vector<bool> seen(sz(t));
        for (int i = 0; i < sz(t); i++) {
          int val = lcs.dp[i];
          assert(val <= i);
          if (val == -1) continue;
          assert(!seen[val]);
          seen[val] = 1;
        }
      }
      msts.emplace_back(lcs.dp);
    }
  }
  for (int i = 0; i < q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << msts[a].query(b, c, -1, b) << '\n';
  }
  return 0;
}
