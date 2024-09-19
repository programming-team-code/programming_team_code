# https://github.com/Errichto/youtube/blob/master/testing/s.sh
# bash tester.sh

g++ -std=c++17 a.cpp -o a.out
g++ -std=c++17 b.cpp -o b.out
g++ -std=c++17 gen.cpp -o gen.out

for((i = 1; ; ++i))
do
	echo $i
	./gen.out > input
	diff -w <(./a.out < input) <(./b.out < input) || break
done
