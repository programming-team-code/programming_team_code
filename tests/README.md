## Makefile
to see commands:
```
make help
```

## Run on each commit:
command | settings | notes | see
--- | --- | --- | ---
oj-verify | [config.toml](../.verify-helper/config.toml) | <ul><li>Run from `programming_team_code/` to enable `config.toml` settings, else disabled.</li><li>[Check/Delete] [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to [see which tests ran/re-run all tests].</li></ul> | <ul><li>https://online-judge-tools.github.io/verification-helper/document.html</li><li>https://online-judge-tools.github.io/verification-helper/installer.html</li><li>[Library Checker](https://judge.yosupo.jp/)</li><li>[Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list)</li></ul>
g++ | [.config/.gcc_compile_flags](.config/.gcc_compile_flags) | <ul><li>`-std=c++17` since some judges still have this version</li><li>`-Wconversion`, `-Wsign-conversion` is out of scope</li><li>`-Werror` treats warnings as errors to make CI fail</li></ul> | <ul><li>https://codeforces.com/blog/entry/15547</li><li>https://codeforces.com/blog/entry/74032</li><li>https://codeforces.com/blog/entry/79024</li></ul>
clang-format | [.config/.clang-format](.config/.clang-format) | running `make do_format` locally will format files | https://clang.llvm.org/docs/ClangFormat.html
cppcheck | [.config/.cppcheck_suppression_list](.config/.cppcheck_suppression_list), also see flags in cppcheck command in [scripts/foramt_lint.sh](scripts/foramt_lint.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.config/.clang-tidy](.config/.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
notebook-generator | see flags in command in [scripts/ptc.sh](scripts/ptc.sh) | creates ptc.pdf | https://github.com/pin3da/notebook-generator 
shellcheck | see flags in [scripts/shellcheck_shfmt.sh](scripts/shellcheck_shfmt.sh) | linter for bash scripts | https://www.shellcheck.net/
shfmt | see flags in [scripts/shellcheck_shfmt.sh](scripts/shellcheck_shfmt.sh) | formatter for bash scripts | https://github.com/mvdan/sh

## Doxygen
Let's try to minimize the # of non-doxygen comments.

Place this at the beginning of a file

```
//! https://codeforces.com/blog/entry/69247
//! @code
//!   //example usage or initialization
//!   vector<int> arr;
//! @endcode
//! @time O(n * sqrt(n log n))
//! @space O(n ^ (3/2))
```
