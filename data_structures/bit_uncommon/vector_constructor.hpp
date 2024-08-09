/**
 * @param a initial array
 * @time O(n)
 * @space O(n) for `s` vector
 */
BIT(const vector<T>& a) : s(a) {
  for (int i = 0; i < ((int)size(a)); i++) {
    int j = i | (i + 1);
    if (j < (int)size(a)) s[j] += s[i];
  }
}
