#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_5_A"
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<int> arr(2 * n);
  for (int& x : arr) cin >> x;
  vector<int> compress(arr);
  sort(begin(compress), end(compress));
  compress.erase(unique(begin(compress), end(compress)),
    end(compress));
  for (int& x : arr) {
    int l = -1, r = int(sz(compress));
    while (r - l > 1) {
      int mi = l + (r - l) / 2;
      if (compress[mi] >= x) r = mi;
      else l = mi;
    }
    assert(0 <= r && r < sz(compress) && compress[r] == x);
    x = r;
  }
  auto [sa, sa_inv, lcp] = get_sa(arr, int(sz(compress)));
  sa_query lq(arr, sa, sa_inv, lcp);
  vector<int> idxs(n);
  iota(begin(idxs), end(idxs), 0);
  sort(begin(idxs), end(idxs), [&](int i, int j) -> bool {
    return lq.cmp_substrs(2 * i, 2 * (i + 1), 2 * j,
             2 * (j + 1)) < 0;
  });
  for (int idx : idxs)
    cout << compress[arr[2 * idx]] << " "
         << compress[arr[2 * idx + 1]] << '\n';
  return 0;
}
