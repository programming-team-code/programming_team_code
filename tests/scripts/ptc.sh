#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"
echo "if you push these changes, I'll slap your butt"

# remove some files not suitable for PDF:
rm ../library/data_structures/bit_uncommon/rupq.hpp
rm ../library/data_structures/bit_uncommon/rurq.hpp
rm ../library/data_structures/seg_tree.png
rm ../library/data_structures/seg_tree_uncommon/distinct_query.hpp
rm ../library/data_structures/seg_tree_uncommon/implicit.hpp
rm ../library/data_structures/seg_tree_uncommon/kth_smallest_query.hpp
rm ../library/data_structures/uncommon/mode_query.hpp
rm ../library/data_structures/uncommon/priority_queue_of_updates.hpp
rm ../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp
rm ../library/math/derangements.hpp
rm ../library/math/num_distinct_subsequences.hpp
rm ../library/math/partitions.hpp
rm ../library/monotonic_stack/cartesian_k_ary_tree.hpp
rm ../library/monotonic_stack/max_rect_histogram.hpp
rm ../library/monotonic_stack/cartesian_binary_tree_after.png
rm ../library/monotonic_stack/mono_stack_ri.png
rm ../library/strings/manacher/longest_palindrome_query.hpp
rm -rf ../library/trees/centroid_decomp_uncommon/
rm -rf ../library/trees/edge_centroid_decomp_uncommon/
rm -rf ../library/trees/ladder_decomposition/ladder_decomposition.hpp
rm ../library/trees/linear_kth_path.hpp

# remove links in comments: these aren't useful in the PDF, and are usually the
# longest words which extend into the next column
echo "removing links"
sed --in-place '/\/\/! https/d' ../library/**/*.hpp

# PDF will wrap at 68 characters. Let's check that there's no long words, as
# they won't wrap in PDF
WORD_LENGTH_THRESHOLD=61
echo "The following words are > $WORD_LENGTH_THRESHOLD characters, and won't wrap in PDF:"
cat ../library/**/*.hpp |
	tr '[:blank:]' '\n' |
	awk --assign=max_len="$WORD_LENGTH_THRESHOLD" '{if(length>max_len)print$0}' |
	grep . &&
	exit 1

echo "check no multiline comments. Generating hashes of file-prefixes requires this."
grep --extended-regexp "\/\*" --recursive ../library/**/*.hpp && exit 1

make compile_commented_snippets || exit 1

# remove #pragma once
sed --in-place '/^#pragma once$/d' ../library/**/*.hpp
# remove NOLINTNEXTLINE comments
sed --in-place '/^\/\/ NOLINTNEXTLINE(readability-identifier-naming)$/d' ../library/**/*.hpp

#adds hash code comments
chmod +x ../library/contest/hash.sh
for header in ../library/**/*.hpp; do
	echo "adding hash codes for $header"
	for i in $(seq "$(wc --lines <"$header")" -5 1); do
		hash=$(head --lines "$i" "$header" | sed '/^#include/d' | cpp -dD -P -fpreprocessed | ./../library/contest/hash.sh)
		line_length=$(sed --quiet "${i}p" "$header" | wc --chars)
		# PDF wraps at 68 chars, and hash comment takes 8 chars total
		padding_length=$((68 - 8 - line_length))
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
