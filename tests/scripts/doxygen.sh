#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

cd ../library/ || exit 1

echo ".hpp files missing the @file tag:"
comm -23 --check-order <(
	find . -type f -name "*.hpp" |
		sort |
		uniq
) <(
	grep --fixed-strings "//! @file" --recursive . --files-with-matches |
		sort |
		uniq
) |
	grep . &&
	exit 1

doxygen ../tests/.config/Doxyfile
