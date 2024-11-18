#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
// since this causes an O(n) partition check for each call
// to `lower_bound`, causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  auto [sa, sa_inv, lcp] = get_sa(s, 256);
  sa_query sf_a(s, sa, sa_inv, lcp);
  {
    auto [sa_le, sa_ri, s_l, s_r] =
      sf_a.find_str_fast(string(""));
    pair<int, int> short_res = sf_a.find_str(string(""));
    assert(sa_le == short_res.first &&
      sa_ri == short_res.second);
    assert(sa_le == 0 && sa_ri == sz(s));
    assert(s_r - s_l == 0);
  }
  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    auto [sa_le, sa_ri, s_l, s_r] = sf_a.find_str_fast(t);
    pair<int, int> short_res = sf_a.find_str(t);
    assert(sa_le == short_res.first &&
      sa_ri == short_res.second);
    int str_len = s_r - s_l;
    assert(str_len <= sz(t));
    assert(s.substr(s_l, str_len) == t.substr(0, str_len));
    assert(str_len == sz(t) || s_r == sz(s) ||
      t[str_len] != s[s_r]);
    assert((sa_le < sa_ri) == (str_len == sz(t)));
    cout << (!!(sa_ri - sa_le > 0)) << '\n';
  }
  return 0;
}
