#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array/len_lcp.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  sa_query lq(s, 256);
  // test `*_cmp` functions
  {
    for (int num_tests = 50; num_tests--;) {
      auto le = rnd<int>(0, sz(s));
      auto ri = rnd<int>(0, sz(s));
      if (rnd(0, 30) == 0) le = sz(s);
      if (rnd(0, 30) == 0) ri = sz(s);
      int cmp_val = lq.cmp_sufs(le, ri);
      if (cmp_val < 0) assert(s.substr(le) < s.substr(ri));
      if (cmp_val == 0) assert(s.substr(le) == s.substr(ri));
      if (cmp_val > 0) assert(s.substr(le) > s.substr(ri));
    }
    for (int num_tests = 50; num_tests--;) {
      auto le1 = rnd<int>(0, sz(s));
      auto ri1 = rnd<int>(0, sz(s));
      if (le1 > ri1) swap(le1, ri1);
      int le2, ri2;
      if (rnd(0, 20) == 0) {
        le2 = le1;
        ri2 = ri1;
      } else {
        le2 = rnd<int>(0, sz(s));
        ri2 = rnd<int>(0, sz(s));
        if (le2 > ri2) swap(le2, ri2);
      }
      int cmp_result = lq.cmp_substrs(le1, ri1, le2, ri2);
      string sub1 = s.substr(le1, ri1 - le1);
      string sub2 = s.substr(le2, ri2 - le2);
      if (cmp_result < 0) assert(sub1 < sub2);
      else if (cmp_result == 0) assert(sub1 == sub2);
      else assert(sub1 > sub2);
    }
  }
  for (int i = 0; i < sz(s); i++)
    cout << lq.len_lcp(i, 0) << " ";
  cout << '\n';
  return 0;
}
