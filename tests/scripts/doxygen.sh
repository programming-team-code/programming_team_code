#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

cd ../library/ || exit 1

doxygen ../tests/.config/Doxyfile
