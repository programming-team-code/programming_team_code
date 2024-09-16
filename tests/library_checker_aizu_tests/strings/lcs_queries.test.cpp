#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "prefix_substring_lcs"
#include "../template.hpp"

#include "../../../library/strings/longest_common_subsequence/lcs_queries.hpp"
#include "../../../library/data_structures/wavelet_merge/wavelet_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  string s, t;
  cin >> q >> s >> t;
  vector<array<int, 3>> queries(q);
  for (int i = 0; i < q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    queries[i] = {a, b, c};
  }
  vector<int> res = lcs_queries(s, t, queries);
  for (int val : res) cout << val << '\n';
  return 0;
}
