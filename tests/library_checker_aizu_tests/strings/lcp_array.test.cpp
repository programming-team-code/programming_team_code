#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"
#include "../../../library/strings/suffix_array_related/lcp_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//to test commented example
		string s = "banana";
		auto [sa, sa_inv] = get_sa(s, 256);
		vector<int> lcp = get_lcp_array(sa, sa_inv, s);
		assert(sa == vector<int>({5, 3, 1, 0, 4, 2}));
		assert(sa_inv == vector<int>({3, 2, 5, 1, 4, 0}));
		assert(lcp == vector<int>({1, 3, 0, 0, 2}));
	}
	string s;
	cin >> s;
	int n = ssize(s);
	auto [sa, sa_inv] = get_sa(s, 256);
	vector<int> lcp = get_lcp_array(sa, sa_inv, s);
	assert(ssize(lcp) == n - 1);
	cout << 1LL * n * (n + 1) / 2 - accumulate(begin(lcp), end(lcp), 0LL) << '\n';
}
