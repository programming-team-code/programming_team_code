//! Requires bit.s[i] >= 0
//! @returns max pos such that pos<=i && query(pos,pos)>0
int prev(int i) { return walk(query(i)); }
