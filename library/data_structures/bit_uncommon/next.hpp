#pragma once
//! Requires bit.s[i] >= 0
//! @returns min pos such that pos>=i && query(pos,pos)>0
int next(int i) { return walk(query(i - 1) + 1); }
