BIT(const vector<int64_t>& a): s(a) {
  for (int i = 0; i < ssize(a); i++) {
    int j = i | (i + 1);
    if (j < ssize(a)) s[j] += s[i];
  }
}
