/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source:
 http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do
 read, it's excellent) Accuracy bound from
 http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x]
 \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power
 of 2. Useful for convolution: \texttt{conv(a, b) = c},
 where $c[x] = \sum a[i]b[x-i]$. For convolution of complex
 numbers or more than two vectors: FFT, multiply pointwise,
 divide by n, reverse(start+1, end), FFT back. Rounding is
 safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} <
 9\cdot10^{14}$ (in practice $10^{16}$; higher for random
 inputs). Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for
 $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both
 FFT and FFTMod can be found
 * here
 (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
  int n = ssize(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1); // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2 * k; i++)
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if
        // hand-rolled)  /// include-line
        auto x = (double*)&rt[j + k],
             y = (double*)&a[i + j + k]; /// exclude-line
        C z(x[0] * y[0] - x[1] * y[1],
          x[0] * y[1] + x[1] * y[0]); /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd& a, const vd& b) {
  if (a.empty() || b.empty()) return {};
  vd res(ssize(a) + ssize(b) - 1);
  int L = 32 - __builtin_clz(ssize(res)), n = 1 << L;
  vector<C> in(n), out(n);
  copy(begin(a), end(a), begin(in));
  for (int i = 0; i < ssize(b); i++) in[i].imag(b[i]);
  fft(in);
  for (C& x : in) x *= x;
  for (int i = 0; i < n; i++)
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < ssize(res); i++)
    res[i] = imag(out[i]) / (4 * n);
  return res;
}
//! @code
//!   centroid(adj, [&](const vector<vi>& adj,
//!     int cent) {
//!   });
//! @endcode
//! @time O(n log n)
//! @space O(n)
template<class F> struct centroid {
  vector<vector<int>> adj;
  F f;
  vector<int> sub_sz;
  centroid(const vector<vector<int>>& a_adj, F a_f):
    adj(a_adj), f(a_f), sub_sz(ssize(adj), -1) {
    for (int i = 0; i < ssize(adj); i++)
      if (sub_sz[i] == -1) dfs(i);
  }
  void calc_sz(int v, int p) {
    sub_sz[v] = 1;
    for (int u : adj[v])
      if (u != p) calc_sz(u, v), sub_sz[v] += sub_sz[u];
  }
  void dfs(int v) {
    calc_sz(v, -1);
    for (int p = -1, sz_root = sub_sz[v];;) {
      auto big_ch =
        find_if(begin(adj[v]), end(adj[v]), [&](int u) {
          return u != p && 2 * sub_sz[u] > sz_root;
        });
      if (big_ch == end(adj[v])) break;
      p = v, v = *big_ch;
    }
    f(adj, v);
    for (int u : adj[v]) {
      iter_swap(find(begin(adj[u]), end(adj[u]), v),
        rbegin(adj[u]));
      adj[u].pop_back();
      dfs(u);
    }
  }
};
//! @param adj unrooted, connected forest
//! @returns array `num_paths` where `num_paths[i]` = # of
//! paths in tree with `i` edges. `num_paths[1]` = # edges
//! @time O(n log^2 n)
//! @space this function allocates/returns various vectors
//! which are each O(n)
vector<int64_t> count_paths_per_length(
  const vector<vector<int>>& adj) {
  vector<int64_t> num_paths(ssize(adj));
  centroid(adj,
    [&](const vector<vector<int>>& cd_adj, int cent) {
      vector<vector<double>> child_depths;
      for (int v : cd_adj[cent]) {
        child_depths.emplace_back(1, 0.0);
        for (queue<pair<int, int>> q({{v, cent}});
             !empty(q);) {
          child_depths.back().push_back(ssize(q));
          queue<pair<int, int>> new_q;
          while (!empty(q)) {
            auto [u, p] = q.front();
            q.pop();
            for (int w : cd_adj[u]) {
              if (w == p) continue;
              new_q.push({w, u});
            }
          }
          swap(q, new_q);
        }
      }
      sort(begin(child_depths), end(child_depths),
        [&](auto& x, auto& y) {
          return ssize(x) < ssize(y);
        });
      vector total_depth(1, 1.0);
      for (auto& cnt_depth : child_depths) {
        auto prod = conv(total_depth, cnt_depth);
        for (int i = 1; i < ssize(prod); i++)
          num_paths[i] += llround(prod[i]);
        total_depth.resize(ssize(cnt_depth));
        for (int i = 1; i < ssize(cnt_depth); i++)
          total_depth[i] += cnt_depth[i];
      }
    });
  return num_paths;
}
