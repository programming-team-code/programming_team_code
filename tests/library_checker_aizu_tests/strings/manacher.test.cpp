#define PROBLEM \
  "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/strings/manacher/longest_from_index.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = sz(s);
  pal_query pq(vi(all(s)));
  vi longest(longest_from_index(pq));
  {
    vector<pii> tests;
    rep(i, 0, n) rep(j, i, min(n, i + 10))
      tests.emplace_back(i, j);
    rep(i, 0, 30) {
      int l = rnd(0, n - 1), r = rnd(0, n - 1);
      if (l > r) swap(l, r);
      tests.emplace_back(l, r);
    }
    for (auto [l, r] : tests) {
      string substr = s.substr(l, r - l + 1);
      assert(
        pq.is_pal(l, r) ==
        (substr == string(rbegin(substr), rend(substr))));
    }
  }
  rep(i, 0, n) {
    assert(longest[i] < n);
    assert(pq.is_pal(i, longest[i]));
    if (longest[i] + 1 < n) {
      assert(!pq.is_pal(i, n - 1));
      for (int tests = 10; tests--;) {
        int r = rnd(longest[i] + 1, n - 1);
        assert(!pq.is_pal(i, r));
      }
    }
  }
  rep(i, 0, sz(pq.man)) {
    int r = i - pq.man[i];
    assert(r + 1 == pq.man[i] || pq.is_pal(pq.man[i], r));
    assert(pq.man[i] == 0 || r == n - 1 ||
           !pq.is_pal(pq.man[i] - 1, r + 1));
    cout << i - 2 * pq.man[i] + 1 << " ";
  }
  return 0;
}
