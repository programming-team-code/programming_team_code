const int mod = 17; //!< must be prime
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = ssize(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod,
      inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}
//! n,k arbitrarily large
//! @time O(log(k)) amortized
//! @space O(1) amortized
int64_t lucas(int64_t n, int64_t k) {
  if (k < 0 || n < k) return 0;
  int64_t res = 1;
  for (; k && k < n && res; n /= mod, k /= mod)
    res = res * C(n % mod, k % mod) % mod;
  return res;
}
