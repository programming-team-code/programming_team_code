#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"

# remove `/** @file */` comments
sed --in-place '/^\/\*\* @file \*\/$/d' ../library/**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/ NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp

# to copy files like template.cpp, *.sh, *.png, *.md to root directory; so they exist in main branch
# also to create all directories (cpp command below fails if destination path isn't created)
cp -r ../library/. ../
cp -r ../kactl/content/. ../kactl_expanded_macros/

# in order to expand the kactl macros, you need to copy-paste the macros into
# the beginning of each .hpp file
for header in ../library/**/*.hpp; do
	cpp -std=c17 -nostdinc -C -P <(cat library_checker_aizu_tests/kactl_macros.hpp "$header") "${header/\/library/}"
done
for header in ../kactl/content/**/*.h; do
	cpp -std=c17 -nostdinc -C -P <(cat library_checker_aizu_tests/kactl_macros.hpp "$header") "${header/kactl\/content/kactl_expanded_macros}"
done

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../**/*.hpp ../**/*.h
# cpp command messes up formatting
make do_format
