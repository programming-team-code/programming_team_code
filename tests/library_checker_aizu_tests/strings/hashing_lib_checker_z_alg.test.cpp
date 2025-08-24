#define PROBLEM \
  "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/strings/string_hash.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = sz(s);
  str_hash hash(s);
  {
    vi a(begin(s), end(s));
    str_hash hash_vec(a);
    assert(hash.substr(0, n) == hash_vec.substr(0, n));
  }
  for (int i = 0; i < n; i++) {
    int start = i, end = n + 1;
    while (start + 1 < end) {
      int mid = (start + end) / 2;
      int len = mid - i;
      if (hash.substr(i, mid) == hash.substr(0, len))
        start = mid;
      else end = mid;
    }
    cout << start - i << ' ';
  }
  cout << '\n';
  return 0;
}
