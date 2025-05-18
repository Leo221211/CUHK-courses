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

(** PART 1: Warm-up **)

(* Exercise 1 - 4 pts *)
let rec repeat n v = 
  if n <= 0 then [] 
  else v :: repeat (n - 1) v


(* Exercise 2 - 6 pts *)
let list_apply fs xs = 
  List.map2 (fun f x -> f x) fs xs

(** PART 2: Representing Neural Networks **)

(* nn type *)
type nn = float list -> float list

(* node type *)
(* a function that takes in (weight, value), using its own bias and activation fn, outputs the node output*)
type node = (float * float) list -> float

(* Exercise 3 - 10 pts *)
let weighted_sum bias weights_and_vals =
  List.fold_left (fun acc (w, x) -> acc +. (w *. x)) bias weights_and_vals

(* Exercise 4 - 10 pts *)
let mk_node (activation_fn : float -> float) (bias : float) : (float * float) list -> float = function
  | weights_and_vals -> 
    activation_fn (weighted_sum bias weights_and_vals)

(* connectivity type *)
type connectivity = int list

(* Exercise 5 - 6 pts *)
let example_connectivity = [ [ 0; 1 ]; [ 1 ]; [ 2 ]; [1; 2] ]

let example_weights = [ [ 0.7; 0.3 ]; [ 1.0 ]; [ 1.0 ]; [0.84; 0.16] ]

(* Exercise 6 - 2 pts *)
type layer = float list -> float list

(* Exercise 7 - 20 pts *)
(*
Input params
  nodes: a list of nodes for a layer: 
    each element is of type node
  c: a list of connectivity. 
    list of per node input index: [[idx_of_inp1_of_node1, idx_of_inp2_of_node1], [idx_of_inp1_of_node2, idx_of_inp2_of_node2], ...]
    eg: [ [ 0; 1 ]; [ 1 ]; [ 2 ]; [1; 2] ]: 
    0th node of this layer connects with 0th and 1st node of the last layer
  weights: a list of (weight: float list)
    eg: [ [ 0.7; 0.3 ]; [ 1.0 ]; [ 1.0 ]; [0.84; 0.16] ]:
    corresponds to the connectivity list

Output:
  Is of type layer. which is a funcition that takes a float list as input and output another float list

Idea:
  Get a list of per node input:per_node_inp_val(per_node_inputs) [[inp1_of_node1, inp2_of_node1], [inp1_of_node2, inp2_of_node2], ...]
    define a fn:per_node_give_inp_idx_ret_inp_val that takes inp_idx of a node, return the inp_val correspondes to that idx
    List.map per_node_give_inp_idx_ret_inp_val c

    Zip the weights list and value to get a list of 2-tupples: wei_val_tupple_list
    [[(w_inp1_of_node1, inp1_of_node1), (w_inp2_of_node1, inp2_of_node1)], [(w_inp1_of_node1, inp1_of_node1), (w_inp2_of_node1, inp2_of_node1)], ...]
    List.map2 (fun a, b -> (a, b)) weights per_node_inputs

  Apply list of per node to the node (the node cal function) and get the output
    list_apply nodes wei_val_tupple_list
*)
let mk_layer (nodes : node list) (c : connectivity list) (weights : float list list) : layer = 
  function | (inputs : float list) ->

    (*nth_input is a function that input an integer n, return the nth element of inputs*)
    let nth_input = List.nth inputs in

      (*give the indices as a list, return a sublist of the elements in input whose indices = input*)
      (*like inputs[input_idx] where input_idx is the input*)
      let per_node_give_inp_idx_ret_inp_val = fun indices -> List.map nth_input indices in 

        (*per_node_inputs is a float list list, where ith element is the inputs for ith node, which is a list of float*)
        let per_node_inputs : float list list = List.map per_node_give_inp_idx_ret_inp_val c  in 

          let wei_val_tupple_list = List.map2 (fun weights inputs -> List.map2 (fun w v -> (w, v)) weights inputs) weights per_node_inputs in

            (*defined before*)
            list_apply nodes wei_val_tupple_list
  
(* some activation functions *)
let relu x = if x > 0. then x else 0.
let sigmoid x = Float.div 1. (1. +. Float.exp x)

