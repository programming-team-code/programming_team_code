#pragma once
//! @time O(mx log mx)
//! @space O(mx)
vi mobius(100'005);
mobius[1] = 1;
rep(i, 1, sz(mobius)) for (int j = i + i; j < sz(mobius);
  j += i) mobius[j] -= mobius[i];
