#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"
#include "compress_char.hpp"
#include "../../../library/strings/suffix_array_related/find/find_string_bwt.hpp"
#include "../../../library/strings/suffix_array_related/lcp_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		find_bwt fb(string(""), vector<int>());
		auto [le, ri] = fb.find_str(string(""));
		assert(ssize(le) == 1 && ssize(ri) == 1);
		assert(le[0] == 0 && ri[0] == 0);
	}
	string s;
	cin >> s;
	transform(begin(s), end(s), begin(s), compress_char);
	auto [sa, sa_inv] = get_sa(s, 256);
	vector<int> lcp = get_lcp_array(sa, sa_inv, s);
	find_bwt fb(s, sa);
	mono_st_asserts(lcp);
	{
		auto [le, ri] = fb.find_str("");
		assert(ssize(le) == 1 && ssize(ri) == 1);
		assert(le[0] == 0 && ri[0] == ssize(s));
	}
	int q;
	cin >> q;
	while (q--) {
		string t;
		cin >> t;
		transform(begin(t), end(t), begin(t), compress_char);
		auto [le, ri] = fb.find_str(compress_char('a') + t);
		assert(ssize(le) == 2 + ssize(t) && ssize(ri) == 2 + ssize(t) && le.back() == 0 && ri.back() == ssize(s));
		for (int i = ssize(le) - 2; i >= 0; i--)
			assert(ri[i] - le[i] <= ri[i + 1] - le[i + 1]);
		cout << (!!(ri[1] - le[1] > 0)) << '\n';
	}
	return 0;
}
