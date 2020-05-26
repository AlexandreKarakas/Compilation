%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "parser.tab.h"
%}

%%
[ \t]+                                ; /* ignore les blancs et tabulations */
"//".*                                ; /* ignore les commentaires uniligines */
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]   ; /* ignore les commentaires multilignes */
"/*"                                  yy_fatal_error("Commentaire non fermé");
[0-9]+                                yylval.num=atoi(yytext); return NOMBRE;
([0-9]*[.])?[0-9]+                    yylval.num=atof(yytext); return NOMBRE;
[a-z][a-zA-Z0-9\_\-]*                 yylval.id = malloc(yyleng); strcpy(yylval.id, yytext); return IDENT;
"Vrai"                                yylval.bool=1; return BOOLEEN;
"Faux"                                yylval.bool=0; return BOOLEEN;
"<="                                  return EST_INFERIEUR_OU_EGAL_A;
">="                                  return EST_SUPERIEUR_OU_EGAL_A;
"==="                                 return EST_EGAL_A;
"!=="                                 return EST_DIFFERENT_DE;
"&&"                                  return ET;
"||"                                  return OU;
"**"                                  return PUISSANCE;
"Si"                                  return SI;
"Sinon"                               return SINON;
"TantQue"                             return TANT_QUE;
"Faire"                               return FAIRE;
"Pour"                                return POUR;
"Ecrire"                              return ECRIRE;
"Typeof"                              return TYPEOF;
"Var"                                 return VAR;
"Fonction"                            return FONCTION;
"Break"                               return BREAK;
"Retourner"                           return RETOURNER;
[ \n]                                 return 0; /* ignore les fins de ligne */
.                                     return (int) yytext[0];
%%

#include <stdio.h>
#include <stdlib.h>

int commenteof()
{
  fprintf (stderr, "unexpected EOF inside comment");
  exit (1);
}

int yywrap()
{
  return (1);
}
