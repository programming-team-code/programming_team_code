//! helper for edge CD: given tree, update node's number,
//! find sum of neighbors' numbers
struct sum_adj {
  int n;
  vector<int64_t> sum, sum_ch;
  vector<int> p;
  //! @param adj undirected, unrooted tree
  //! @param sum sum[u] = initial number for node u
  //! @time O(n)
  //! @space various O(n) vectors are allocated; recursion
  //! stack for dfs is O(n)
  sum_adj(const vector<vector<int>>& adj,
    const vector<int64_t>& sum):
    n(ssize(sum)), sum(sum), sum_ch(n), p(n, -1) {
    auto dfs = [&](auto&& self, int u) -> void {
      for (int c : adj[u])
        if (c != p[u])
          p[c] = u, sum_ch[u] += sum[c], self(self, c);
    };
    dfs(dfs, 0);
  }
  //! @param u node
  //! @param delta number to add
  //! @time O(1)
  //! @space O(1)
  void update(int u, int64_t delta) {
    sum[u] += delta;
    if (p[u] != -1) sum_ch[p[u]] += delta;
  }
  //! @param u node
  //! @returns sum of u's neighbors numbers
  //! @time O(1)
  //! @space O(1)
  int64_t query(int u) {
    return sum_ch[u] + (p[u] != -1 ? sum[p[u]] : 0);
  }
};