(* example nn *)
let example : nn = function
  | input ->
      let layer1 =
        mk_layer
          (repeat 3 (mk_node relu 0.))
          [ [ 1 ]; [ 0; 1; 2 ]; [ 0; 2 ] ]
          [ [ 1. ]; [ 0.3; 0.3; 0.4 ]; [ 0.2; 0.8 ] ]
      in
      let layer2 =
        mk_layer
          (repeat 2 (mk_node relu 0.2))
          [ [ 0; 1; 2 ]; [ 0; 1; 2 ] ]
          [ [ 0.3; 0.4; 0.3 ]; [ 0.4; 0.3; 0.3 ] ]
      in
      (*pipe operator. used to pass the result of one expression as the input to another function.*)
      layer1 input |> layer2

(** PART 3: Specification **)
(* nn architecture *)
type activation = ReLU | Sigmoid
type node_arch = Node of activation
type in_edge_indices = int list   (*connectivity*)

(* nn architectures as compositions of one or more neural networks *)
(*
Uniform(n, a, c) 
  describes a neural network with one (non-input) layer of n nodes with architecture a,
  where each node has connectivity c.
Custom(acs) 
  describes a neural network with one (non-input) layer of List.length(acs) nodes,
  where each (a, c) in acs specifies a node with architecture a and connectivity c.
Composition(nns) 
  describes a neural network formed by the composition of the neural networks nns, 
  where for nns = [ nn_1; nn_2; ...; nn_k ], nn_1 is applied first to the inputs of the neural network, 
  nn_2 to the output of nn_1, nn_3 to the output of nn_2, and so on.
  eg: Composition [ Uniform (1, Node ReLU, [ 0 ]); Custom []; Uniform (2, Node ReLU, []) ]
      Composition [ layer1; Composition [ layer2; layer3 ] ]    (*weird case*)
*)
type nn_arch =
  | Uniform of (int * node_arch * in_edge_indices)
  | Custom of (node_arch * in_edge_indices) list    (*in_edge_indices is the connectivity of that node*)
  | Composition of nn_arch list

(* example nn architecture *)
let example_arch =
  let layer1 =
    Custom
      [ (Node ReLU, [ 1 ]); (Node ReLU, [ 0; 1; 2 ]); (Node ReLU, [ 0; 2 ]) ]
  in
    let layer2 = Uniform (2, Node ReLU, [ 0; 1; 2 ]) in
      Composition [ layer1; layer2 ]

(* nn params *)
type layer_params = { weights : float list list; biases : float list }
type nn_params = layer_params list    
(*eg: [
        {weights: [[w1_of_node1, w2_of_node1], [w1_of_node2, w2_of_node2], ...]; 
        biases: [b1, b2, ...]};       # for layer 0 
        
        {weights: [[w1_of_node1, w2_of_node1], [w1_of_node2, w2_of_node2], ...]; 
        biases: [b1, b2, ...]};       # for layer 1
        
      ]
*)

(* Exercise 8 - 5 pts *)
(*give an activation and a bias, return a node (a function defined above)*)
let node_from_arch (Node activation) bias =
  let activation_fn = match activation with
    | ReLU -> relu
    | Sigmoid -> sigmoid
  in
    mk_node activation_fn bias

(* Exercise 9 - 25 pts *)
exception InvalidParams of nn_arch * nn_params

(*
type: nn_arch -> nn_params -> nn.
Input:
  arch: the architecture of an nn: the activation fn and connectivity of all nodes in nn (see type nn_arch)
  params: of type nn_params (see above): the weights and biases of all nodes in nn
  input: list of float as input

output: the output of the whole nn

Note:
  1. raise exception if not match
  1. if the arch is empty, is identity function

Idea:
  Recursively process the left most layer, then pass the output as the input to the recursive function. 
  Until empty arch as input, pass the input and return

Pseudo code:
```


let nn_from_arch arch params inputs =
  let wrapped_arch = wrap_arch arch in

    let rec rec_cal_output arch params inputs =
      # if wrapped_arch has no elements
      if arch = (Composition []):
        return inputs
 
      # next element is Uniform or Custom
      else:
          # calculate single layer output
          first_layer, rest_lyrs = 

          `nodes
          _list`: a list of nodes that will be used in function mk_layer()
            get a list of activations and biases from params and arch separately
            use node_from_arch() to make a list of nodes:`nodes_list` for each node by zip(activations, biases)
          `conns`: from the input of type Uniform or Custom, get a list of connectivity that will be used in mk_layer
          `weights`: get the weights list of that layer from param

          cal_layer() = mk_layer nodes_list conn weights

          return cal_layer(inputs)

      # if is non-empty composition layer:
        return rec_cal_output 
      else:
        return nn_from_arch arch[1:] params[1:] inputs[1:]
```

*)

