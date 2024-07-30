/** @file */
#pragma once
#include "../../../kactl/content/numerical/NumberTheoreticTransform.h"
#include "../n_choose_k/n_choose_k.hpp"

array<vl, 2> get_right_and_top(vl left, vl bottom) {
  assert(!empty(left) && !empty(bottom));
  array<vl, 2> ret;
  for (auto& res : ret) {
    {
      vl tr(sz(left));
      for (int i = 0; i < sz(tr); i++) {
        tr[i] = C(i + sz(bottom) - 1, i);
      }
      res = conv(left, tr);
      res.resize(sz(left));
    }
    {
      vl tr(sz(left) + sz(bottom));
      for (int i = 0; i < sz(tr); i++) {
        tr[i] = t[i].fact;
      }
      auto dp = bottom;
      for (int i = 0; i < sz(dp); i++) {
        dp[i] = dp[i] * t[sz(dp) - 1 - i].inv_fact % mod;
      }
      auto tmp_res = conv(dp, tr);
      for (int i = 0; i < sz(res); i++) {
        res[i] += tmp_res[i + sz(bottom) - 1] * t[i].inv_fact % mod;
        res[i] %= mod;
      }
    }
    swap(left, bottom);
  }
  return ret;
}
