#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/strings/suffix_array_related/find/find_string_bs.hpp"
#include "../../../library/strings/suffix_array_related/find/find_substrings_concatenated.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		string s;
		auto [sa, sa_inv] = get_sa(s, 256);
		assert(empty(get_lcp_array(sa, sa_inv, s)));
	}
	{
		string s = "a";
		auto [sa, sa_inv] = get_sa(s, 256);
		assert(empty(get_lcp_array(sa, sa_inv, s)));
	}
	string s;
	cin >> s;
	int n = ssize(s);
	lcp_query lq(s, 256);
	mono_st_asserts(lq.lcp);
	assert(ssize(lq.sa) == n);
	assert(ssize(lq.sa_inv) == n);
	assert(ssize(lq.lcp) == n - 1);
	{
		auto [sa_le, sa_ri, str_le, str_ri] = find_str(s, lq.sa, string(""));
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = find_substrs_concated(lq, {});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = find_substrs_concated(lq, {{0, 0}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = find_substrs_concated(lq, {{0, 0}, {n, n}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = find_substrs_concated(lq, {{0, 0}, {n / 2, n / 2}, {n, n}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	for (int i = 0; i < n; i++) {
		assert(lq.sa[lq.sa_inv[i]] == i);
		assert(lq.sa_inv[lq.sa[i]] == i);
	}
	for (auto val : lq.sa)
		cout << val << " ";
	cout << '\n';
}
