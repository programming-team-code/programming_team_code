#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"

# to copy files like template.cpp, *.sh, *.png, *.md to root directory; so they exist in main branch
# also to create all directories (cpp command below fails if destination path isn't created)
cp -r ../library/. ../

for header in ../library/**/*.hpp; do
	cpp -std=c17 -nostdinc -C -P "$header" "${header/\/library/}"
done

# cpp command messes up formatting
astyle --options=.config/.astylerc --recursive "../*.hpp"
# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../**/*.hpp
# remove `/** @file */` comments
sed --in-place '/^\/\*\* @file \*\/$/d' ../**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/NOLINTNEXTLINE(readability-identifier-naming)$/d' ../**/*.hpp
