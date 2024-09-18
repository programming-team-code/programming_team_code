#pragma once
#include "../../../kactl/content/numerical/NumberTheoreticTransform.h"
#include "../n_choose_k/n_choose_k.hpp"
//! https://noshi91.hatenablog.com/entry/2023/07/21/235339
//! @code
//!   auto [right, top] = get_right_and_top(left, bottom);
//! @endcode
//! @param left,bottom see image
//! @returns [right, top] -> see image, note right.back() ==
//! top.back()
//! @time O((n + m)log(n + m))
//! @space O(n + m)
array<vl, 2> get_right_and_top(vl left, vl bottom) {
  array<vl, 2> ret;
  for (vl& res : ret) {
    {
      vl tr(sz(left));
      rep(i, 0, sz(tr)) tr[i] = C(i + sz(bottom) - 1, i);
      res = conv(left, tr);
      res.resize(sz(left));
    }
    {
      vl tr(sz(left) + sz(bottom));
      grow(sz(tr));
      rep(i, 0, sz(tr)) tr[i] = t[i].fact;
      vl dp(sz(bottom));
      rep(i, 0, sz(dp)) dp[i] =
        bottom[i] * t[sz(dp) - 1 - i].inv_fact % mod;
      vl tmp_res = conv(dp, tr);
      rep(i, 0, sz(res)) res[i] =
        (res[i] +
          tmp_res[i + sz(bottom) - 1] * t[i].inv_fact) %
        mod;
    }
    swap(left, bottom);
  }
  return ret;
}
