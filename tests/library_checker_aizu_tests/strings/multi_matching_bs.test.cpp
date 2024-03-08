#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array/suffix_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		suffix_array sf_a(string(""), 256);
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_str(string(""));
		assert(sa_le == 0 && sa_ri == 0 && str_le == 0 && str_ri == 0);
	}
	string s;
	cin >> s;
	suffix_array sf_a(s, 256);
	{
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_str(string(""));
		assert(sa_le == 0 && sa_ri == ssize(s));
		assert(str_ri - str_le == 0);
	}
	int q;
	cin >> q;
	while (q--) {
		string t;
		cin >> t;
		auto [sa_le, sa_ri, str_le, str_ri] = sf_a.find_str(t);
		int str_len = str_ri - str_le;
		assert(str_len <= ssize(t));
		assert(s.substr(str_le, str_len) == t.substr(0, str_len));
		assert(str_len == ssize(t) || str_ri == ssize(s) || t[str_len] != s[str_ri]);
		assert((sa_le < sa_ri) == (str_len == ssize(t)));
		cout << (!!(sa_ri - sa_le > 0)) << '\n';
	}
	return 0;
}
