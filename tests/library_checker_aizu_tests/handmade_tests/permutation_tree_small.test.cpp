#define PROBLEM                             \
  "https://judge.u-aizu.ac.jp/onlinejudge/" \
  "description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../perm_tree_asserts.hpp"

#include "../../../library/data_structures/uncommon/permutation_tree.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 1; n <= 8; n++) {
    vector<int> a(n);
    iota(begin(a), end(a), 0);
    do {
      perm_tree pt = perm_tree_asserts(a);
    } while (next_permutation(begin(a), end(a)));
  }
  cout << "Hello World\n";
  return 0;
}
