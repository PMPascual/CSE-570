%{
#include <stdio.h>
#include <stdlib.h>
int regs[26];
int base;
int answer;
int yylex();
int yyerror(char *s);
int yywrap();
%}

%start list
%union {int a; char c;}
%type <a> expr number DIGIT
%type <c> LETTER
%token DIGIT LETTER
%token exit_command
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%

list: /* empty */
    | list stat '\n'
    | list error '\n' {yyerrok;};

stat: expr {printf("%d\n", $1);}
    | LETTER '=' expr {regs[$1] = $3;};

expr: '(' expr ')' {$$ = $2;}
    | expr '*' expr {$$ = $1 * $3; answer = $$;}
    | expr '/' expr {$$ = $1 / $3; answer = $$;}
    | expr '%' expr {$$ = $1 % $3; answer = $$;}
    | expr '+' expr {$$ = $1 + $3; answer = $$;}
    | expr '-' expr {$$ = $1 - $3; answer = $$;}
    | expr '&' expr {$$ = $1 & $3; answer = $$;}
    | expr '|' expr {$$ = $1 | $3; answer = $$;}
    | '`' expr %prec UMINUS {$$ = -$2;}
    | LETTER {$$ = regs[$1];}
    | number;
    | exit_command {exit(EXIT_SUCCESS);}
    | '*' expr {$$ = answer * $2;}
    | '/' expr {$$ = answer / $2;}
    | '%' expr {$$ = answer % $2;}
    | '+' expr {$$ = answer + $2;}
    | '-' expr {$$ = answer - $2;}
    | '&' expr {$$ = answer & $2;}
    | '|' expr {$$ = answer | $2;}

number: DIGIT {
          $$ = $1;
          base = ($1 == 0) ? 8 : 10;
        }
      | number DIGIT {
          $$ = base * $1 + $2;
        };

%%

int main() {
  return yyparse();
}

int yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
  return 1;
}

int yywrap() {
  return 1;
}

