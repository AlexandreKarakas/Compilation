bison -d TP.y
flex TP.l
gcc -g -o Programme TP.c TP.tab.c lex.yy.c
