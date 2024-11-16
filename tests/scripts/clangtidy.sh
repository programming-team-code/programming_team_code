#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

cp library_checker_aizu_tests/kactl_macros_gcc17.hpp library_checker_aizu_tests/kactl_macros_gcc20.hpp

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=c++20 ||
	exit 1
