%{
  open Desugar
%}
%token <int> INT
%token <bool> BOOL
%token <string> IDENT
%token COMMA
%token LET REC IN
%token PLUS MINUS TIMES DIV
%token AND OR NOT
%token EQ
%token FUN ARROW
%token LTE
%token IF THEN ELSE
%token LPAREN RPAREN
%token EOF
%token APPLY
%nonassoc IN
%nonassoc ARROW
%nonassoc ELSE
%left AND OR
%left LTE
%left PLUS MINUS
%left TIMES DIV
%left APPLY
%nonassoc NOT
%start main             /* the entry point */
%type <Desugar.saml_ast> main
%%
main:
    expr EOF                { $1 }
;

expr:
  | LET binds IN expr           { Let ($2, $4) }
  | LET REC var EQ expr IN expr { LetRec ($3, $5, $7) }
  | FUN vars ARROW expr         { Fun ($2, $4) }
  | IF expr THEN expr ELSE expr { Ite ($2, $4, $6) }
  | expr PLUS expr              { Plus ($1, $3) }
  | expr MINUS expr             { Minus ($1, $3) }
  | expr TIMES expr             { Times ($1, $3) }
  | expr DIV expr               { Divides ($1, $3) }
  | expr LTE expr               { Lte ($1, $3) }
  | expr AND expr               { And ($1, $3) }
  | expr OR expr                { Or ($1, $3) }
  | expr subexpr  %prec APPLY   { App($1, $2) }
  | subexpr                     { $1 }

subexpr:
    id { $1 }
  | LPAREN expr RPAREN { $2 }
  | NOT expr           { Not ($2) }

id:
    INT                         { Int ($1) }
  | BOOL                        { Bool ($1) }
  | var { $1 }

binds:
    bind { [ $1 ] }
  | bind COMMA binds { $1 :: $3 }

bind:
  var EQ expr { ($1, $3) }

vars:
    var { [ $1 ] }
  | var vars { $1 :: $2 }

var:
  IDENT                     { Var ($1) }
;
