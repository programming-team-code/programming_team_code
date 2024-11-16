#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# build cpp file with everything in the library with all code in @code ...
# @endcode comments in main

{
	cat library_checker_aizu_tests/template.hpp
	echo "const ll mod = (119 << 23) + 1, root = 62;"
	find ../library/ -type f -name "*.hpp" | grep --invert-match --file=.config/.code_snippet_excluded_file_list | sort | sed 's/^/#include "/; s/$/"/' | cpp -std=c17 -nostdinc -C -P | grep --invert-match --extended-regexp "const int mod = |const ll mod = "
	echo "int main() {"
	echo "vi a,b,subset;"
	echo "vl left,bottom,s_vec,t_vec;"
	echo "vector<vi> adj;"
	echo "vector<vector<pair<int,ll>>> adj_w;"
	echo "vector<pii> edges;"
	echo "vector<array<int,2>> eds;"
	echo "vector<array<int,3>> w_eds;"
	echo "vector<mint> rhs;"
	echo "vector<vector<mint>> mat;"
	echo "vector<vector<bool>> grid;"
	echo "string s,t;"
	echo "int n,m,k,tl,tr,l,r,l1,r1,l2,r2,s_l,s_r,root_l,root_r,source,sink,total_flow,bccid,u,v,rsz,cols,cap;"
} >entire_library_without_main

{
	cat entire_library_without_main
	sed --quiet '/\/\/! @code$/,/\/\/! @endcode$/{//!p;}' entire_library_without_main | sed 's/\/\/!//'
	echo "return 0;"
	echo "}"
} >entire_library.cpp

echo "compiling code in @code ... @endcode comments with g++"
g++ -std=c++20 entire_library.cpp || exit 1

echo "compiling code in @code ... @endcode comments with clang++"
clang++ -std=c++20 -Wno-narrowing entire_library.cpp || exit 1
