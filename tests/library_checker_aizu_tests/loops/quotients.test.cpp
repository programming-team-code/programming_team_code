#define PROBLEM \
  "https://judge.yosupo.jp/problem/enumerate_quotients"
#include "../template.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int64_t n;
  cin >> n;
  vector<int64_t> quots;
  {
    int64_t prev_ri = 0;
#include "../../../library/loops/quotients.hpp"
    {
      assert(n / le == n / ri);
      assert(le == 1 || n / le < n / (le - 1));
      assert(n / (ri + 1) < n / ri);
      assert(prev_ri + 1 == le);
      prev_ri = ri;
      quots.push_back(n / le);
    }
    assert(prev_ri == n);
  }
  cout << sz(quots) << '\n';
  for (int i = sz(quots) - 1; i >= 0; i--)
    cout << quots[i] << ' ';
  cout << '\n';
  return 0;
}
