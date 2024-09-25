#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# compile lib with actual kactl macros
cp library_checker_aizu_tests/actual_kactl_macros.hpp library_checker_aizu_tests/kactl_macros.hpp

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel g++ {} "$(tr '\n' ' ' <.config/.compile_flags)" -std=c++20 -Wno-narrowing
