T operator[](int i) {
  return (i < ssize(l) ? l[ssize(l) - i - 1]
                       : r[i - ssize(l)])[0];
}
