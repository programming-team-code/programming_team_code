#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel clang-tidy --config-file=.config/.clang-tidy {} -- -std=gnu++20 ||
	exit 1
