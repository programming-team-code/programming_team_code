#define PROBLEM                                         \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/7/" \
  "DPL/"                                                \
  "all/DPL_3_C"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "../../../library/monotonic_stack/max_rect_histogram.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  mono_st_asserts(a);
  cout << max_rect_histogram(a) << '\n';
  return 0;
}
