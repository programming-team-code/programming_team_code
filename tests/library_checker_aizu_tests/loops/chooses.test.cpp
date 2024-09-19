#define PROBLEM                                        \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/" \
  "ITP2/"                                              \
  "all/ITP2_11_D"
#include "../template.hpp"
#include "../../../library/loops/next_subset.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, k;
  cin >> n >> k;
#include "../../../library/loops/chooses.hpp"
  {
    cout << mask << ':';
    for (int bit = 0; bit < n; bit++)
      if ((mask >> bit) & 1) cout << ' ' << bit;
    cout << '\n';
  }
  return 0;
}
