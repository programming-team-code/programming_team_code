#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"
#include "../template.hpp"

#include "../../../library/strings/suffix_array/suffix_array.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s, t;
  cin >> s >> t;
  string both = s + '$' + t;
  suffix_array sf_a(both, 256);
  array<int, 2> substr_s = {0, 0}, substr_t = {0, 0};
  for (int i = 0; i < ssize(sf_a.lcp); i++) {
    if (both[sf_a.sa[i]] == '$' || both[sf_a.sa[i + 1]] == '$') continue;
    bool before_in_s = (sf_a.sa[i] < ssize(s));
    bool after_in_s = (sf_a.sa[i + 1] < ssize(s));
    if (before_in_s ^ after_in_s) {
      if (sf_a.lcp[i] > substr_s[1] - substr_s[0]) {
        substr_s = {sf_a.sa[i], sf_a.sa[i] + sf_a.lcp[i]};
        substr_t = {sf_a.sa[i + 1], sf_a.sa[i + 1] + sf_a.lcp[i]};
        if (after_in_s) swap(substr_s, substr_t);
        substr_t[0] -= int(ssize(s)) + 1;
        substr_t[1] -= int(ssize(s)) + 1;
      }
    }
  }
  cout << substr_s[0] << " " << substr_s[1] << " " << substr_t[0] << " " << substr_t[1] << '\n';
  return 0;
}
