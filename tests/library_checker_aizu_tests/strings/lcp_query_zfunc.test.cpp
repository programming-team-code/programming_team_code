#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/compare/compare_suffixes.hpp"
#include "../../../library/strings/suffix_array_related/compare/compare_substrings.hpp"
#include "../../../library/strings/suffix_array_related/lcp_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	lcp_query lq(s, 256);
	//test `*_cmp` functions
	{
		for (int num_tests = 50; num_tests--;) {
			auto le = get_rand<int>(0, ssize(s));
			auto ri = get_rand<int>(0, ssize(s));
			if (get_rand(0, 30) == 0) le = ssize(s);
			if (get_rand(0, 30) == 0) ri = ssize(s);
			int cmp_val = suf_cmp(lq.sa_inv, le, ri);
			if (cmp_val < 0) assert(s.substr(le) < s.substr(ri));
			if (cmp_val == 0) assert(s.substr(le) == s.substr(ri));
			if (cmp_val > 0) assert(s.substr(le) > s.substr(ri));
		}
		for (int num_tests = 50; num_tests--;) {
			auto le1 = get_rand<int>(0, ssize(s));
			auto ri1 = get_rand<int>(0, ssize(s));
			if (le1 > ri1) swap(le1, ri1);
			int le2, ri2;
			if (get_rand(0, 20) == 0) {
				le2 = le1;
				ri2 = ri1;
			} else {
				le2 = get_rand<int>(0, ssize(s));
				ri2 = get_rand<int>(0, ssize(s));
				if (le2 > ri2) swap(le2, ri2);
			}
			int cmp_result = substr_cmp(lq, le1, ri1, le2, ri2);
			string sub1 = s.substr(le1, ri1 - le1);
			string sub2 = s.substr(le2, ri2 - le2);
			if (cmp_result < 0) assert(sub1 < sub2);
			else if (cmp_result == 0) assert(sub1 == sub2);
			else assert(sub1 > sub2);
		}
	}
	for (int i = 0; i < ssize(s); i++)
		cout << lq.get_lcp(i, 0) << " ";
	cout << '\n';
	return 0;
}
