type token =
  | INT of (
# 4 "parser.mly"
        int
# 6 "parser.mli"
)
  | BOOL of (
# 5 "parser.mly"
        bool
# 11 "parser.mli"
)
  | IDENT of (
# 6 "parser.mly"
        string
# 16 "parser.mli"
)
  | COMMA
  | LET
  | REC
  | IN
  | PLUS
  | MINUS
  | TIMES
  | DIV
  | AND
  | OR
  | NOT
  | EQ
  | FUN
  | ARROW
  | LTE
  | IF
  | THEN
  | ELSE
  | LPAREN
  | RPAREN
  | EOF
  | APPLY

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Desugar.saml_ast
