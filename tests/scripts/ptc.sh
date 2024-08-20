#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

WORD_LENGTH_THRESHOLD=63
echo "The following words are > $WORD_LENGTH_THRESHOLD characters, and won't wrap in PDF:"
cat ../library/**/*.hpp |
	tr '[:blank:]' '\n' |
	awk --assign=max_len="$WORD_LENGTH_THRESHOLD" '{if(length>max_len)print$0}' |
	grep . &&
	exit 1

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"

# remove #pragma once
sed --in-place '/^#pragma once$/d' ../library/**/*.hpp
# remove /** @file */
sed --in-place '/^\/\*\* @file \*\/$/d' ../library/**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp
# remove clang-format off comments
sed --in-place '/\/\/clang-format off$/d' ../library/**/*.hpp

#adds hash code comments
chmod +x ../library/contest/hash.sh
for header in ../library/**/*.hpp; do
	hash=$(sed '/^#include/d' "$header" | cpp -dD -P -fpreprocessed | ./../library/contest/hash.sh)
	sed --in-place "1i //hash: $hash" "$header"
done

git submodule init
git submodule update

# install dependencies listed in ../notebook-generator/package.json
npm ci --prefix ../notebook-generator/
npm run test --prefix ../notebook-generator/

# underscores in file names look bad in ptc, so this
# replaces all underscores with spaces
# note, this is the perl `rename` command, not the linux util
find ../library/ -depth -execdir rename 'y/_/ /' {} +

# regarding school branding: https://brand.sdsmt.edu/identity/our-name/
# in particular, no initials
# logo taken from https://brand.sdsmt.edu/identity/official-logos/
./../notebook-generator/bin/notebookgen ../library/ --author "South Dakota Mines" --output ./ptc.pdf --size 8 --columns 3 --image images/south_dakota_mines_logo.png
