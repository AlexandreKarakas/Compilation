bison -d TP.y
flex TP.l
gcc -o Programme TP.c TP.tab.c lex.yy.c
echo 'ready'
./Programme
