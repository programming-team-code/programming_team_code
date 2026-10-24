//! https://cp-algorithms.com/string/aho_corasick.html#construction-of-the-trie
const int mn = 'A';
struct trie {
  struct node {
    array<int, 26> nxt;
    bool end_of_word = 0;
    node() { ranges::fill(nxt, -1); }
  };
  deque<node> t;
  trie(): t(1) {}
  void insert(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].nxt[u] == -1) {
        t[v].nxt[u] = ssize(t);
        t.emplace_back();
      }
      v = t[v].nxt[u];
    }
    t[v].end_of_word = 1;
  }
  int find(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].nxt[u] == -1) return 0;
      v = t[v].nxt[u];
    }
    return t[v].end_of_word;
  }
};
