# !/bin/bash

yacc -d -y --debug --verbose 22299480.y
echo 'Generated the parser C file and header file'

g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'

flex 22299480.l
echo 'Generated the scanner C file'

g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'

# g++ -o analyzer y.o l.o
g++ y.o l.o
echo 'All ready, running'
