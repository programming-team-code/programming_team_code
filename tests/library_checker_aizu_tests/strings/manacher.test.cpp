#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/manacher/longest_from_index.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = sz(s);
  pal_query pq(s);
  vector<int> longest(longest_from_index(pq));
  {
    vector<pair<int, int>> tests;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < min(n, i + 10); j++)
        tests.emplace_back(i, j);
    }
    for (int i = 0; i < 30; i++) {
      int l = rnd(0, n - 1), r = rnd(0, n - 1);
      if (l > r) swap(l, r);
      tests.emplace_back(l, r);
    }
    for (auto [l, r] : tests) {
      string substr = s.substr(l, r - l + 1);
      assert(pq.is_pal(l, r) == (substr == string(rbegin(substr), rend(substr))));
    }
  }
  for (int i = 0; i < n; i++) {
    assert(longest[i] < n);
    assert(pq.is_pal(i, longest[i]));
    if (longest[i] + 1 < n) {
      assert(!pq.is_pal(i, n - 1));
      for (int tests = 10; tests--;) {
        int ri = rnd(longest[i] + 1, n - 1);
        assert(!pq.is_pal(i, ri));
      }
    }
  }
  for (int i = 0; i < sz(pq.man); i++) {
    int ri = i - pq.man[i];
    assert(ri + 1 == pq.man[i] || pq.is_pal(pq.man[i], ri));
    assert(pq.man[i] == 0 || ri == n - 1 || !pq.is_pal(pq.man[i] - 1, ri + 1));
    cout << i - 2 * pq.man[i] + 1 << " ";
  }
  return 0;
}
