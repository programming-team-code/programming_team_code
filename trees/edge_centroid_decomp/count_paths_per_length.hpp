/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
  int n = (int)size(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);  // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < (2 * k); i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vector<int> rev(n);
  for (int i = 0; i < (n); i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < (n); i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < (k); j++) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
        auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];  /// exclude-line
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd& a, const vd& b) {
  if (a.empty() || b.empty()) return {};
  vd res((int)size(a) + (int)size(b) - 1);
  int L = 32 - __builtin_clz((int)size(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(begin(a), end(a), begin(in));
  for (int i = 0; i < ((int)size(b)); i++) in[i].imag(b[i]);
  fft(in);
  for (C& x : in) x *= x;
  for (int i = 0; i < (n); i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < ((int)size(res)); i++) res[i] = imag(out[i]) / (4 * n);
  return res;
}
/**
 * @see https://codeforces.com/blog/entry/104997 https://codeforces.com/blog/entry/120446
 *
 * only handle paths with >=1 edge in each edge-set
 *     (it is guaranteed the edge-sets are non-empty i.e. 0 < split < sz(adj[cent]))
 * don't handle cent<->u paths as these will be handled in some smaller decomposition
 *     (except for single-edge paths, so handle these separately)
 *
 * @code{.cpp}
       edge_cd(adj, [&](const vector<vi>& adj, int cent, int split) {
           // subtrees of prefix [0, split) of adj[cent] are the first edge-set
           // subtrees of suffix [split, sz(adj[cent])) of adj[cent] are the second edge-set
       });
 * @endcode
 */
template <class F> struct edge_cd {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  /**
   * @param a_adj,a_f unrooted tree and callback
   * @time O(n * log1.5(n))
   * @space `adj` and `sub_sz` arrays take O(n); recursion stack for `dfs` is
   * O(log1.5 n); recursion stack for `find_cent` is O(n)
   */
  edge_cd(const vector<vector<int>>& a_adj, F a_f) : adj(a_adj), f(a_f), sub_sz((int)size(adj)) {
    dfs(0, (int)size(adj));
  }
  int find_cent(int u, int p, int siz) {
    sub_sz[u] = 1;
    for (int v : adj[u])
      if (v != p) {
        int cent = find_cent(v, u, siz);
        if (cent != -1) return cent;
        sub_sz[u] += sub_sz[v];
      }
    if (p == -1) return u;
    return 2 * sub_sz[u] >= siz ? sub_sz[p] = siz - sub_sz[u], u : -1;
  }
  void dfs(int u, int siz) {
    if (siz <= 2) return;
    u = find_cent(u, -1, siz);
    int sum = 0;
    auto it = partition(begin(adj[u]), end(adj[u]), [&](int v) {
      bool ret = 2 * sum + sub_sz[v] < siz - 1 && 3 * (sum + sub_sz[v]) <= 2 * (siz - 1);
      if (ret) sum += sub_sz[v];
      return ret;
    });
    f(adj, u, it - begin(adj[u]));
    vector<int> oth(it, end(adj[u]));
    adj[u].erase(it, end(adj[u]));
    dfs(u, sum + 1);
    swap(adj[u], oth);
    dfs(u, siz - sum);
  }
};
/**
 * @param adj unrooted, connected tree
 * @returns array `num_paths` where `num_paths[i]` = # of paths in tree with `i`
 * edges. `num_paths[1]` = # edges
 * @time O(n * log1.5(n) * log2(n))
 * @space this function allocates/returns various vectors which are each O(n)
 */
vector<int64_t> count_paths_per_length(const vector<vector<int>>& adj) {
  vector<int64_t> num_paths((int)size(adj));
  num_paths[1] = (int)size(adj) - 1;
  edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) {
    vector<vector<double>> cnt(2, vector<double>(1));
    auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
      if ((int)size(cnt[side]) == d) cnt[side].push_back(0.0);
      cnt[side][d]++;
      for (int v : cd_adj[u])
        if (v != p) self(self, v, u, 1 + d, side);
    };
    for (int i = 0; i < ((int)size(cd_adj[cent])); i++)
      dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
    vector<double> prod = conv(cnt[0], cnt[1]);
    for (int i = 0; i < ((int)size(prod)); i++)
      num_paths[i] += llround(prod[i]);
  });
  return num_paths;
}
