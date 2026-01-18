#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# Intended usage:
# find ../library/ -type f -name "*.hpp" | ./scripts/compile_commented_snippets.sh
# build cpp file with all files passed in via stdin and with all code in @code ...
# @endcode comments in main

{
	echo "#include <bits/stdc++.h>"
	echo "using namespace std;"
	cat library_checker_aizu_tests/kactl_macros.hpp
	echo "const ll mod = (119 << 23) + 1, root = 62;"
	cat | grep --invert-match --file=.config/.code_snippet_excluded_file_list | sort | sed 's/^/#include "/; s/$/"/' | cpp -nostdinc -C -P | grep --invert-match --extended-regexp "const int mod = |const ll mod = "
	echo "int main() {"
	echo "vi a,b,subset;"
	echo "vector<ll> left,bottom;"
	echo "vector<pii> edges;"
	echo "vector<array<int,2>> eds;"
	echo "vector<array<int,3>> w_eds, queries;"
	echo "vi rhs;"
	echo "vector<vi> mat;"
	echo "vector<vector<bool>> grid;"
	echo "int n,m,k,tl,tr,l,r,l1,r1,l2,r2,s_l,s_r,root_l,root_r,source,sink,total_flow,bccid,u,v,lsz,rsz,cols,cap,num,x,y;"
} >entire_library_without_main

{
	cat entire_library_without_main
	sed --quiet '/\/\/! @code$/,/\/\/! @endcode$/p' entire_library_without_main | sed 's/\/\/! @code/{/' | sed 's/\/\/! @endcode/}/' | sed 's/\/\/!//'
	echo "return 0;"
	echo "}"
} >entire_library.cpp

echo "compiling code in @code ... @endcode comments with g++"
g++ -std=c++20 entire_library.cpp || exit 1

echo "compiling code in @code ... @endcode comments with clang++"
clang++-19 -std=c++20 entire_library.cpp || exit 1
