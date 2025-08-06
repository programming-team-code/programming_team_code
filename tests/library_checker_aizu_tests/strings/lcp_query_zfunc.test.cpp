#define PROBLEM \
  "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  auto [sa, sa_inv, lcp] = get_sa(vi(all(s)), 256);
  sa_query lq(vi(all(s)), sa, sa_inv, lcp);
  // test `*_cmp` functions
  {
    for (int num_tests = 50; num_tests--;) {
      auto l = rnd(0, int(sz(s)) - 1);
      auto r = rnd(0, int(sz(s)) - 1);
      int cmp_val = lq.cmp_sufs(l, r);
      if (cmp_val < 0) assert(s.substr(l) < s.substr(r));
      if (cmp_val == 0) assert(s.substr(l) == s.substr(r));
      if (cmp_val > 0) assert(s.substr(l) > s.substr(r));
    }
    for (int num_tests = 50; num_tests--;) {
      auto l1 = rnd(0, int(sz(s)));
      auto r1 = rnd(0, int(sz(s)));
      if (l1 > r1) swap(l1, r1);
      if (l1 == sz(s)) l1--;
      int l2, r2;
      if (rnd(0, 20) == 0) {
        l2 = l1;
        r2 = r1;
      } else {
        l2 = rnd(0, int(sz(s)));
        r2 = rnd(0, int(sz(s)));
        if (l2 > r2) swap(l2, r2);
        if (l2 == sz(s)) l2--;
      }
      int cmp_result = lq.cmp_substrs(l1, r1, l2, r2);
      string sub1 = s.substr(l1, r1 - l1);
      string sub2 = s.substr(l2, r2 - l2);
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
