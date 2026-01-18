#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

#############################################################################
############ DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!! ############
#############################################################################

echo "DON'T PUSH ANY OF THESE CHANGES TO THE REPO!!!!!!!!"
echo "if you push these changes, I'll slap your butt"

# remove some files not suitable for PDF:
rm "../library/data_structures_[l,r)/bit_uncommon/rupq.hpp" || exit 1
rm "../library/data_structures_[l,r)/bit_uncommon/rurq.hpp" || exit 1
rm "../library/data_structures_[l,r)/uncommon/seg_tree.png" || exit 1
rm "../library/data_structures_[l,r)/seg_tree_uncommon/distinct_query.hpp" || exit 1
rm "../library/data_structures_[l,r)/seg_tree_uncommon/implicit.hpp" || exit 1
rm "../library/data_structures_[l,r)/seg_tree_uncommon/kth_smallest_query.hpp" || exit 1
rm "../library/data_structures_[l,r)/uncommon/mode_query.hpp" || exit 1
rm "../library/data_structures_[l,r)/uncommon/priority_queue_of_updates.hpp" || exit 1
rm "../library/data_structures_[l,r)/uncommon/deque_op.hpp" || exit 1
rm ../library/graphs/strongly_connected_components/add_edges_strongly_connected.hpp || exit 1
rm ../library/graphs/strongly_connected_components/offline_incremental_scc.hpp || exit 1
rm ../library/graphs/uncommon/bridges.hpp || exit 1
rm ../library/graphs/uncommon/cuts.hpp || exit 1
rm ../library/graphs/uncommon/block_vertex_tree.hpp || exit 1
rm ../library/graphs/uncommon/bridge_tree.hpp || exit 1
rm ../library/math/derangements.hpp || exit 1
rm ../library/math/num_distinct_subsequences.hpp || exit 1
rm ../library/math/partitions.hpp || exit 1
rm ../library/monotonic_stack/cartesian_k_ary_tree.hpp || exit 1
rm ../library/monotonic_stack/max_rect_histogram.hpp || exit 1
rm ../library/monotonic_stack/cartesian_binary_tree_after.png || exit 1
rm ../library/monotonic_stack/mono_stack_ri.png || exit 1
rm ../library/strings/manacher/longest_palindrome_query.hpp || exit 1
rm ../library/trees/uncommon/count_paths_per_length.hpp || exit 1
rm ../library/trees/uncommon/count_paths_per_node.hpp || exit 1
rm ../library/trees/uncommon/contour_range_query.hpp || exit 1
rm ../library/trees/uncommon/contour_range_update.hpp || exit 1
rm ../library/trees/uncommon/sum_adjacent.hpp || exit 1
rm ../library/trees/uncommon/ladder_decomposition.hpp || exit 1

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

find ../library/ -path "../library/data_structures_\[l,r\]" -prune -o -type f -name "*.hpp" -print | ./scripts/compile_commented_snippets.sh || exit 1
rm entire_library_without_main || exit 1
rm entire_library.cpp || exit 1
find "../library/data_structures_[l,r]" -type f -name "*.hpp" | ./scripts/compile_commented_snippets.sh || exit 1

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
