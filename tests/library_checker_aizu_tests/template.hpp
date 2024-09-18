// to avoid bits/stdc++.h include which slows down CI
// modifying this file will re-run all library checker tests
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric> //for iota
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
// for random numbers
#include <stdint.h> // for uint64_t
#include <bitset>
#include <chrono>
#include <climits> // for INT_MAX, INT_MIN
#include <complex> //for kactl's FFT
#include <functional> //for lambdas
#include <optional>
#include <random>
#include <utility> // for std::exchange
using namespace std;
// https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/template.cpp
// compile all tests with KACTL macros mainly to avoid naming
// collisions when combining code from both repos
//
// also defines are used here instead of typedef/using's
// (even though it's sketchier) so that they can be expanded
// before pushing to main
//
// modifying kactl_macros.hpp will also re-run all library
// checker tests
#include "kactl_macros.hpp"
