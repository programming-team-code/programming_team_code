/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x]
 g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of
 the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For
 arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested
 */
/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
const int64_t mod = 1000000007; // faster if const
int64_t modpow(int64_t b, int64_t e) {
  int64_t ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
const int64_t mod = (119 << 23) + 1,
              root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 <<
// 21 and 483 << 21 (same root). The last two are > 10^9.
typedef vector<int64_t> vl;
void ntt(vl &a) {
  int n = ssize(a), L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    int64_t z[] = {1, modpow(root, mod >> s)};
    for (int i = k; i < 2 * k; i++)
      rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        int64_t z = rt[j + k] * a[i + j + k] % mod,
                &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = ssize(a) + ssize(b) - 1,
      B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, mod - 2);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  for (int i = 0; i < n; i++)
    out[-i & (n - 1)] =
      (int64_t)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}
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
//! https://noshi91.hatenablog.com/entry/2023/07/21/235339
//! @code
//!   auto [right, top] = get_right_and_top(left, bottom);
//! @endcode
//! @time O((n + m)log(n + m))
//! @space O(n + m)
array<vl, 2> get_right_and_top(vl left, vl bottom) {
  array<vl, 2> ret;
  for (vl &res : ret) {
    {
      vl tr(ssize(left));
      for (int i = 0; i < ssize(tr); i++)
        tr[i] = C(i + ssize(bottom) - 1, i);
      res = conv(left, tr);
      res.resize(ssize(left));
    }
    {
      vl tr(ssize(left) + ssize(bottom));
      grow(ssize(tr));
      for (int i = 0; i < ssize(tr); i++)
        tr[i] = t[i].fact;
      vl dp(ssize(bottom));
      for (int i = 0; i < ssize(dp); i++)
        dp[i] =
          bottom[i] * t[ssize(dp) - 1 - i].inv_fact % mod;
      vl tmp_res = conv(dp, tr);
      for (int i = 0; i < ssize(res); i++)
        res[i] = (res[i] +
                   tmp_res[i + ssize(bottom) - 1] *
                     t[i].inv_fact) %
          mod;
    }
    swap(left, bottom);
  }
  return ret;
}
