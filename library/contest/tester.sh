# https://github.com/Errichto/youtube/blob/master/testing/s.sh
# bash tester_diff.sh a naive gen

g++ -std=c++20 -g -D_GLIBCXX_DEBUG -fsanitize=address,undefined $1.cpp -o $1.out
g++ -std=c++20 $2.cpp -o $2.out
g++ -std=c++20 $3.cpp -o $3.out

for((i = 1; ; ++i))
do
	echo $i
	./$3.out > input
	diff -w <(./$1.out < input) <(./$2.out < input) || break
done
