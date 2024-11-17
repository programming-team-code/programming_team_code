help:
	@echo "command                              | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_gcc                     | compile all tests with -std=c++20 for warnings"
	@echo "                                     |"
	@echo "make compile_clang                   | compile all tests with clang, -std=c++20 for warnings"
	@echo "                                     |"
	@echo "make check_format_lint               | checks format with clang-format, then cppcheck"
	@echo "                                     |"
	@echo "make do_format                       | format with clang-format"
	@echo "                                     |"
	@echo "make clangtidy                       | runs clang-tidy (mainly to verify snake_case)"
	@echo "                                     |"
	@echo "make ptc                             | build ptc.pdf from .tex file"
	@echo "                                     |"
	@echo "make shellcheck_shfmt                | runs shellcheck and shfmt"
	@echo "                                     |"
	@echo "make update_main                     | 1) copies included files into file"
	@echo "                                     | 2) force pushes to main branch"
	@echo "                                     |"
	@echo "make files_without_tests             | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci"
	@echo "                                     |"
	@echo "make print_which_tests_havent_run    | mainly to check if all tests have run"
	@echo "                                     |"
	@echo "make finish_running_tests            | manually trigger CI every 15 minutes until all tests have run"
	@echo "                                     |"
	@echo "make compile_commented_snippets      | compile code in @code...@endcode comments"

compile_gcc:
	./scripts/compile_gcc.sh

compile_clang:
	./scripts/compile_clang.sh

check_format_lint:
	./scripts/check_format_lint.sh

do_format:
	./scripts/do_format.sh

clangtidy:
	./scripts/clangtidy.sh

files_without_tests:
	./scripts/files_without_tests.sh

ptc:
	./scripts/ptc.sh

shellcheck_shfmt:
	./scripts/shellcheck_shfmt.sh

update_main:
	./scripts/update_main.sh

print_which_tests_havent_run:
	./scripts/print_which_tests_havent_run.sh

finish_running_tests:
	./scripts/finish_running_tests.sh

compile_commented_snippets:
	./scripts/compile_commented_snippets.sh
