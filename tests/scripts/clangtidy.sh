#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# version 17 is used temporarily as there's some randome bug on 20
# https://stackoverflow.com/q/68475958
find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=c++17 ||
	exit 1
