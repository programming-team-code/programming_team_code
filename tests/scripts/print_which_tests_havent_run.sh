#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# so that paths match up for comm command (otherwise you need basename)
cd ..

echo "total number of tests:"
find tests/library_checker_aizu_tests/ -type f -name "*.test.cpp" | wc --lines

echo "number of tests which have run:"
grep --count "test.cpp" .verify-helper/timestamps.remote.json

echo "tests which have *not* run:"
! comm -23 --check-order <(
	find tests/library_checker_aizu_tests/ -type f -name "*.test.cpp" |
		sort |
		uniq
) <(
	grep --only-matching '".*test.cpp"' .verify-helper/timestamps.remote.json |
		tr -d '"' |
		sort |
		uniq
) |
	grep .
