{
  open Parser        (* The type token is defined in parser.mli *)
  exception InvalidChar of char
} 

let digit = ['0'-'9']
let id = ['a'-'z'] ['a'-'z' '0'-'9']*

rule token = parse
  | digit+ as inum { INT(int_of_string inum) }
  | "(" { LPAREN }
  | ")" { RPAREN }
  | "fun" { FUN }
  | "->" { ARROW }
  | "=" { EQ }
  | "let" { LET }
  | "if" { IF } 
  | "then" { THEN }
  | "else" { ELSE }
  | "rec" { REC }
  | "in" { IN }
  | "true" { BOOL(true) }
  | "false" { BOOL(false) }
  | "and" { AND }
  | "or" { OR }
  | "not" { NOT }
  | id as text { IDENT(text) }
  | '+' { PLUS }
  | '-' { MINUS }
  | '*' { TIMES }
  | '/' { DIV }
  | ',' { COMMA }
  | "<=" { LTE }
  | [' ' '\t' '\n'] { token lexbuf } (* eat up whitespace *)
  | _ as c      { raise (InvalidChar c) }
  | eof		{ EOF }
