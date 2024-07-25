#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# compile lib with actual kactl macros
# catches things like ll(x) (works with int64_t, but not with long long)
cp library_checker_aizu_tests/actual_kactl_macros.hpp library_checker_aizu_tests/kactl_macros.hpp

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel g++ {} "$(tr '\n' ' ' <.config/.gcc_compile_flags)" -std=c++20 -Wno-narrowing
