#define PROBLEM \
  "https://judge.yosupo.jp/problem/longest_common_substring"
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s, t;
  cin >> s >> t;
  string both = s + '$' + t;
  auto [sa, sa_inv, lcp] = get_sa(both, 256);
  pair<int, int> substr_s = {0, 0}, substr_t = {0, 0};
  for (int i = 0; i < sz(lcp); i++) {
    if (both[sa[i]] == '$' || both[sa[i + 1]] == '$')
      continue;
    bool before_in_s = (sa[i] < sz(s));
    bool after_in_s = (sa[i + 1] < sz(s));
    if (before_in_s ^ after_in_s) {
      if (lcp[i] > substr_s.second - substr_s.first) {
        substr_s = {sa[i], sa[i] + lcp[i]};
        substr_t = {sa[i + 1], sa[i + 1] + lcp[i]};
        if (after_in_s) swap(substr_s, substr_t);
        substr_t.first -= int(sz(s)) + 1;
        substr_t.second -= int(sz(s)) + 1;
      }
    }
  }
  cout << substr_s.first << " " << substr_s.second << " "
       << substr_t.first << " " << substr_t.second << '\n';
  return 0;
}
