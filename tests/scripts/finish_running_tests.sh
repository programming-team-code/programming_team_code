#!/bin/bash
# ** glob now searches any number of levels
shopt -s globstar

# assuming you're on `dev` branch, and in `tests` folder, and
# have run this via `make finish_running_tests`

echo "pulling dev"
git pull

while ! make print_which_tests_havent_run; do
	echo "not all tests ran; starting CI to run more tests"
	gh workflow run 'programming team code CI' --ref dev
	echo "sleeping for 15 minutes"
	sleep 15m
	echo "pulling dev"
	git pull
done
