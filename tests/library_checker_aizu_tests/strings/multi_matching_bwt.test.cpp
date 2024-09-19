#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "compress_char.hpp"
#include "../../../library/strings/suffix_array/burrows_wheeler.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    bwt bw(string(""), vector<int>());
    auto [le, ri] = bw.find_str(string(""));
    assert(sz(le) == 1 && sz(ri) == 1);
    assert(le[0] == 0 && ri[0] == 0);
  }
  string s;
  cin >> s;
  transform(begin(s), end(s), begin(s), compress_char);
  sa_query sf_a(s, 256);
  bwt bw(s, sf_a.sa);
  mono_st_asserts(sf_a.lcp);
  {
    auto [le, ri] = bw.find_str("");
    assert(sz(le) == 1 && sz(ri) == 1);
    assert(le[0] == 0 && ri[0] == sz(s));
  }
  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    transform(begin(t), end(t), begin(t), compress_char);
    auto [le, ri] = bw.find_str(compress_char('a') + t);
    assert(sz(le) == 2 + sz(t) && sz(ri) == 2 + sz(t) &&
      le.back() == 0 && ri.back() == sz(s));
    for (int i = sz(le) - 2; i >= 0; i--)
      assert(ri[i] - le[i] <= ri[i + 1] - le[i + 1]);
    cout << (!!(ri[1] - le[1] > 0)) << '\n';
  }
  return 0;
}
