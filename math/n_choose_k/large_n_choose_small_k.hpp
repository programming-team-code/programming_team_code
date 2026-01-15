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
//! n arbitrarily large; k < mod
//! @time O(k) amortized
//! @space O(1) amortized
int64_t c_small_k(int64_t n, int k) {
  if (k < 0 || n < k || (n %= mod) < k) return 0;
  grow(k);
  int64_t res = t[k].inv_fact;
  for (int i = 0; i < k; i++) res = res * (n - i) % mod;
  return res;
}
