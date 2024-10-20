#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
#include "../template.hpp"
#include "compress_char.hpp"
#include "../../../library/strings/suffix_array/burrows_wheeler.hpp"
#define mn mn_other
#define cnt_let cnt_let_other
#include "../../../library/strings/suffix_array/lcp_interval_tree/lcp_interval_tree.hpp"
#undef mn
#undef cnt_let
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s, t;
  cin >> s >> t;
  transform(begin(s), end(s), begin(s), compress_char);
  transform(begin(t), end(t), begin(t), compress_char);
  lcp_tree lt(s);
  auto [l, r] = lt.find_str(t);
  vector<int> matches(begin(lt.sf_a.sa) + l,
    begin(lt.sf_a.sa) + r);
  sort(begin(matches), end(matches));
  {
    // test find via BWT
    bwt bw(s, lt.sf_a.sa);
    auto [bwt_le, bwt_ri] = bw.find_str(t);
    assert(r - l == bwt_ri[0] - bwt_le[0]);
    if (l < r) assert(bwt_le[0] == l);
  }
  for (auto match : matches) cout << match << '\n';
  return 0;
}
