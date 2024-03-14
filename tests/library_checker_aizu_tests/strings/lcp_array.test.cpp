#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../template.hpp"

#include "../../../library/strings/suffix_array/suffix_array.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  {
    // to test commented example
    string s = "banana";
    suffix_array sf_a(s, 256);
    assert(sf_a.sa == vector<int>({5, 3, 1, 0, 4, 2}));
    assert(sf_a.sa_inv == vector<int>({3, 2, 5, 1, 4, 0}));
    assert(sf_a.lcp == vector<int>({1, 3, 0, 0, 2}));
  }
  string s;
  cin >> s;
  int n = ssize(s);
  suffix_array sf_a(s, 256);
  assert(ssize(sf_a.lcp) == n - 1);
  cout << 1LL * n * (n + 1) / 2 - accumulate(begin(sf_a.lcp), end(sf_a.lcp), 0LL) << '\n';
}
