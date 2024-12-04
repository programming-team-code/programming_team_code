#pragma once
//! https://github.com/yosupo06/Algorithm/blob/master/src/string/suffixarray.hpp
//! returns range [l,r) such that:
//!   - for all i in [l,r): t==s.substr(sa[i],sz(t))
//!   - `r-l` is the # of matches of t in s.
//! @time O(|t| * log(|s|))
//! @space O(1)
pii find_str(const T& t) {
  auto [l, r] = ranges::equal_range(sa, 0, {}, [&](int i) {
    return bit_cast<char>(
      lexicographical_compare_three_way(begin(s) + i,
        begin(s) + min(i + sz(t), sz(s)), all(t)));
  });
  return {l - begin(sa), r - begin(sa)};
}
