#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
// since find_str_fast uses lower_bound in a weird way
// which makes the partition check fail
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/strings/suffix_array/suffix_array_query.hpp"
#include "../../../library/strings/knuth_morris_pratt.hpp"
#include "../../../library/strings/manacher/longest_from_index.hpp"
#include "../../../library/strings/manacher/count_palindromes_query.hpp"
#include "../../../library/strings/manacher/longest_palindrome_query.hpp"
#include "../../../library/strings/longest_common_subsequence/lcs_queries.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  // mainly to test all strings algs compile when passing
  // in vectors I had a bug where `compare` is only for
  // strings, making `find_str` useless when using vectors
  const int shift = 100'000;
  vector<int> arr(100);
  for (int i = 0; i < 100; i++) arr[i] = shift + i;
  sa_query sf_a(arr, shift + 100);
  {
    for (int i = 1; i < 100; i++)
      assert(sf_a.cmp_sufs(i - 1, i) < 0);
    for (int i = 0; i < 99; i++) {
      assert(sf_a.cmp_sufs(99, i) > 0);
      assert(sf_a.cmp_sufs(i, 99) < 0);
      assert(sf_a.cmp_sufs(i, i) == 0);
    }
    assert(sf_a.cmp_sufs(99, 99) == 0);
  }
  vector<int> t(10);
  for (int i = 50; i < 60; i++) t[i - 50] = shift + i;
  {
    auto [sa_le, sa_ri] = sf_a.find_str(t);
    assert(sa_le == 50 && sa_ri == 51);
  }
  {
    auto [sa_le, sa_ri, s_l, s_r] = sf_a.find_str_fast(t);
    assert(sa_le == 50 && sa_ri == 51);
    assert(s_l == 50 && s_r == 60);
  }
  for (int val : sf_a.lcp) assert(val == 0);
  {
    assert(sf_a.len_lcp(0, 99) == 0);
    for (int i = 0; i < 100; i++) {
      auto [sa_le, sa_ri, s_l, s_r] =
        sf_a.find_substrs_concated({{i, i + 1}});
      pair<int, int> short_res =
        sf_a.find_substr(i, i + 1);
      assert(sa_le == short_res.first &&
        sa_ri == short_res.second);
      assert(sa_le == i && sa_ri == i + 1);
      assert(s_l == i && s_r == i + 1);
    }
    for (int i = 0; i < 100; i++) {
      auto [sa_le, sa_ri, s_l, s_r] =
        sf_a.find_substrs_concated({{i, i}, {i, i}});
      pair<int, int> short_res = sf_a.find_substr(i, i);
      assert(sa_le == short_res.first &&
        sa_ri == short_res.second);
    }
    auto [sa_le, sa_ri, s_l, s_r] =
      sf_a.find_substrs_concated({});
    assert(sa_le == 0 && sa_ri == sz(arr));
    assert(s_l == s_r);
    assert(sf_a.cmp_substrs(0, 0, 99, 99) == 0);
    assert(sf_a.cmp_substrs(5, 5, 47, 47) == 0);
    assert(sf_a.cmp_substrs(50, 50, 99, 100) < 0);
    assert(sf_a.cmp_substrs(50, 51, 20, 20) > 0);
    assert(sf_a.cmp_substrs(0, 100, 0, 100) == 0);
    assert(sf_a.cmp_substrs(1, 100, 0, 100) > 0);
    assert(sf_a.cmp_substrs(0, 100, 1, 100) < 0);
  }
  {
    KMP kmp(t);
    vector<bool> is_m = kmp.find_str(arr);
    assert(is_m[50]);
    rep(i, 0, sz(is_m)) {
      if (i == 50) continue;
      assert(!is_m[i]);
    }
  }
  {
    pal_query pq(arr);
    vector<int> man(manacher(arr)),
      longest(longest_from_index(pq));
    for (int i = 0; i < sz(man); i++) {
      int sz = i - 2 * man[i] + 1;
      assert(sz == (1 ^ (i & 1)));
    }
    for (int i = 0; i < 100; i++) {
      assert(longest[i] == i);
      assert(pq.is_pal(i, i));
      if (i + 2 <= 100) {
        assert(!pq.is_pal(i, i + 1));
        if (i) assert(!pq.is_pal(i - 1, i + 1));
      }
    }
    count_pal_query cpq(arr);
    longest_pal_query lpq(arr);
    for (int l = 0; l < 100; l++) {
      for (int r = l + 1; r <= 100; r++) {
        assert(cpq.count_pals(l, r) == r - l);
        auto [idx, len] = lpq.longest_pal(l, r);
        assert(l <= idx && idx < r);
        assert(len == 1);
      }
    }
  }
  {
    vector<array<int, 3>> queries;
    queries.push_back({100, 0, 100});
    vector<int> res = lcs_queries(arr, arr, queries);
    assert(res[0] == 100);
  }
  cout << "Hello World\n";
  return 0;
}
