#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

git submodule init
git submodule update

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"

# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/ NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp

# to copy files like template.cpp, *.sh, *.png, *.md to root directory; so they exist in main branch
# also to create all directories (cpp command below fails if destination path isn't created)
cp -r ../library/. ../

for header in ../library/**/*.hpp; do
	# see https://github.com/programming-team-code/kactl_no_macros/blob/main/remove_macros.sh
	cpp -nostdinc -C -P "$header" | cat library_checker_aizu_tests/kactl_macros.hpp - | cpp -nostdinc -C -P - -o "${header/\/library/}"
done

# the cpp preprocessor sometimes leaves blank empty lines
sed --in-place '/^[[:space:]]*$/d' ../**/*.hpp
# cpp command messes up formatting
make do_format
