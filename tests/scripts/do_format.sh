#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

clang-format -i --style=file:.config/.clang-format ../**/*.hpp ../**/*.cpp
