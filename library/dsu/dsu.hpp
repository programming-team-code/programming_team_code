#pragma once
// NOLINTNEXTLINE(readability-identifier-naming)
struct DSU {
  vi p;
  DSU(int n): p(n, -1) {}
  int size(int x) { return -p[f(x)]; }
  int f(int x) { return p[x] < 0 ? x : p[x] = f(p[x]); }
  bool join(int a, int b) {
    if ((a = f(a)) == (b = f(b))) return 0;
    if (p[a] > p[b]) swap(a, b);
    return p[a] += p[b], p[b] = a, 1;
  }
};
