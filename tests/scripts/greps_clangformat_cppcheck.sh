#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# miscellaneous checks - done before initializing git submodules to avoid checking stuff not in our code

echo "check NULL instead of nullptr"
grep "nullptr" --recursive ../library/ && exit 1

echo "check no endl"
grep "endl" --recursive library_checker_aizu_tests/ && exit 1

echo "check template<class T> over template<typename T>:"
grep --extended-regexp "template\s?<typename" --recursive ../library/ && exit 1

echo "check 1 instead of true"
grep "true" --recursive ../library/ && exit 1

echo "check 0 instead of false"
grep "false" --recursive ../library/ && exit 1

echo "check ll instead of long long or int64_t"
grep "long long" --recursive ../library/ && exit 1
grep "int64_t" --recursive ../library/**/*.hpp | grep "uint64_t" --invert-match && exit 1

echo "check pii instead of pair<int, int>"
grep "pair<int, int>" --recursive ../library/**/*.hpp && exit 1

echo "check sz instead of ssize"
grep "ssize" --recursive ../library/ && exit 1

echo "check vi instead of vector<int>"
grep "vector<int>" --recursive ../library/ && exit 1

echo "check begin(arr) instead of arr.begin(), similarly for end, rbegin, rend, empty, size:"
# TODO: remove this define filter if/when we move to -std=c++20
grep --invert-match --fixed-strings "#define" --recursive ../library/ library_checker_aizu_tests/ |
	grep --fixed-strings --regexp=".begin()" --regexp=".rbegin()" --regexp=".end()" --regexp=".rend()" --regexp=".empty()" --regexp=".size()" && exit 1

echo "check that there are no empty lines"
grep "^$" ../library/**/*.hpp && exit 1

echo "check files and directories are snake_case:"
find ../library/ library_checker_aizu_tests/ -name "*[A-Z]*" -or -name "*-*" |
	grep --invert-match ".verify-helper" |
	grep --invert-match "README" &&
	exit 1

clang-format-19 --dry-run --Werror --style=file:.config/.clang-format library_checker_aizu_tests/**/*.hpp library_checker_aizu_tests/**/*.test.cpp ../library/**/*.hpp ../library/**/*.cpp || exit 1

git submodule init
git submodule update

cppcheck --enable=all --inconclusive --suppressions-list=.config/.cppcheck_suppression_list \
	--force --language=c++ --error-exitcode=1 --std=c++20 --max-ctu-depth=50 \
	library_checker_aizu_tests/**/*.hpp library_checker_aizu_tests/**/*.test.cpp ../library/**/*.hpp ../library/**/*.cpp ||
	exit 1
