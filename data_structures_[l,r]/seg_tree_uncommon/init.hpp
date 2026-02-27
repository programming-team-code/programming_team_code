tree(const vector<T>& a, F op):
  n(ssize(a)), op(op), s(2 * n) {
  for (int i = 0; i < n; i++) s[i + n] = a[i];
  for (int i = n - 1; i >= 1; i--)
    s[i] = op(s[2 * i], s[2 * i + 1]);
}
