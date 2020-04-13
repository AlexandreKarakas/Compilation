/*fichier calc.c */


#include <stdio.h>
#include <stdlib.h>
#include "AST.c"

int main(void)
{
  struct ExpressionA* ast = (struct  ExpressionA*)malloc( sizeof( struct  ExpressionA ) );

  yyparse(ast);

  fprintf(stderr, "symbol principal: %c \n", ast->sym );
}
