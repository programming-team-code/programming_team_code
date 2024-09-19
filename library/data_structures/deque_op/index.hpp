#pragma once
T operator[](int i) {
  return (
    i < sz(le) ? le[sz(le) - i - 1] : ri[i - sz(le)])[0];
}
