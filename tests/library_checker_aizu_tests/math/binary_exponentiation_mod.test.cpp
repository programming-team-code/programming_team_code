#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"
#include "../template.hpp"

#include "../../../library/math/tetration_mod.hpp"
#include "../../../library/math/binary_exponentiation_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int m, n;
	cin >> m >> n;
	assert(bin_exp(m, n, 998'244'353) == bin_exp(m, n));
	if (n & 1) {
		assert(bin_exp(-m, n, 998'244'353) == (998'244'353 - bin_exp(m, n)) % 998'244'353);
		assert((998'244'353 - bin_exp(m, n, 998'244'353)) % 998'244'353 == bin_exp(-m, n));
	} else {
		assert(bin_exp(-m, n, 998'244'353) == bin_exp(m, n));
		assert(bin_exp(m, n, 998'244'353) == bin_exp(-m, n));
	}
	cout << bin_exp(m, n, 1'000'000'007) << '\n';
	return 0;
}
