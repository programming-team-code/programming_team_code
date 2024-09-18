#pragma once
//! @param convex,arbitrary arrays where convex satisfies
//! convex[i + 1] - convex[i] <= convex[i + 2] - convex[i +
//! 1] for all i [0, n - 2)
//! @returns array `res` where `res[k]` = the min of (a[i] +
//! b[j]) for all pairs (i,j) where i + j == k
//! @time O((n + m) log (n + m))
//! @space a size O(n + m) vector is allocated and returned
vi min_plus_convolution_convex_and_arbitrary(
  const vi& convex, const vi& arbitrary) {
  int n = sz(convex);
  int m = sz(arbitrary);
  vi res(n + m - 1, INT_MAX);
  auto dnc = [&](auto&& self, int res_le, int res_ri,
               int arb_le, int arb_ri) -> void {
    if (res_le >= res_ri) return;
    int mid_res = (res_le + res_ri) / 2;
    int op_arb = arb_le;
    rep(i, arb_le, min(mid_res + 1, arb_ri)) {
      int j = mid_res - i;
      if (j >= n) continue;
      if (res[mid_res] > convex[j] + arbitrary[i]) {
        res[mid_res] = convex[j] + arbitrary[i];
        op_arb = i;
      }
    }
    self(self, res_le, mid_res, arb_le,
      min(arb_ri, op_arb + 1));
    self(self, mid_res + 1, res_ri, op_arb, arb_ri);
  };
  dnc(dnc, 0, n + m - 1, 0, m);
  return res;
}
