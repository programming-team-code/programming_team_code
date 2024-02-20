#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "compress_char.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	transform(begin(s), end(s), begin(s), compress_char);
	lcp_tree lt(s);
	{
		auto [le, ri] = find_str(s, lt, string(""));
		assert(le == 0 && ri == ssize(s));
	}
	int q;
	cin >> q;
	while (q--) {
		string t;
		cin >> t;
		transform(begin(t), end(t), begin(t), compress_char);
		auto [le, ri] = find_str(s, lt, t);
		cout << (!!(ri - le > 0)) << '\n';
	}
	return 0;
}
