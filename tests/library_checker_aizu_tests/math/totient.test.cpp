#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"
#include "../template.hpp"

#include "../../../library/math/totient.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	cout << totient(n) << '\n';
	return 0;
}
