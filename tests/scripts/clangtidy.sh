#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# doesn't compile with clang
rm library_checker_aizu_tests/handmade_tests/dynamic_bitset.test.cpp

git submodule init
git submodule update

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy-18 --config-file=.config/.clang-tidy {} -- -std=c++20 ||
	exit 1
