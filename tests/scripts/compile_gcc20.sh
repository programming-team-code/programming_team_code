#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# remove ssize macro first
sed --in-place '/ssize/d' library_checker_aizu_tests/template.hpp

find library_checker_aizu_tests/ -type f -name "*.test.cpp" |
	parallel g++ {} "$(tr '\n' ' ' <.config/.gcc_compile_flags)" -std=c++20 -Wno-narrowing
