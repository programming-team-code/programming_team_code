#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

touch entire_library.cpp

# build cpp file with everything in the library with all code in @code ...
# @endcode comments in main

echo "#include <bits/stdc++.h>" >> entire_library.cpp
echo "using namespace std;" >> entire_library.cpp
cat library_checker_aizu_tests/actual_kactl_macros.hpp >> entire_library.cpp
echo "const ll mod = (119 << 23) + 1, root = 62;" >> entire_library.cpp
find ../library/ -type f -name "*.hpp" | grep --invert-match --file=.config/.code_snippet_excluded_file_list | sed 's/^/#include "/; s/$/"/' | cpp -std=c17 -nostdinc -C -P | grep --invert-match --extended-regexp "const int mod = |const ll mod = " >> entire_library.cpp
echo "int main() {" >> entire_library.cpp
echo "return 0;" >> entire_library.cpp
echo "}" >> entire_library.cpp

#cpp -std=c17 -nostdinc -C -P library_checker_aizu_tests/template.hpp > entire_library.cpp

sed --quiet '/\/\/! @code$/,/\/\/! @endcode$/{//!p;}' ../library/data_structures/bit.hpp
