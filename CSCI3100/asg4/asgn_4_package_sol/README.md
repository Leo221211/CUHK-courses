Q1.1
    Please refer to tests/test_lib_raw.py for the test cases, which should include:
    1. No common substring
    2. One input is empty
    3. Both inputs are empty
    4. Have common substring for short inputs
    5. Have common substring for long inputs
    6. Identical inputs
    7. Common substring at the beginning
    8. Common substring at the end
    9. One input is longer than another

Q2.2

         5007866 function calls in 3.536 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    3.536    3.536 /home/tklam/.venv/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:66(analyze)
        1    2.263    2.263    3.536    3.536 /home/tklam/.venv/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:1(longest_common_substr)
  4006002    0.845    0.000    0.845    0.000 {method 'append' of 'list' objects}
  1001850    0.428    0.000    0.428    0.000 {built-in method builtins.max}
        1    0.000    0.000    0.000    0.000 /home/tklam/.venv/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:45(longest_common_suffix)
        1    0.000    0.000    0.000    0.000 /home/tklam/.venv/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:34(longest_common_prefix)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        6    0.000    0.000    0.000    0.000 {built-in method builtins.len}
        1    0.000    0.000    0.000    0.000 /home/tklam/.venv/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:62(__init__)
        2    0.000    0.000    0.000    0.000 {built-in method builtins.min}

Q3.1 
    analyze(), or longest_common_substr()

    Since `analyze()` is the root of the profiled function, it must be the function that takes the
    most time when considering its own run time and the time spent in all functions it calls. But
    the statistics show `analyze()` and `longest_common_substr()` have the same run time after
    rounding, so both are acceptable. 

Q3.2
    longest_common_substr()

Q4.2
  The techniques used in the sample solution:

  1. More efficient array allocation method instead of `loop + append()`.     
     To our surprise, `[v]*a` is faster than `[v for i in range(a)]` in this case
  2. Another surprise: Built-in functions are said to be usually more efficient. The built-in
     function `max()`, however, is found to be less efficient than a simple if-then-else check in
     this case.
  3. Reduce memory allocation and deallocation in the loop.
     In this case, it is to move the allocation of `cur` from inside the nested loops to the line
     before the loop. Additionally, Instead of copying the content `cur` to `prev`, the memory
     addresses of `prev` and `cur` are swapped afterwards.  This trick does not have significant
     effect, though.

  These techniques, except the last one, can be deduced directly from the profiling result.

Q4.3
```
---------------------------------------------------------------------------------------------------- benchmark: 2 tests ----------------------------------------------------------------------------------------------------
Name (time in ms)                                        Min                   Max                  Mean            StdDev                Median               IQR            Outliers     OPS            Rounds  Iterations
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
test_longest_common_substr_raw (NOW)                676.6374 (1.0)        680.7737 (1.0)        678.5410 (1.0)      1.7661 (1.16)       677.7720 (1.0)      2.9253 (1.08)          2;0  1.4738 (1.0)           5           1
test_longest_common_substr_raw (0001_96ca329)     1,040.6453 (1.54)     1,044.1541 (1.53)     1,042.5620 (1.54)     1.5173 (1.0)      1,042.5870 (1.54)     2.7006 (1.0)           2;0  0.9592 (0.65)          5           1
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Legend:
  Outliers: 1 Standard Deviation from Mean; 1.5 IQR (InterQuartile Range) from 1st Quartile and 3rd Quartile.
  OPS: Operations Per Second, computed as 1 / Mean
```
