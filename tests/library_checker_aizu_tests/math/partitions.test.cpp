#define PROBLEM \
  "https://judge.yosupo.jp/problem/partition_function"
#include "../template.hpp"
#include "../../../library/math/partitions.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  for (auto val : partitions(n + 1)) cout << val << " ";
  cout << '\n';
  return 0;
}
