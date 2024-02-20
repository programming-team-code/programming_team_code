help:
	@echo "command                              | explanation"
	@echo "------------------------------------ | -----------"
	@echo "make compile_gcc17                   | compile all tests with -std=c++17 for warnings"
	@echo "                                     |"
	@echo "make compile_gcc20                   | compile all tests with -std=c++20 without ssize macro for warnings"
	@echo "                                     |"
	@echo "make astyle_cppcheck                 | runs astyle, cppcheck"
	@echo "                                     |"
	@echo "make clangtidy                       | runs clang-tidy (mainly to verify snake_case)"
	@echo "                                     |"
	@echo "make doxygen                         | runs doxygen"
	@echo "                                     |"
	@echo "make ptc                             | build ptc.pdf from .tex file"
	@echo "                                     |"
	@echo "make shellcheck_shfmt                | runs shellcheck and shfmt"
	@echo "                                     |"
	@echo "make update_main                     | 1) copies included files into file"
	@echo "                                     | 2) pushes to main branch"
	@echo "                                     |"
	@echo "make files_without_tests             | print list of all .hpp files included by *no* .test.cpp files"
	@echo "                                     |   - these files are not compiled nor linted as part of ci"
	@echo "                                     |"
	@echo "make print_which_tests_havent_run    | mainly to check if all tests have run"

compile_gcc17:
	./scripts/compile_gcc17.sh

compile_gcc20:
	./scripts/compile_gcc20.sh

astyle_cppcheck:
	./scripts/astyle_cppcheck.sh

clangtidy:
	./scripts/clangtidy.sh

files_without_tests:
	./scripts/files_without_tests.sh

doxygen:
	./scripts/doxygen.sh

ptc:
	./scripts/ptc.sh

shellcheck_shfmt:
	./scripts/shellcheck_shfmt.sh

update_main:
	./scripts/update_main.sh

print_which_tests_havent_run:
	./scripts/print_which_tests_havent_run.sh

remove_randomly_generated_tests:
	./scripts/remove_randomly_generated_tests.sh
