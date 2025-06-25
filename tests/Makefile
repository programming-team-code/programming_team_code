help:
	@echo "command                              | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_gcc                     | compile all tests with -std=c++20 for warnings"
	@echo "                                     |"
	@echo "make compile_clang                   | compile all tests with clang, -std=c++20 for warnings"
	@echo "                                     |"
	@echo "make compile_commented_snippets      | compile code in @code...@endcode comments"
	@echo "                                     |"
	@echo "make grep_clangformat_cppcheck       | various greps to catch certain things, clang-format, cppcheck"
	@echo "                                     |"
	@echo "make do_format                       | format with clang-format"
	@echo "                                     |"
	@echo "make clangtidy                       | runs clang-tidy (mainly to verify snake_case)"
	@echo "                                     |"
	@echo "make build_pdf                       | build build_pdf.pdf from .tex file"
	@echo "                                     |"
	@echo "make shellcheck_shfmt                | runs shellcheck and shfmt"
	@echo "                                     |"
	@echo "make update_main                     | 1) copies included files into file"
	@echo "                                     | 2) force pushes to main branch"
	@echo "                                     |"
	@echo "make find_files_without_tests        | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci"
	@echo "                                     |"
	@echo "make print_which_tests_havent_run    | mainly to check if all tests have run"

compile_gcc:
	./scripts/compile_gcc.sh

compile_clang:
	./scripts/compile_clang.sh

grep_clangformat_cppcheck:
	./scripts/grep_clangformat_cppcheck.sh

do_format:
	./scripts/do_format.sh

clangtidy:
	./scripts/clangtidy.sh

find_files_without_tests:
	./scripts/find_files_without_tests.sh

build_pdf:
	./scripts/build_pdf.sh

shellcheck_shfmt:
	./scripts/shellcheck_shfmt.sh

update_main:
	./scripts/update_main.sh

print_which_tests_havent_run:
	./scripts/print_which_tests_havent_run.sh

compile_commented_snippets:
	./scripts/compile_commented_snippets.sh
