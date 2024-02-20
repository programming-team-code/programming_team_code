#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
#include "../template.hpp"
#include "compress_char.hpp"

#include "../../../library/strings/suffix_array_related/find/find_string_bwt.hpp"
#define mn mn_other
#define max_val max_val_other
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t;
	cin >> s >> t;
	transform(begin(s), end(s), begin(s), compress_char);
	transform(begin(t), end(t), begin(t), compress_char);
	lcp_tree lt(s);
	auto [le, ri] = find_str(s, lt, t);
	vector<int> matches(begin(lt.sa) + le, begin(lt.sa) + ri);
	sort(begin(matches), end(matches));
	{
		//test find via BWT
		find_bwt fb(s, lt.sa);
		auto [bwt_le, bwt_ri] = fb.find_str(t);
		assert(ri - le == bwt_ri[0] - bwt_le[0]);
		if (le < ri) assert(bwt_le[0] == le);
	}
	for (auto match : matches)
		cout << match << '\n';
	return 0;
}
