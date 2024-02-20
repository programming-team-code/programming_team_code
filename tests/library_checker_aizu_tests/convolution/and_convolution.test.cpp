#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"
#include "../template.hpp"

#include "../../../library/convolution/and_convolution.hpp"

istream& operator >> (istream& is, vector<int>& v) {
	for (auto& x : v)
		is >> x;
	return is;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> a(1 << n), b(1 << n);
	cin >> a >> b;
	auto c = and_convolution(a, b);
	for (int i = 0; i < (1 << n); i++)
		cout << c[i] << ' ';
	cout << '\n';
	return 0;
}
