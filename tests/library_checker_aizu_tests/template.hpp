// to avoid bits/stdc++.h include which slows down CI
// modifying this file will re-run all library checker tests
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>  //for iota
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
// for random numbers
#include <stdint.h>  // for uint64_t

#include <bitset>
#include <chrono>
#include <climits>     // for INT_MAX, INT_MIN
#include <complex>     //for kactl's FFT
#include <functional>  //for lambdas
#include <optional>
#include <random>
using namespace std;

#define ssize(x) (int)(x).size()

// https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/template.cpp
// compile all tests with KACTL macros mainly to avoid naming collisions when
// combining code from both repos
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef int64_t ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
