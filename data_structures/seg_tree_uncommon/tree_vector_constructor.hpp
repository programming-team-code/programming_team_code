tree(const vector<T>& a, T a_unit, F a_f):
  n(ssize(a)), unit(a_unit), f(a_f), s(2 * n) {
  for (int i = 0; i < n; i++) s[i + n] = a[i];
  for (int i = n - 1; i > 0; i--)
    s[i] = f(s[2 * i], s[2 * i + 1]);
}
