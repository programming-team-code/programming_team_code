#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
// since this causes an O(n) partition check for each call to `lower_bound`,
// causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array/suffix_array.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    suffix_array sf_a(string(""), 256);
    auto [sa_le, sa_ri, s_le, s_ri] = sf_a.find_str_long(string(""));
    array<int, 2> short_res = sf_a.find_str(string(""));
    assert(sa_le == short_res[0] && sa_ri == short_res[1]);
    assert(sa_le == 0 && sa_ri == 0 && s_le == 0 && s_ri == 0);
  }
  string s;
  cin >> s;
  suffix_array sf_a(s, 256);
  {
    auto [sa_le, sa_ri, s_le, s_ri] = sf_a.find_str_long(string(""));
    array<int, 2> short_res = sf_a.find_str(string(""));
    assert(sa_le == short_res[0] && sa_ri == short_res[1]);
    assert(sa_le == 0 && sa_ri == ssize(s));
    assert(s_ri - s_le == 0);
  }
  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;
    auto [sa_le, sa_ri, s_le, s_ri] = sf_a.find_str_long(t);
    array<int, 2> short_res = sf_a.find_str(t);
    assert(sa_le == short_res[0] && sa_ri == short_res[1]);
    int str_len = s_ri - s_le;
    assert(str_len <= ssize(t));
    assert(s.substr(s_le, str_len) == t.substr(0, str_len));
    assert(str_len == ssize(t) || s_ri == ssize(s) || t[str_len] != s[s_ri]);
    assert((sa_le < sa_ri) == (str_len == ssize(t)));
    cout << (!!(sa_ri - sa_le > 0)) << '\n';
  }
  return 0;
}
