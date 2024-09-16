#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/bool_bit.hpp"

const int max_bit = 51;

vector<bool_bit> init_prebools(
  const vector<int64_t>& arr) {
  const int mx_n = sz(arr);
  vector<bool_bit> prebools;
  for (int bit = 0; bit < max_bit; bit++) {
    vector<bool> curr(mx_n);
    for (int i = 0; i < mx_n; i++)
      curr[i] = (arr[i] >> bit) & 1;
    prebools.emplace_back(curr);
  }
  return prebools;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 0; n <= 500; n++) {
    vector<bool> init(n);
    bool_bit bb(init);
    for (int i = 0; i <= n; i++)
      assert(bb.popcount(i) == 0);
  }
  int n, q;
  cin >> n >> q;
  vector<int64_t> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  vector<bool_bit> prebools = init_prebools(arr);
  assert(sz(prebools) == max_bit);
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int i;
      int delta;
      cin >> i >> delta;
      arr[i] += delta;
      for (int bit = 0; bit < max_bit; bit++)
        prebools[bit].set(i, (arr[i] >> bit) & 1);
    } else {
      assert(type == 1);
      int le, ri;
      cin >> le >> ri;
      int64_t sum = 0;
      for (int bit = 0; bit < max_bit; bit++) {
        if (ri - le == 1)
          sum +=
            (1LL << bit) * prebools[bit].on(le);
        else
          sum += (1LL << bit) *
                 prebools[bit].popcount(le, ri);
      }
      cout << sum << '\n';
    }
  }
}
