/* fichier calc.l */

%{
/* fichier dans lequel est defini la macro constante NOMBRE */
#include "TP.tab.h"
%}
%%
[0-9]+ {yylval.num=atoi(yytext); return NOMBRE;}
([0-9]*[.])?[0-9]+ {yylval.num=atof(yytext); return NOMBRE;}
[a-z][a-z,A-Z,0-9,_,'-']* {yylval.id = yytext; return IDENT;}
"Vrai" {yylval.num=1; return BOOLEAN;}
"Faux" {yylval.num=0; return BOOLEAN;}
"<=" return infEgal;
"===" return Equals;
">=" return supEgal;
"&&" return Et;
"||" return Ou;
"!==" return Diff;
"**" return pow;

[ \t] ; /* ignore les blancs et tabulations */
\n return 0;
. return yytext[0];
%%

#include <stdio.h>
#include <stdlib.h>

commenteof()
{
  fprintf (stderr, "unexpected EOF inside comment");
  exit (1);
}

yywrap ()
{
  return (1);
}
