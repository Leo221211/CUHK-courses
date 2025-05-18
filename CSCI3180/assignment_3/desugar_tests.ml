open Desugar;;
open Printf;;

let int_3 = Int 3
let core_int_3 = CInt 3

let var_v = Var "v"
let core_var_v = CVar "v"

let square = Times(var_v, var_v)
let core_square = CTimes(core_var_v, core_var_v)

let square_fun = Fun([var_v], square)
let core_square_fun = CFun(core_var_v, core_square)

let square_fun_2 = Fun([var_v; var_v], square)
let core_square_fun_2 = CFun(core_var_v, CFun(core_var_v, core_square))

let square_3 = App(App(Fun([var_v; var_v], square), int_3), int_3)
let core_square_3 =
  CApp(CApp(CFun(core_var_v,
          CFun(core_var_v, core_square)), core_int_3),
      core_int_3)

let quad_3 =
  Let ([Var "f", square_fun; Var "g", square_fun_2],
       App(App(Var "f", App(App(Var "g", int_3), int_3)), int_3))
let core_quad_3 =
  CApp (CFun (CVar "f",
    CApp (CFun (CVar "g",
      CApp(CApp(CVar "f", CApp(CApp(CVar "g", core_int_3), core_int_3)),
           core_int_3)),
      core_square_fun_2)),
    core_square_fun)

let test_result result = if result then "Passed!" else "Failed"

let run_test (info, result) =
  printf "%-20s: %s\n" info (test_result result)

let () =
  List.iter run_test
    [
      ("desugar integer",
       (desugar int_3) = core_int_3);
      ("desugar variable",
        (desugar var_v) = core_var_v);
      ("desugar binary op",
        (desugar square) = core_square);
      ("desugar function",
        (desugar square_fun) = core_square_fun);
      ("desugar function (2)",
       (desugar square_fun_2) = core_square_fun_2);
      ("desugar let",
       (desugar quad_3) = core_quad_3)
    ] 
