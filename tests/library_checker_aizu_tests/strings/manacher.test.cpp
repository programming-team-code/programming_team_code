#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/manacher/longest_from_index.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = ssize(s);
  vector<int> man(manacher(s)), longest(longest_from_index(man));
  {
    vector<pair<int, int>> tests;
    for (int i = 0; i < n; i++) {
      for (int j = i; j <= min(n, i + int(10'000'000 / max(n, 1))); j++)
        tests.emplace_back(i, j);
    }
    for (int i = 0; i < int(10'000'000 / max(n, 1)); i++) {
      int l = get_rand(0, n - 1), r = get_rand(0, n - 1);
      if (l > r) swap(l, r);
      tests.emplace_back(l, r);
    }
    for (auto [l, r] : tests) {
      string substr = s.substr(l, r - l);
      assert(is_pal(man, l, r) == (substr == string(rbegin(substr), rend(substr))));
    }
  }
  for (int i = 0; i < n; i++) {
    assert(i + longest[i] <= n);
    assert(is_pal(man, i, i + longest[i]));
    if (i + longest[i] < n) {
      assert(!is_pal(man, i, n));
      for (int tests = 10; tests--;) {
        int ri = get_rand(i + longest[i] + 1, n);
        assert(!is_pal(man, i, ri));
      }
    }
  }
  for (int i = 0; i < ssize(man); i++) {
    int ri = i - man[i] + 1;
    assert(man[i] <= ri);
    assert(is_pal(man, man[i], ri));
    assert(man[i] == 0 || ri == n || !is_pal(man, man[i] - 1, ri + 1));
    cout << i - 2 * man[i] + 1 << " ";
  }
  return 0;
}
