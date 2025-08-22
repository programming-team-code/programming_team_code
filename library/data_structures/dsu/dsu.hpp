#pragma once
struct dsu {
  vi e;
  dsu(int n): e(n, -1) {}
  int size(int x) { return -e[go(x)]; }
  int go(int x) { return e[x] < 0 ? x : e[x] = go(e[x]); }
  bool join(int a, int b) {
    if ((a = go(a)) == (b = go(b))) return 0;
    if (e[a] > e[b]) swap(a, b);
    return e[a] += e[b], e[b] = a;
  }
};
