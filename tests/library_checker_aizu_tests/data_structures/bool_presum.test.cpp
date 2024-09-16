#define PROBLEM                      \
  "https://judge.yosupo.jp/problem/" \
  "static_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/bool_presum.hpp"

vector<bool_presum> init_presums(
  const vector<int>& arr) {
  const int mx_n = sz(arr);
  vector<bool_presum> presums;
  for (int bit = 0; bit < 30; bit++) {
    vector<bool> the_bools(mx_n);
    for (int i = 0; i < mx_n; i++)
      the_bools[i] = (arr[i] >> bit) & 1;
    presums.emplace_back(the_bools);
  }
  return presums;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int n = 0; n <= 500; n++) {
    vector<bool> init(n);
    bool_presum bp(init);
    for (int i = 0; i <= n; i++)
      assert(bp.popcount(i) == 0);
  }
  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  vector<bool_presum> presums = init_presums(arr);
  assert(sz(presums) == 30);
  while (q--) {
    int le, ri;
    cin >> le >> ri;
    int64_t sum = 0;
    for (int bit = 0; bit < 30; bit++)
      if (ri - le == 1)
        sum += (1LL << bit) * presums[bit].on(le);
      else
        sum += (1LL << bit) *
               (presums[bit].popcount(ri) -
                 presums[bit].popcount(le));
    cout << sum << '\n';
  }
}
