open Nn
open Printf

let test_result prop = if prop then "Passed!" else "Failed"

let run_test (prop, info, result) =
  printf "%-7s (%-14s): %s\n" prop info (test_result @@ result)

let prop0 = ( "Prop 0", "repeat",
              try repeat 3 4 = [ 4; 4; 4 ]
              with _ -> false )
let prop1 = ( "Prop 1", "repeat",
              try repeat 0 [] = []
              with _ -> false )
let prop2 = ( "Prop 2", "repeat",
              try repeat 5 [] = [ []; []; []; []; [] ]
              with _ -> false )

let prop3 =
  ( "Prop 3",
    "list_apply",
    try
      list_apply [ (fun x -> x + 1); (fun x -> x + 2) ] [ 1; 1 ] = [ 2; 3 ]
    with _ -> false )

let prop4 =
  ( "Prop 4", "weighted_sum",
    try weighted_sum 0. [ (1., 0.); (1., 1.) ] = 1.
    with _ -> false )

let prop5 = ( "Prop 5", "weighted_sum",
             try weighted_sum 20. [] = 20.
             with _ -> false )

let prop6 =
  ( "Prop 6", "weighted_sum",
    try weighted_sum 10. [ (5., 2.); (3., 3.) ] = 29.
    with _ -> false )

let prop7 = ( "Prop 7", "mk_node",
               try (mk_node (fun x -> x) 2.) [ (2., 5.) ] = 12.
               with _ -> false )

let prop8 =
  ( "Prop 8", "mk_node",
   try
     (mk_node (fun x -> x +. 1.) 2.) [ (2., 5.) ] = 13.
   with _ -> false )

let prop9 = ( "Prop 9", "mk_layer",
              try
                mk_layer [] [] [] [ 1. ] = []
              with _ -> false )
let prop10 = ( "Prop 10", "example",
                try
                  List.length (example [ 1.; 2.; 3. ]) = 2
                with _ -> false )

let prop11 =
  ( "Prop 11",
    "node_from_arch",
    try
      (node_from_arch (Node Sigmoid) 2.) [ (2., 3.) ]
      = (mk_node sigmoid 2.) [ (2., 3.) ]
    with _ -> false )

let empty_arch = Composition []

let prop12 =
  ("Prop 12", "nn_from_arch",
    try
      nn_from_arch empty_arch [] [ 1.; 2. ] = [ 1.; 2. ]
    with _ -> false )

let example_arch_2 =
  let layer1 =
    Custom
      [ (Node ReLU, [ 1 ]); (Node ReLU, [ 0; 1; 2 ]); (Node ReLU, [ 0; 2 ]) ]
  in
  let layer2 = Uniform (2, Node ReLU, [ 0; 1; 2 ]) in
  let layer3 = Uniform (2, Node ReLU, [ 0; 1 ]) in
  Composition [ layer1; Composition [ layer2; layer3 ] ]

let layer_1_params =
  {
    biases = [ 1.; 2.; 3. ];
    weights = [ [ 1. ]; [ 0.3; 0.2; 0.3 ]; [ 0.5; 0.5 ] ];
  }

let layer_2_params =
  { biases = [ 1.; 2. ]; weights = [ [ 0.5; 0.2; 0.3 ]; [ 0.4; 0.6; 0. ] ] }

let layer_3_params =
  { biases = [ 1.; 2. ]; weights = [ [ 0.5; 0.5 ]; [ 0.4; 0.6 ] ] }

let prop13 =
  ( "Prop 13",
    "nn_from_arch",
    try
      List.length
        (nn_from_arch example_arch_2
           [ layer_1_params; layer_2_params; layer_3_params ]
        @@ [ 1.; 2.; 3. ])
      = 2 
    with
    _ -> false
  )

let prop14 =
  ("Prop 14", "example", 
    try example [ 1.; 2.; 3. ] = example_v2 [ 1.; 2.; 3. ]
    with _ -> false )

let prop15 =
  ("Prop 15", "example",
   try example [ 1.; 2.2; 0.3 ] = example_v2 [ 1.; 2.2; 0.3 ]
   with _ -> false )

open Circle

let prop16 =
  ( "Prop 16",
    "nn_from_arch",
    try
      nn_from_arch example_arch circle_params [ 1.; 2.; 3. ] |> ignore;
      false
    with
    | InvalidParams _ -> true
    | _ -> false )

let prop17 =
  ( "Prop 17",
    "circle_nn",
    try
      circle_nn [ 1. ] |> ignore;
      false
    with _ -> true )

let empty_hidden_layer_arch =
  Composition
    [ Uniform (1, Node ReLU, [ 0 ]); Custom []; Uniform (2, Node ReLU, []) ]

let empty_hidden_layer_params =
  [
    { biases = [ 0. ]; weights = [ [ 1. ] ] };
    { biases = []; weights = [] };
    { biases = [ 0.; 0. ]; weights = [ []; [] ] };
  ]

let prop18 =
  ("Prop 18", "empty_hidden",
    try
      let empty_hidden_layer_nn =
        nn_from_arch empty_hidden_layer_arch empty_hidden_layer_params in
      empty_hidden_layer_nn [ 20. ] = [ 0.; 0. ]
    with _ -> false )

let empty_hidden_layer_params_v2 =
  [
    { biases = [ 0. ]; weights = [ [ 1. ] ] };
    { biases = []; weights = [] };
    { biases = [ 10.; 5. ]; weights = [ []; [] ] };
  ]

let prop19 =
  ( "Prop 19",
    "empty_hidden",
    try
      let empty_hidden_layer_nn =
        nn_from_arch empty_hidden_layer_arch empty_hidden_layer_params in
      empty_hidden_layer_nn [ 20. ] = empty_hidden_layer_nn [ 32. ]
    with _ -> false )

let empty_output_layer_arch =
  Composition [ Uniform (2, Node ReLU, [ 0 ]); Custom [] ]

let empty_output_layer_params =
  [
    { biases = [ 0.; 0.2 ]; weights = [ [ 1. ]; [ 1. ] ] };
    { biases = []; weights = [] };
  ]

let prop20 =
  ( "Prop 20",
    "empty_output",
    try
      nn_from_arch empty_output_layer_arch empty_output_layer_params [ 1.; 3. ]
       == []
    with _ -> false )

let () =
  List.iter run_test
    [
      prop1;
      prop2;
      prop3;
      prop4;
      prop5;
      prop6;
      prop7;
      prop8;
      prop9;
      prop10;
      prop11;
      prop12;
      prop13;
      prop14;
      prop15;
      prop16;
      prop17;
      prop18;
      prop19;
      prop20;
    ]

