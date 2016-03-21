%{


/* This interpreter evaluates arithmetic expressions and assigns
   them to the specified variable names. The grammar is:

   pgm -> stmtlist
   stmtlist -> stmt | stmtlist ; stmt
   stmt -> id = exp |  print id
   exp -> exp + mulexp | exp - mulexp 
   mulexp -> mulexp * primexp | mulexp / primexp
   primexp ->  ( exp ) | ( exp ) | - primexp | id | number | input
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "imp.h"



using namespace std;

 extern FILE *yyin;

// the root of the abstract syntax tree
 statement *root;

// for keeping track of line numbers in the program we are parsing
  int line_num = 1;

// function prototypes, we need the yylex return prototype so C++ won't complain
int yylex();
void yyerror(const char * s);

%}

%start program

%union {
  float num;
  float input;
  char *id;
  bool true1;
  bool false1;

  exp_node *exp_node_ptr;
  bexp_node *bexp_node_ptr;
  statement *st;
}

%error-verbose

%token <num> NUMBER
%token <id> ID
%token <input> INPUT
%token <true1> TRUE
%token <false1> FALSE
%token SEMICOLON  EQUALS PRINT  PLUS MINUS TIMES DIVIDE  LPAREN RPAREN LBRACE RBRACE B_EQUALS
%token AND OR NOT EQUALS_EQUALS GREATER_OR_EQUALS IF THEN ELSE WHILE DO
%type <exp_node_ptr> exp
%type <exp_node_ptr> mulexp
%type <exp_node_ptr> primexp
%type <bexp_node_ptr> bexp
%type <bexp_node_ptr> bmulexp
%type <bexp_node_ptr> btermexp
%type <bexp_node_ptr> bprimitive
%type <st> stmtlist
%type <st> stmt
%type <st> program

%%

program :
    stmtlist { root = $$; }
;

stmtlist :
    stmtlist SEMICOLON stmt { $$ = new sequence_stmt($1,$3); }

    | stmtlist SEMICOLON error { $$ = $1; yyclearin; }

    | stmt { $$ = $1;   }
;

stmt:
    ID EQUALS exp { $$ = new assignment_stmt($1, $3); }

    | PRINT exp { $$ = new print_stmt($2); }

    | ID B_EQUALS bexp { $$ = new boolean_assignment_stmt($1, $3); }

    | PRINT bexp { $$ = new boolean_print_stmt($2); }

    | { $$ = new skip_stmt(); }

    | LBRACE stmtlist RBRACE { $$=$2; }

    | IF bexp THEN stmtlist ELSE stmtlist {$$ = new if_else_stmt($2, $4, $6);}

    | WHILE bexp DO stmtlist {$$ = new while_do_stmt($2, $4);}
;


exp:
    exp PLUS mulexp { $$ = new plus_node($1, $3); }

    | exp MINUS mulexp { $$ = new minus_node($1, $3); }

    | mulexp {  $$ = $1; }
;



mulexp:
    mulexp TIMES primexp { $$ = new times_node($1, $3); }

    | mulexp DIVIDE primexp { $$ = new divide_node($1, $3); }

    | primexp { $$=$1;  }
;



primexp:
    MINUS primexp %prec UMINUS { $$ = new unary_minus_node($2); }

    | LPAREN exp RPAREN  {  $$ = $2; }

    | NUMBER { $$ = new number_node($1); }

    | ID { $$ = new id_node($1); }

    | INPUT { $$ = new input_node($1); }
;


bexp:
	bexp OR bmulexp { $$ = new or_node($1, $3); }

	| bmulexp { $$ = $1; }
;


bmulexp:
	bmulexp AND btermexp { $$ = new and_node ($1, $3); }

	| btermexp { $$ = $1; }
;


btermexp:
	NOT btermexp { $$ = new not_node($2); }

	| bprimitive { $$ = $1; }
;


bprimitive:
	LPAREN bexp RPAREN { $$ = $2; }

	| bexp EQUALS_EQUALS bexp { $$ = new equals_equals_node($1, $3); }

	| ID { $$ = new boolean_id_node($1); }

	| TRUE    { $$ = new true_node();   }

    | FALSE   { $$ = new false_node();  }
;


%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

  //  yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print();

  cout << "---------- exeuction of input program------------" << endl << endl;
  

  root->evaluate();
}

void yyerror(const char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

