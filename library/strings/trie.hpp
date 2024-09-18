//! @file
#pragma once
//! @see https://cp-algorithms.com/string/aho_corasick.html#construction-of-the-trie
const int mn = 'A',
          cnt_let = 26; // mn <= s[i] < mn + cnt_let
struct trie {
  struct node {
    array<int, cnt_let> next;
    int cnt_words = 0, par = -1;
    char ch;
    node(int a_par = -1, char a_ch = '#'):
      par(a_par), ch(a_ch) {
      fill(all(next), -1);
    }
  };
  vector<node> t;
  trie(): t(1) {}
  void insert(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) {
        t[v].next[u] = sz(t);
        t.emplace_back(v, ch);
      }
      v = t[v].next[u];
    }
    t[v].cnt_words++;
  }
  int find(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) return 0;
      v = t[v].next[u];
    }
    return t[v].cnt_words;
  }
};
