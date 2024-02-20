#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"
#include "compress_char.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	transform(begin(s), end(s), begin(s), compress_char);
	int n = ssize(s);
	lcp_tree lt(s);
	{
		auto [le, ri] = find_str(s, lt, string(""));
		assert(le == 0 && ri == n);
		assert(ssize(lt.sa) == n);
		assert(ssize(lt.sa_inv) == n);
		assert(ssize(lt.lcp) == n - 1);
	}
	for (auto val : lt.sa)
		cout << val << " ";
	cout << '\n';
}
