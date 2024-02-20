#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

echo "bash scripts missing the bash shebang:"
comm -23 --check-order <(
	find scripts/ -type f -name "*.sh" |
		sort |
		uniq
) <(
	grep --recursive --fixed-strings --files-with-matches "#!/bin/bash" scripts/ |
		sort |
		uniq
) |
	grep . &&
	exit 1

echo "bash scripts in tests/scripts/ missing shopt -s globstar:"
comm -23 --check-order <(
	find scripts/ -type f -name "*.sh" |
		sort |
		uniq
) <(
	grep --recursive --fixed-strings --files-with-matches "shopt -s globstar" scripts/ |
		sort |
		uniq
) |
	grep . &&
	exit 1

shellcheck --shell=bash --check-sourced --enable=check-set-e-suppressed,quote-safe-variables ./**/*.sh || exit 1

shfmt -ln=bash -s -d -w ./**/*.sh || exit 1
