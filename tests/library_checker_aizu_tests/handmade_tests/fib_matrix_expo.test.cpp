#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/math/fibonacci.hpp"

//NOLINTNEXTLINE(readability-identifier-naming)
const int MOD = 998'244'353;

#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../hackpack-cpp/content/number-theory/ModInt.h"

void check(int64_t n) {
	using mat_2_by_2 = Matrix<mi, 2>;
	mat_2_by_2 mat;
	mat.d = {{{{1, 1}}, {{1, 0}}}};
	vector<mi> vec = {1, 0};
	int64_t res = fib(n)[0];
	assert(res == int(((mat ^ n) * vec)[1]));
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	//n=0 -> val=0
	//n=1 -> val=1
	//n=2 -> val=1
	//n=3 -> val=2
	//n=4 -> val=3
	//n=5 -> val=5
	assert(fib(0)[0] == 0);
	assert(fib(1)[0] == 1);
	assert(fib(2)[0] == 1);
	assert(fib(3)[0] == 2);
	assert(fib(4)[0] == 3);
	assert(fib(5)[0] == 5);
	for (int i = 0; i < 500; i++)
		check(i);
	for (int tests = 1000; tests--;)
		check(get_rand<int64_t>(0, LLONG_MAX));
	cout << "Hello World\n";
	return 0;
}
