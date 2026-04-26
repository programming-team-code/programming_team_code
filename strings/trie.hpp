//! https://cp-algorithms.com/string/aho_corasick.html#construction-of-the-trie
const int mn = 'A';
struct trie {
  struct node {
    array<int, 26> next;
    bool end_of_word = 0;
    node() { ranges::fill(next, -1); }
  };
  deque<node> t;
  trie(): t(1) {}
  void insert(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) {
        t[v].next[u] = ssize(t);
        t.emplace_back();
      }
      v = t[v].next[u];
    }
    t[v].end_of_word = 1;
  }
  int find(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) return 0;
      v = t[v].next[u];
    }
    return t[v].end_of_word;
  }
};
