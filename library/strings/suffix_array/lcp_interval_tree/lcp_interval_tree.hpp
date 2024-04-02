/** @file */
#pragma once
#include "../../../monotonic_stack/monotonic_range.hpp"
#include "../../../monotonic_stack/cartesian_k_ary_tree.hpp"
#include "../suffix_array.hpp"
const int mn = '0', cnt_let = 36;  // mn <= s[i] < mn + cnt_let; for lowercase letters: mn = 'a', cnt_let = 26
/**
 * @see Replacing suffix trees with enhanced suffix arrays by Mohamed Ibrahim
 * Abouelhoda, Stefan Kurtz, Enno Ohlebusch
 *
 * offline version of suffix tree, idea: min k-ary cartesian tree of LCP array
 * corresponds exactly to the internal nodes of the suffix tree. Then add in <=
 * n nodes, one for each suffix, and it corresponds to the suffix tree.
 *
 * string = "cabcabacaabc"
 *                                              c
 *              c                               b
 *              b               c               a
 *              a               b           c   a
 *      c       a               a           b   c
 *      b       c       c       a           a   a
 *      a       a   c   b       c           a   b
 *      a       b   b   a       a       c   c   a
 *  c   c       a   a   a       b       b   a   c
 *  b   a   c | c   a   c       a       a   b | b
 *  a   b | b | b   c   a   c | c       a | a | a
 *  a | a | a | a | a   b | b | b   c | c | c | c
 *    1   2   3   1   0   1   2   0   1   2   3   <- LCP
 * (------------------------------R--------------)
 * (--------------a--) (--b------) (--c----------)
 * (a) (--b------) (c) (a) (--c--)     (--a------)
 *     (a) (--c--)             (a)     (a) (--b--)
 *             (a)                         (a) (c)
 *
 * note leaf nodes dont exist when that suffix is a prefix of a longer suffix
 *
 * @code{.cpp}
       string s;
       lcp_tree lt(s);
 * @endcode
 *
 * internal nodes are a subset of [0, n - 1), each internal node represents:
 *     - a prefix of some suffix; in the suffix tree, each edge has some substring. This prefix of suffix corresponds to this substring
 *     - a range in the suffix array
 *     - a lcp value of this range of suffixes representing length of prefix of these suffixes
 * leaf nodes are a subset of [n - 1, 2 * n - 1), each leaf represents:
 *     - a single suffix
 */
struct lcp_tree {
  suffix_array<string> sf_a;
  vi le, ri;
  int root;
  vector<vi> adj;
  /**
   * @param s non-empty string/array
   * @time O((n log n) + (mn + cnt_let) + (n * cnt_let))
   * @space adj is O(n * cnt_let)
   */
  lcp_tree(const string& s) : sf_a(s, mn + cnt_let), le(mono_st(sf_a.lcp, less())), ri(mono_range(le)), adj(max(sf_a.n - 1, 0), vector(cnt_let, -1)) {
    assert(sf_a.n > 0);
    auto p = cart_k_ary_tree(sf_a.lcp, le);
    root = find(all(p), -1) - begin(p);
    auto node = [&](int i) -> int {
      return p[i] < i || sf_a.lcp[i] != sf_a.lcp[p[i]] ? i : p[i];
    };
    rep(i, 0, sz(p)) if (node(i) == i && i != root) adj[p[i]][s[sf_a.sa[i] + sf_a.lcp[p[i]]] - mn] = i;
    rep(i, 0, sf_a.n) {
      int prev_lcp = (i ? sf_a.lcp[i - 1] : 0);
      int next_lcp = (i < sz(sf_a.lcp) ? sf_a.lcp[i] : -1);
      int u = (prev_lcp > next_lcp) ? i - 1 : node(i);
      int idx = sf_a.sa[i] + max(prev_lcp, next_lcp);
      if (u == -1 || idx == sf_a.n) continue;
      adj[u][s[idx] - mn] = sf_a.n - 1 + i;
    }
  }
#include "sa_range.hpp"
#include "len_lcp_range.hpp"
#include "get_child.hpp"
#include "find_string.hpp"
};
