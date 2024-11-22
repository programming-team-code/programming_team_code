#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# doesn't compile with clang
rm library_checker_aizu_tests/handmade_tests/dynamic_bitset.test.cpp

git submodule init
git submodule update

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang++-18 {} "$(tr '\n' ' ' <.config/.clang_compile_flags)" -std=c++20
