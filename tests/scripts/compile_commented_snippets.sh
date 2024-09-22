#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar


# the flags we want:
cpp -std=c17 -nostdinc -P ../library/data_structures/bit.hpp




# 



for header in ../library/**/*.hpp; do
	# see https://github.com/programming-team-code/kactl_no_macros/blob/main/remove_macros.sh
	cpp -std=c17 -nostdinc -C -P "$header" | cat library_checker_aizu_tests/kactl_macros.hpp - | cpp -std=c17 -nostdinc -C -P - -o "${header/\/library/}"
done


hash=$(head --lines "$i" "$header" | sed '/^#include/d' | cpp -dD -P -fpreprocessed | ./../library/contest/hash.sh)
