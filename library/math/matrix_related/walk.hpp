bitset<B> walk(const bitset<B>& k) {
  bitset<B> res;
  for (int i = B, j = npivot; i--;)
    if (basis[i][i] && res[i] ^ k[--j]) res ^= basis[i];
  return res;
}
