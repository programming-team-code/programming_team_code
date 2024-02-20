/** @file */
#pragma once
/**
 * @code{.cpp}
       enumerate_triangles(edges, n, [&](int u, int v, int w) {
           //u, v, w form a triangle
       });
 * @endcode
 * @param edges simple undirected graph
 * @param n number of nodes
 * @param f a function run on all length-3-cycles exactly once
 * @time O(n + m ^ (3/2))
 * @space besides the O(m) `edges` param, this function allocates a O(n + m) vector temporarily
 */
template <class F> void enumerate_triangles(const vector<array<int, 2>>& edges, int n, F f) {
	vector<int> deg(n);
	for (auto [u, v] : edges) deg[u]++, deg[v]++;
	vector<vector<int>> adj(n);
	for (auto [u, v] : edges) {
		if (tie(deg[u], u) > tie(deg[v], v)) swap(u, v);
		adj[u].push_back(v);
	}
	vector<bool> seen(n);
	for (auto [u, v] : edges) {
		for (int w : adj[u]) seen[w] = 1;
		for (int w : adj[v]) if (seen[w]) f(u, v, w);
		for (int w : adj[u]) seen[w] = 0;
	}
}
