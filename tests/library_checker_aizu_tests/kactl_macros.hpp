// https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/template.cpp
// compile all tests with KACTL macros mainly to avoid naming collisions when
// combining code from both repos
//
// also defines are used here instead of typedef/using's (even though it's sketchier)
// so that they can be expanded before pushing to main
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ll int64_t
#define pii pair<int, int>
#define vi vector<int>
