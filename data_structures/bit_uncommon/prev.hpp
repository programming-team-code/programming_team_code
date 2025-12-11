//! Requires s[i] >= 0
//! max j such that j<=i && query(j,j)>0, or -1
int prev(int i) { return walk(query(i)); }
