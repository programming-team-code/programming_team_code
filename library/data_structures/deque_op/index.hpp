#pragma once
T operator[](int i) {
  return (i < sz(l) ? l[sz(l) - i - 1] : r[i - sz(l)])[0];
}
