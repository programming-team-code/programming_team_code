template<int K> struct KD_BIT;
template<> struct KD_BIT<0> {
  ll s = 0;
  void update(ll v) { s += v; }
  ll query() { return s; }
};
template<int K> struct KD_BIT {
  vector<KD_BIT<K - 1>> s;
  template<class... A>
  KD_BIT(int n, A... a): s(n, KD_BIT<K - 1>(a...)) {}
  template<class... A> void update(int i, A... a) {
    for (; i < sz(s); i |= i + 1) s[i].update(a...);
  }
  template<class... A> ll query(int l, int r, A... a) {
    ll ans = 0;
    for (; l < r; r &= r - 1) ans += s[r - 1].query(a...);
    for (; r < l; l &= l - 1) ans -= s[l - 1].query(a...);
    return ans;
  }
};
