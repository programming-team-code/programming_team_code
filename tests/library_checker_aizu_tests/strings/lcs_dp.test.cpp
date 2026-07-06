#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C"
#include "../template.hpp"
#include "../../../library/strings/longest_common_subsequence/lcs_dp.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  rep(i, 0, q) {
    string s, t;
    cin >> s >> t;
    array<int, 2> res;
    rep(j, 0, 2) {
      lcs_dp lcs(vi(all(t)));
      for (char c : s) lcs.push_onto_s(c);
      res[j] = int(count(begin(lcs.dp), end(lcs.dp), -1));
      swap(s, t);
    }
    assert(res[0] == res[1]);
    cout << res[0] << '\n';
  }
  return 0;
}
