#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

cp -r ../library/. ../

for header in ../library/**/*.hpp; do
	cpp -std=c17 -nostdinc -C -P "$header" "${header/\/library/}"
done

# cpp command changes tabs to white space
astyle --options=.config/.astylerc --recursive "../*.hpp"
# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../**/*.hpp
# remove `/** @file */` comments
sed --in-place '/^\/\*\* @file \*\/$/d' ../**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/NOLINTNEXTLINE(readability-identifier-naming)$/d' ../**/*.hpp
