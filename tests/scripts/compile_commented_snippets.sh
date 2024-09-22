#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

# build cpp file with everything in the library with all code in @code ...
# @endcode comments in main

{
	echo "#include <bits/stdc++.h>"
	echo "using namespace std;"
	cat library_checker_aizu_tests/actual_kactl_macros.hpp
	echo "const ll mod = (119 << 23) + 1, root = 62;"
	find ../library/ -type f -name "*.hpp" | grep --invert-match --file=.config/.code_snippet_excluded_file_list | sort | sed 's/^/#include "/; s/$/"/' | cpp -std=c17 -nostdinc -C -P | grep --invert-match --extended-regexp "const int mod = |const ll mod = "
	echo "int main() {"
	echo "vi a,b;"
	echo "vl left,bottom;"
	echo "vector<vi> adj;"
	echo "vector<vector<pair<int,ll>>> adj_w;"
  echo "vector<pii> edges;"
  echo "vector<array<int,3>> w_eds;"
  echo "vector<vector<mint>> mat;"
  echo "vector<vector<bool>> grid;"
	echo "int n,m,k,le,ri,root_l,root_r,source,sink,total_flow,bccid,v,rsz,cols;"
} >entire_library_without_main

{
	cat entire_library_without_main
	sed --quiet '/\/\/! @code$/,/\/\/! @endcode$/{//!p;}' entire_library_without_main | sed 's/\/\/!//'
	echo "return 0;"
	echo "}"
} >entire_library.cpp

g++ <.config/.gcc_compile_flags -std=c++17 entire_library.cpp
