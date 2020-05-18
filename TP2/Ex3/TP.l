/* fichier calc.l */

%{
/* fichier dans lequel est defini la macro constante NOMBRE */
#include "TP.tab.h"
#include <string.h>
%}

%%
[0-9]+                      yylval.num=atoi(yytext); return NOMBRE;
([0-9]*[.])?[0-9]+          yylval.num=atof(yytext); return NOMBRE;
[a-z][a-z,A-Z,0-9,_,'-']*   yylval.id = malloc(yyleng); strcpy(yylval.id, yytext); return IDENT;
"Vrai"                      yylval.num=1; return BOOLEEN;
"Faux"                      yylval.num=0; return BOOLEEN;
"<="                        return EST_INFERIEUR_OU_EGAL_A;
">="                        return EST_SUPERIEUR_OU_EGAL_A;
"==="                       return EST_EGAL_A;
"!=="                       return EST_DIFFERENT_DE;
"&&"                        return ET;
"||"                        return OU;
"**"                        return PUISSANCE;
"Si"                        return SI;
"Sinon"                     return SINON;
"TantQue"                   return TANT_QUE;
"Faire"                     return FAIRE;
"Pour"                      return POUR;
"Ecrire"                    return ECRIRE;
[ \n]                       return 0; /* ignore les fins de ligne */
[ \t]+                      return 0; /* ignore les blancs et tabulations */
.                           return (int) yytext[0];
"//"                        return COMMENTAIRE_UNILIGNE;
"/*"                        return DEB_COMMENTAIRE_MULTILIGNE;
"*/"                        return FIN_COMMENTAIRE_MULTILIGNE;
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
