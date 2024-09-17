#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# first remove @see <link> comments: these aren't useful in the PDF, and are
# usually the longest words which extend into the next column
echo "removing links"
sed --in-place '/\/\/! @see http/d' ../library/**/*.hpp

# PDF will wrap at 66 characters, but when the PDF wraps, it goes onto the next
# line with an indent of a few characters
WORD_LENGTH_THRESHOLD=61
echo "The following words are > $WORD_LENGTH_THRESHOLD characters, and won't wrap in PDF:"
cat ../library/**/*.hpp |
	tr '[:blank:]' '\n' |
	awk --assign=max_len="$WORD_LENGTH_THRESHOLD" '{if(length>max_len)print$0}' |
	grep . &&
	exit 1

echo "check no multiline comments. Generating hash of each prefix of a file requires this."
grep --extended-regexp "\/\*" --recursive ../library/**/*.hpp && exit 1

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"

# remove #pragma once
sed --in-place '/^#pragma once$/d' ../library/**/*.hpp
# remove //! @file
sed --in-place '/^\/\/! @file$/d' ../library/**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/ NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp

#adds hash code comments
chmod +x ../library/contest/hash.sh
for header in ../library/**/*.hpp; do
	echo "$header"
	for i in $(seq "$(wc --lines <"$header")" -5 1); do
		hash=$(head --lines "$i" "$header" | sed '/^#include/d' | cpp -dD -P -fpreprocessed | ./../library/contest/hash.sh)
		line_length=$(sed --quiet "${i}p" "$header" | wc --chars)
		# PDF wraps at 66 chars, and hash comment takes 8 chars total
		padding_length=$((66 - 8 - line_length))
		padding_length=$((padding_length > 0 ? padding_length : 0))
		padding=$(printf '%*s' "$padding_length" '')
		sed --in-place "${i}s/$/$padding\/\/${hash}/" "$header"
	done
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
