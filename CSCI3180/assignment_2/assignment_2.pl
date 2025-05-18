% CSCI3180 Principles of Programming Languages
%
% --- Declaration ---
% For all submitted files, including the source code files and the written  
% report, for this assignment:
%
% I declare that the assignment here submitted is original except for source
% materials explicitly acknowledged. I also acknowledge that I am aware of
% University policy and regulations on honesty in academic work, and of the
% disciplinary guidelines and procedures applicable to breaches of such policy
% and regulations, as contained in the website
% http://www.cuhk.edu.hk/policy/academichonesty/
%
% Name: Muquan YU
% Student ID: 1155191596
% Email Address: mqyu@link.cuhk.edu.hk
%
% Source material acknowledgements (if any):
% 
% Students whom I have discussed with (if any):


% PART 1: Natural Numbers (50 pts)

% Inductive definition of the natural numbers
nat(z). % base case: zero
nat(s(N)) :- nat(N). % inductive case

% Exercise 1 (10 pts)
% Define the predicate to_nat/2 below:

to_nat(0, z).
to_nat(N, s(T)) :- to_nat(M, T), N is M + 1.

% Exercise 2 (5 pts)
% Define the predicate nat_plus/3 before:

nat_plus(z, Y, Y).
nat_plus(s(X), Y, s(Z)) :- nat_plus(X, Y, Z).

% Exercise 3 (5 pts)
% Write a query that uses nat_plus and to_nat to discover the difference X of 40 and 3. The result of the query should discover X such that X = 37.
%
% ?- to_nat(40, PL40), to_nat(3, PL3), nat_plus(X_nat, PL3, PL40), to_nat(X, X_nat).

% Exercise 4 (10 pts)
% Define a predicate nat_mul/3 below:

nat_mul(z, _, z).
nat_mul(s(X), Y, Z) :-
    nat_mul(X, Y, ZMINUS),
    nat_plus(Y, ZMINUS, Z).

% Exercise 5 (20 pts)
% Define predicate eval/2 below:

eval(A, A) :- nat(A).
eval((plus, B, C), D) :- eval(B, E), eval(C, F), nat_plus(E, F, D).
eval((minus, B, C), D) :- eval(B, E), eval(C, F), nat_plus(D, F, E).
eval((times, B, C), D) :- eval(B, E), eval(C, F), nat_mul(E, F, D).

% PART 2: Nested Queue Processing (50 pts)

% Set of names
name(alice).
name(bob).
name(charlie).
name(eve).

% Exercise 6 (5 pts)
% Define the predicate queue/1 below:

queue([]).
queue([H|T]) :-
    ( name(H) -> true ; queue(H) ),
    queue(T).

% Exercise 7 (10 pts)
% Define the predicate step/4 below:

% ex 7
% step([[ ]|T], P, T, P).  
% step([H|T], P, T, P2) :-  
%     name(H),
%     append(P, [H], P2).
% step([H|T], P, [H1|T], P2) :-  
%     queue(H),
%     step(H, P, H1, P2).

step([[ ]|T], P, T, P) :- !.  
step([H|T], P, T, P2) :-  
    name(H),
    append(P, [H], P2), !.
step([H|T], P, [H1|T], P2) :-  
    queue(H),
    step(H, P, H1, P2), !.

% Exercise 8 (5 pts)
% Add cuts to the predicate step/4 above.

% Exercise 9 (5 pts)
% Define the predicate step_rtc/4 below:

step_rtc(Q, P, Q, P).  
step_rtc(Q, P, Q2, P2) :-  
    step(Q, P, Q1, P1),
    step_rtc(Q1, P1, Q2, P2).

% Exercise 10 (5 pts)
% Define the predicate big_step/4 below:

big_step(Q, P, [], PFINAL) :-
    step_rtc(Q, P, [], PFINAL).

% Exercise 11 (20 pts)
% Define the predicate step_n/4:

step_n(Q, P, Q_new, P_new) :-
    select(E, Q, Q_rest),
    (
      ( E == [] ->
          Q_new = Q_rest,
          P_new = P
      ;
        name(E) ->
          Q_new = Q_rest,
          append(P, [E], P_new)
      ;
        queue(E) ->
          step_n(E, P, E_new, P_new),
          Q_new = [E_new | Q_rest]
      )
    ).
    % !.


%%%%