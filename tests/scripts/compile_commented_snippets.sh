#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

touch entire_library.cpp

# build cpp file with everything in the library with all code in @code ...
# @endcode comments in main

{
	echo "#include <bits/stdc++.h>"
	echo "using namespace std;"
	cat library_checker_aizu_tests/actual_kactl_macros.hpp
	echo "const ll mod = (119 << 23) + 1, root = 62;"
	find ../library/ -type f -name "*.hpp" | grep --invert-match --file=.config/.code_snippet_excluded_file_list | sort | sed 's/^/#include "/; s/$/"/' | cpp -std=c17 -nostdinc -C -P | grep --invert-match --extended-regexp "const int mod = |const ll mod = "
	echo "int main() {"
} >>entire_library.cpp

{
	sed --quiet '/\/\/! @code$/,/\/\/! @endcode$/{//!p;}' entire_library.cpp | sed 's/\/\/!//'
	echo "return 0;"
	echo "}"
} >>entire_library.cpp
