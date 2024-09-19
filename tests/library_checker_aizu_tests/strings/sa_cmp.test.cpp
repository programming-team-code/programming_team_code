#define PROBLEM                                        \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/" \
  "ITP2/"                                              \
  "all/ITP2_3_D"
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> arr;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    arr.push_back(val);
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int val;
    cin >> val;
    arr.push_back(val);
  }
  sa_query lq(arr, 1001);
  cout << (lq.cmp_substrs(0, n, n, n + m) < 0) << '\n';
  return 0;
}
