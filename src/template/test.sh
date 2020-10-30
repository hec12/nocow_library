#!/bin/sh

rm -f a.out
g++ *.cpp -std=c++1y -O2 -Wall -Wshadow -D_GLIBCXX_DEBUG -g
if [ $? = 0 -a $1 ]; then
	./a.out < sample$1.in > sample$1.out
	diff sample$1.out sample$1.ans
	if [ $? = 0 ]; then
		echo "sample OK"
	fi
fi
