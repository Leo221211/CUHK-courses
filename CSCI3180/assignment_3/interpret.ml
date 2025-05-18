(*
 * CSCI3180 Principles of Programming Languages
 *
 * --- Declaration ---
 * For all submitted files, including the source code files and the written  
 * report, for this assignment:
 *
 * I declare that the assignment here submitted is original except for source
 * materials explicitly acknowledged. I also acknowledge that I am aware of
 * University policy and regulations on honesty in academic work, and of the
 * disciplinary guidelines and procedures applicable to breaches of such policy
 * and regulations, as contained in the website
 * http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Name: Muquan YU
 * Student ID: 1155191596
 * Email Address: mqyu@link.cuhk.edu.hk
 *
 * Source material acknowledgements (if any):
 * 
 * Students whom I have discussed with (if any):
 *)

(*by doing eval env body, where body is an expression and env is a list of name mapping to values, try to replace the names in body by value and finally get a final value*)

open Desugar;;

type value =
    VInt of int
  | VBool of bool
  | Closure of string * core_ast * env  (*variable name, func body expression, environment*)

(* Environment: Maps variable names to values *)
and env = (string * value) list

exception Stuck;;

let rec eval (environment : env) (expr : core_ast) : value =
  match expr with
  | CInt n -> VInt n
  | CBool b -> VBool b
  | CVar x -> (
      match List.assoc_opt x environment with
      | Some v -> v
      | None -> raise Stuck)
  | CPlus (e1, e2) -> (
      match (eval environment e1, eval environment e2) with
      | (VInt v1, VInt v2) -> VInt (v1 + v2)
      | _ -> raise Stuck)
  | CMinus (e1, e2) -> (
      match (eval environment e1, eval environment e2) with
      | (VInt v1, VInt v2) -> VInt (v1 - v2)
      | _ -> raise Stuck)
  | CTimes (e1, e2) -> (
      match (eval environment e1, eval environment e2) with
      | (VInt v1, VInt v2) -> VInt (v1 * v2)
      | _ -> raise Stuck)
  | CDivides (e1, e2) -> (
      match (eval environment e1, eval environment e2) with
      | (VInt v1, VInt v2) when v2 <> 0 -> VInt (v1 / v2)
      | _ -> raise Stuck)
  | CLte (e1, e2) -> (
      match (eval environment e1, eval environment e2) with
      | (VInt v1, VInt v2) -> VBool (v1 <= v2)
      | _ -> raise Stuck)
  | CIte (cond, e1, e2) -> (
      match eval environment cond with
      | VBool true -> eval environment e1
      | VBool false -> eval environment e2
      | _ -> raise Stuck)
  | CFun (CVar x, body) -> Closure (x, body, environment)
  | CApp (e1, e2) -> (
      match eval environment e1 with
      | Closure (x, body, closure_env) ->   
          let arg_value = eval environment e2 in    
          eval ((x, arg_value) :: closure_env) body 
      | _ -> raise Stuck)
  | CLetRec (f, e1, e2) ->  (*name of the function, function parameter expression, function body expression*)
      (match f with
      | CVar f_name -> (
          match e1 with
          | CFun (CVar x, body) -> 
              let rec rec_env = (f_name, Closure (x, body, rec_env)) :: environment in
              eval rec_env e2
          | _ -> raise Stuck)
      | _ -> raise Stuck)
  | _ -> raise Stuck


(*
ocamlc -c desugar.ml; ocamlc -c parser.mli; ocamlc -c lexer.ml; ocamlc -c parser.ml; ocamlc -c interpret.ml; ocamlc -c evaluator.ml; ocamlc -o saml lexer.cmo parser.cmo desugar.cmo interpret.cmo evaluator.cmo

./saml programs/program_1.saml

python /home/leosunix/workspace/CUHK/csci3180/asg/assignment_3/compile_and_evaluate.py
*)