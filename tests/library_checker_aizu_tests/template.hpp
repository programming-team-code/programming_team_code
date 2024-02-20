//to avoid bits/stdc++.h include which slows down CI
//modifying this file will re-run all library checker tests
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <string>
#include <array>
#include <numeric> //for iota
//for random numbers
#include <chrono>
#include <random>
#include <complex> //for kactl's FFT
#include <functional> //for lambdas
#include <climits> // for INT_MAX, INT_MIN
#include <optional>
#include <stdint.h> // for uint64_t
#include <bitset>
using namespace std;

#define ssize(x) (int)(x).size()

//https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/template.cpp
//compile all tests with KACTL macros mainly to avoid naming collisions when
//combining code from both repos
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef int64_t ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
