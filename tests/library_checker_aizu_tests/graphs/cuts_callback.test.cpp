#define PROBLEM \
  "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"
#include "../../../library/graphs/bridges_cuts/cuts_callback.hpp"
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n,m;
  cin>>n>>m;
  vector<basic_string<int>> adj(n);
  for (int i = 0; i <n; i++) {
    adj[i] += i;
  }
  for (int i = 0; i <m; i++) {
    int u,v;
    cin>>u>>v;
    adj[u] += v;
    adj[v] += u;
  }
  vector<bool> vis(n, 0);
  vector<vector<int>> all_bccs;
  cuts_callback(adj, [&](const vi& nodes_bcc) {
    for(int v : nodes_bcc){
      vis[v] = 1;
    }
    all_bccs.push_back(nodes_bcc);
  });
  for (int i = 0; i <n; i++) {
    if(!vis[i]) {
      all_bccs.push_back({i});
    }
  }
  cout << ssize(all_bccs) << '\n';
  for(const vector<int>& other_nodes : all_bccs) {
    cout<<ssize(other_nodes)<<' ';
    for(int v : other_nodes){
      cout<<v<<' ';
    }
    cout<<'\n';
  }
  return 0;
}
