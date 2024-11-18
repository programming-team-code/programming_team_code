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
    auto [l, r] = bw.find_str(string(""));
    assert(sz(l) == 1 && sz(r) == 1);
    assert(l[0] == 0 && r[0] == 0);
  }
  string s;
  cin >> s;
  transform(begin(s), end(s), begin(s), compress_char);
  auto [sa, sa_inv, lcp] = get_sa(s, 256);
  sa_query sf_a(s, sa, sa_inv, lcp);
  bwt bw(s, sa);
  mono_st_asserts(lcp);
  {
    auto [l, r] = bw.find_str("");
    assert(sz(l) == 1 && sz(r) == 1);
    assert(l[0] == 0 && r[0] == sz(s));
  }
  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    transform(begin(t), end(t), begin(t), compress_char);
    auto [l, r] = bw.find_str(compress_char('a') + t);
    assert(sz(l) == 2 + sz(t) && sz(r) == 2 + sz(t) &&
      l.back() == 0 && r.back() == sz(s));
    for (int i = sz(l) - 2; i >= 0; i--)
      assert(r[i] - l[i] <= r[i + 1] - l[i + 1]);
    cout << (!!(r[1] - l[1] > 0)) << '\n';
  }
  return 0;
}
