#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		string s;
		suffix_array sf_a(s, 256);
		assert(empty(sf_a.lcp));
	}
	{
		string s = "a";
		suffix_array sf_a(s, 256);
		assert(empty(sf_a.lcp));
	}
	string s;
	cin >> s;
	int n = ssize(s);
	suffix_array sf_a(s, 256);
	mono_st_asserts(sf_a.lcp);
	assert(ssize(sf_a.sa) == n);
	assert(ssize(sf_a.sa_inv) == n);
	assert(ssize(sf_a.lcp) == n - 1);
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_str(string(""));
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_substrs_concated({});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_substrs_concated({{0, 0}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_substrs_concated({{0, 0}, {n, n}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_substrs_concated({{0, 0}, {n / 2, n / 2}, {n, n}});
		assert(sa_le == 0 && sa_ri == n);
		assert(str_ri - str_le == 0);
	}
	for (int i = 0; i < n; i++) {
		assert(sf_a.sa[sf_a.sa_inv[i]] == i);
		assert(sf_a.sa_inv[sf_a.sa[i]] == i);
	}
	for (auto val : sf_a.sa)
		cout << val << " ";
	cout << '\n';
}
