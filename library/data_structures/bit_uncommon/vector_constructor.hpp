#pragma once
BIT(const vector<ll>& a): s(a) {
  rep(i, 0, sz(a)) {
    int j = i | (i + 1);
    if (j < sz(a)) s[j] += s[i];
  }
}
