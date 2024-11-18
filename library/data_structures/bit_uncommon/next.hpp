//! Requires s[i] >= 0
//! @returns min j such that j>=i && query(j,j)>0, or sz(s)
int next(int i) { return walk(query(i - 1) + 1); }
