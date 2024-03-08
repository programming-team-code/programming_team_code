#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"
#include "compress_char.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree/lcp_interval_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	transform(begin(s), end(s), begin(s), compress_char);
	int n = ssize(s);
	lcp_tree lt(s);
	{
		auto [le, ri] = lt.find_str(string(""));
		assert(le == 0 && ri == n);
		assert(ssize(lt.sf_a.sa) == n);
		assert(ssize(lt.sf_a.sa_inv) == n);
		assert(ssize(lt.sf_a.lcp) == n - 1);
	}
	for (auto val : lt.sf_a.sa)
		cout << val << " ";
	cout << '\n';
}
