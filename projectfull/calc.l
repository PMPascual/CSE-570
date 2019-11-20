%{
#include <stdio.h>
#include "calc.tab.h"

int c;
extern YYSTYPE yylval;
%}

%%

" ";

"exit" {return exit_command;}

[a-zA-Z] {
  c = yytext[0];
  yylval.a = c - 'a';
  return(LETTER);
}

[0-9] {
  c = yytext[0];
  yylval.a = c - '0';
  return(DIGIT);
}

[^a-z0-9\b] {
  c = yytext[0];
  return(c);
}

