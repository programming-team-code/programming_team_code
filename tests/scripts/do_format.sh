#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

clang-format -i --style=file:.config/.clang-format library_checker_aizu_tests/**/*.hpp library_checker_aizu_tests/**/*.test.cpp ../library/**/*.hpp ../library/**/*.cpp
