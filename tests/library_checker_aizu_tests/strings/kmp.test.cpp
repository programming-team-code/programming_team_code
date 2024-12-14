#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
#include "../template.hpp"
#include "../../../library/strings/kmp.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string haystack, needle;
  cin >> haystack >> needle;
  KMP kmp(needle);
  vector<bool> is_m = kmp.find_str(haystack);
  for (int i = 0; i < sz(is_m); i++)
    if (is_m[i]) cout << i << '\n';
  return 0;
}
