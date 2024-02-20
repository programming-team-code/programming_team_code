#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"

#include "../../../library/strings/prefix_function.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = ssize(s);
	vector<int> pi = prefix_function(s);
	//prefix -> z func conversion
	//source: https://codeforces.com/blog/entry/9612#comment-217621
	vector<int> z(n, 0);
	for (int i = 1; i < n; i++) {
		if (pi[i])
			z[i - pi[i] + 1] = pi[i];
	}
	for (int i = 1; i < n;) {
		int j, v;
		for (j = 1; j < z[i] && (v = min(z[j], z[i] - j)) >= z[i + j]; j++)
			z[i + j] = v;
		i += j;
	}
	z[0] = n;
	for (int i = 0; i < n; i++)
		cout << z[i] << " ";
	cout << '\n';
	return 0;
}
