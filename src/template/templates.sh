##### gdb #####
*`setxkbmap -option ctrl:nocaps`
gdbcmd
```
r
bt
```
gdb a.out -x gdbcmd
echo -ne "r\nbt" | gdb ./a.out 2>&1 | grep -n2 $(basename `pwd`).cpp

##### build env #####
alias g++="g++ -std=c++1y -O2 -Wall -Wshadow -D_GLIBCXX_DEBUG -g"
mkdir {a..l}

vim template.cpp

for d in {a..l}
do
cp template.cpp $d/$d.cpp
done
