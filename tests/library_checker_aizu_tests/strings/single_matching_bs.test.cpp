#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
// since this causes an O(n) partition check for each call to `lower_bound`,
// causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array/suffix_array_query.hpp"

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s, t;
  cin >> s >> t;
  sa_query sf_a(s, 256);
  auto [sa_le, sa_ri, s_le, s_ri] = sf_a.find_str_long(t);
  pair<int, int> short_res = sf_a.find_str(t);
  assert(sa_le == short_res.first && sa_ri == short_res.second);
  int str_len = s_ri - s_le;
  assert(s.substr(s_le, str_len) == t.substr(0, str_len));
  assert(str_len <= sz(t));
  assert(str_len == sz(t) || s_ri == sz(s) || t[str_len] != s[s_ri]);
  assert((sa_le < sa_ri) == (str_len == sz(t)));
  vector<int> matches(begin(sf_a.sa) + sa_le, begin(sf_a.sa) + sa_ri);
  sort(begin(matches), end(matches));
  {
    // test find_substrs_concated
    string both = s + '$' + t;
    int t_start = sz(s) + 1;
    suffix_array lq_both(both, 256);
    vector<int> splits = {0, int(sz(t))};
    for (int num_splits = rnd(0, 4); num_splits--;)
      splits.push_back(rnd<int>(0, sz(t)));
    sort(begin(splits), end(splits));
    vector<pair<int, int>> subs;
    for (int i = 1; i < sz(splits); i++)
      subs.emplace_back(splits[i - 1] + t_start, splits[i] + t_start);
    assert(!empty(subs));
    auto [sa_le2, sa_ri2, s_le2, s_ri2] = lq_both.find_substrs_concated(subs);
    pair<int, int> short_res2 = lq_both.find_substr(t_start, sz(both));
    assert(sa_le2 == short_res2.first && sa_ri2 == short_res2.second);
    assert(both.substr(s_le2, s_ri2 - s_le2) == t);
    assert(sa_ri2 - sa_le2 == 1 + sa_ri - sa_le);
    vector<int> matches_other(begin(lq_both.sa) + sa_le2, begin(lq_both.sa) + sa_ri2);
    matches_other.erase(remove_if(begin(matches_other), end(matches_other), [&](int val) { return val >= sz(s) + 1; }), end(matches_other));
    sort(begin(matches_other), end(matches_other));
    assert(matches == matches_other);
  }
  for (auto match : matches)
    cout << match << '\n';
  return 0;
}