(*
help to split the param to first::rest
split the parameters according to the arch element.
give the [corresponding param], [rest params]
*)
let rec get_param_of_first_arch arch params =
  match arch with
  | Composition [] -> [], params

  | Uniform _ | Custom _ -> 
      (match params with
      | fst::rest -> [fst], rest
      | [] -> raise (InvalidParams (arch, params)))

  | Composition (fst_arch::rest_arch) ->    (*Composition in Composition*)
      let fst_param, rest_params = get_param_of_first_arch fst_arch params in

        let snd_param, non_fst_2_param = get_param_of_first_arch (Composition rest_arch) rest_params in

          fst_param @ snd_param, non_fst_2_param

let nn_from_arch arch params inputs =
  let rec rec_cal_output arch params inputs =
    match arch, params with
    (*if has no layers*)
    | Composition [], [] -> inputs   

    (*if is non composition*)
    | Uniform (node_num, node_arch, conn), [lyr_param] -> 
      if List.length lyr_param.biases = node_num then 

        (*get a list of nodes for mk_layer*)
        let lyr_nodes = List.map2 node_from_arch (repeat node_num node_arch) lyr_param.biases in

            let lyr_fn = mk_layer lyr_nodes (repeat node_num conn) lyr_param.weights in

              lyr_fn inputs  
      else
        raise (InvalidParams (arch, params))

    | Custom arch_conn, [lyr_param]  ->

      let node_num = List.length arch_conn in
          
        if List.length lyr_param.biases = node_num then

          let lyr_arch = List.map fst arch_conn in

            let lyr_conn = List.map snd arch_conn in

              (*get a list of nodes for mk_layer*)
              let lyr_nodes = List.map2 node_from_arch lyr_arch lyr_param.biases in

                let lyr_fn = mk_layer lyr_nodes lyr_conn lyr_param.weights in

                  lyr_fn inputs  
        else
          raise (InvalidParams (arch, params))

    (*if is not empyt composition, decomposition*)
    | Composition (fst::rest), params ->
        let fst_param, rest_params = get_param_of_first_arch fst params in

          let fst_out = rec_cal_output fst fst_param inputs in

            rec_cal_output (Composition rest) rest_params fst_out
        
    (*other cases*)
    | _ -> raise (InvalidParams (arch, params))
  in
    rec_cal_output arch params inputs
  
(* apply nn architecture to weights *)
let example_v2 : nn =
  let layer1_params =
    {
      biases = [ 0.; 0.; 0. ];
      weights = [ [ 1. ]; [ 0.3; 0.3; 0.4 ]; [ 0.2; 0.8 ] ];
    }
  in
  let layer2_params =
    {
      biases = [ 0.2; 0.2 ];
      weights = [ [ 0.3; 0.4; 0.3 ]; [ 0.4; 0.3; 0.3 ] ];
    }
  in
  nn_from_arch example_arch [ layer1_params; layer2_params ]

(* Exercise 10 - 12 pts *)
let circle_arch =
  let layer1 = Uniform (5, Node ReLU, [0; 1]) in
  let layer2 = Uniform (5, Node ReLU, [0; 1; 2; 3; 4]) in
  let layer3 = Uniform (5, Node ReLU, [0; 1; 2; 3; 4]) in
  let output_layer = Uniform (1, Node Sigmoid, [0; 1; 2; 3; 4]) in
  Composition [layer1; layer2; layer3; output_layer]



  
  