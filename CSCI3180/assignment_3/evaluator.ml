open Desugar;;
open Interpret;;

let ast_from_string str =
  Parser.main Lexer.token (Lexing.from_string str)

let rec string_of_expr = function
  | CInt z -> string_of_int z
  | CBool b -> string_of_bool b
  | CVar x -> x
  | CLetRec(x, e1, e2) -> "let " ^ string_of_expr x ^
                          " = " ^ string_of_expr e1 ^
                          " in " ^ string_of_expr e2
  | CIte(e1, e2, e3) -> "if " ^ string_of_expr e1 ^
                        " then "  ^ string_of_expr e2 ^
                        " else " ^ string_of_expr e3
  | CFun(x, body) -> "fun " ^ string_of_expr x ^ " -> " ^ string_of_expr body
  | CApp(CFun(x,body), e2) ->
      "((" ^ (string_of_expr (CFun(x, body))) ^ ") " ^ string_of_expr e2 ^ ")"
  | CApp(e1, e2) -> "(" ^ string_of_expr e1 ^ " " ^ string_of_expr e2 ^ ")"
  | CLte(e1, e2) -> "(" ^ string_of_expr e1 ^ " <= " ^ string_of_expr e2 ^ ")"
  | CPlus(e1, e2) -> "(" ^ string_of_expr e1 ^ " + " ^ string_of_expr e2 ^ ")"
  | CMinus(e1, e2) -> "(" ^ string_of_expr e1 ^ " - " ^ string_of_expr e2 ^ ")"
  | CTimes(e1, e2) -> "(" ^ string_of_expr e1 ^ " * " ^ string_of_expr e2 ^ ")"
  | CDivides(e1, e2) -> "(" ^ string_of_expr e1 ^ " / " ^ string_of_expr e2 ^ ")"

let rec string_of_value = function
  | VInt z -> string_of_int z
  | VBool b -> string_of_bool b
  | Closure (x, body, _) ->
      "(Closure: " ^ string_of_expr (CFun(CVar x, body)) ^ ")"

let interpret str =
  let full_ast = ast_from_string str in
  let core_ast = desugar full_ast in
  let result = eval [] core_ast in
  print_endline (string_of_value result)

let rec input str =
  let s = String.trim(str) in
  let len = String.length s in
  let finished =
    if len >= 2
    then (String.sub s (len - 2) 2) = ";;"
    else false
  in
  if finished
  then interpret (String.sub s 0 (len - 2))
  else match read_line() with
         "exit" -> raise Exit
         | s' -> input (s ^ " " ^ s')

let _ =
  (* Check if the correct number of arguments is provided *)
  if Array.length Sys.argv <> 2 then
    Printf.eprintf "Usage: %s <filename>\n" Sys.argv.(0)
  else
    let filename = Sys.argv.(1) in
    try
      let chan = open_in filename in
      let prog = really_input_string chan (in_channel_length chan) in
      close_in chan;
      interpret prog
    with
    | Stuck -> Printf.printf "Stuck\n"
    | Sys_error err -> Printf.eprintf "Error: %s\n" err
