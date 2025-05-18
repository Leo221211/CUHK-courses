(* Saml AST type *)
type saml_ast =
    Int of int
  | Bool of bool
  | Var of string
  | Let of (saml_ast * saml_ast) list * saml_ast
  | LetRec of saml_ast * saml_ast * saml_ast
  | Ite of saml_ast * saml_ast * saml_ast
  | Fun of saml_ast list * saml_ast
  | App of saml_ast * saml_ast
  | Lte of saml_ast * saml_ast
  | Plus of saml_ast * saml_ast
  | Minus of saml_ast * saml_ast
  | Times of saml_ast * saml_ast
  | Divides of saml_ast * saml_ast
  | And of saml_ast * saml_ast 
  | Or of saml_ast * saml_ast 
  | Not of saml_ast

(* SamlCore AST type *)
type core_ast =
    CInt of int
  | CBool of bool
  | CVar of string
  | CIte of core_ast * core_ast * core_ast
  | CLetRec of core_ast * core_ast * core_ast
  | CFun of core_ast * core_ast
  | CApp of core_ast * core_ast
  | CLte of core_ast * core_ast
  | CPlus of core_ast * core_ast
  | CMinus of core_ast * core_ast
  | CTimes of core_ast * core_ast
  | CDivides of core_ast * core_ast

(* Exercise 1 (30 pts): Define desugar: saml_ast -> core_ast below *)

let rec desugar (e : saml_ast) : core_ast =
  match e with
  | Int i -> CInt i
  | Bool b -> CBool b
  | Var x -> CVar x
  | Let (binds, body) ->
      let rec desugar_binds = function
        | [] -> desugar body
        | (x, e1)::rest ->
            CApp (CFun (desugar x, desugar_binds rest), desugar e1)
      in desugar_binds binds
  | LetRec (x, e1, e2) -> CLetRec (desugar x, desugar e1, desugar e2)
  | Ite (e1, e2, e3) -> CIte (desugar e1, desugar e2, desugar e3)
  | Fun (args, body) ->
      List.fold_right (fun arg acc -> CFun (desugar arg, acc)) args (desugar body)
  | App (e1, e2) -> CApp (desugar e1, desugar e2)
  | Lte (e1, e2) -> CLte (desugar e1, desugar e2)
  | Plus (e1, e2) -> CPlus (desugar e1, desugar e2)
  | Minus (e1, e2) -> CMinus (desugar e1, desugar e2)
  | Times (e1, e2) -> CTimes (desugar e1, desugar e2)
  | Divides (e1, e2) -> CDivides (desugar e1, desugar e2)
  | And (e1, e2) -> CIte (desugar e1, desugar e2, CBool false)
  | Or (e1, e2) -> CIte (desugar e1, CBool true, desugar e2)
  | Not e1 -> CIte (desugar e1, CBool false, CBool true)

