const int mod = 17; /**< must be prime */
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  while ((int)size(t) <= n) {
    int64_t i = (int)size(t), inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod, inv * t[i - 1].inv_fact % mod});
  }
}
