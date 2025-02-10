#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

clang-format-19 -i --style=file:.config/.clang-format ../**/*.hpp ../**/*.cpp
