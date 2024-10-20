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
      assert(n / l == n / r);
      assert(l == 1 || n / l < n / (l - 1));
      assert(n / (r + 1) < n / r);
      assert(prev_ri + 1 == l);
      prev_ri = r;
      quots.push_back(n / l);
    }
    assert(prev_ri == n);
  }
  cout << sz(quots) << '\n';
  for (int i = sz(quots) - 1; i >= 0; i--)
    cout << quots[i] << ' ';
  cout << '\n';
  return 0;
}
