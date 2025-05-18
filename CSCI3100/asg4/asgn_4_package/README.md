# qustion 2.2
```
         5007866 function calls in 1.139 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    1.139    1.139 /home/leosunix/anaconda3/envs/leonie/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:66(analyze)
        1    0.712    0.712    1.139    1.139 /home/leosunix/anaconda3/envs/leonie/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:1(longest_common_substr)
  4006002    0.305    0.000    0.305    0.000 {method 'append' of 'list' objects}
  1001850    0.122    0.000    0.122    0.000 {built-in method builtins.max}
        1    0.000    0.000    0.000    0.000 /home/leosunix/anaconda3/envs/leonie/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:45(longest_common_suffix)
        1    0.000    0.000    0.000    0.000 /home/leosunix/anaconda3/envs/leonie/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:34(longest_common_prefix)
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
        6    0.000    0.000    0.000    0.000 {built-in method builtins.len}
        1    0.000    0.000    0.000    0.000 /home/leosunix/anaconda3/envs/leonie/lib/python3.12/site-packages/asgn_4_package/lib_raw.py:62(__init__)
        2    0.000    0.000    0.000    0.000 {built-in method builtins.min}
```

# question 3
1. `StringAnalysis.analyze()`: since it has the highest cumulative time (cumtime).
2. `longest_common_substr()` Since it has the highest `tottime`.

# question 4
3. output of benchmarking
    ```
    Comparing against benchmarks from: Linux-CPython-3.7-64bit/0001_unversioned_20250501_035925.json
    ================================================== test session starts ===================================================
    platform linux -- Python 3.7.16, pytest-7.4.4, pluggy-1.2.0
    benchmark: 4.0.0 (defaults: timer=time.perf_counter disable_gc=False min_rounds=5 min_time=0.000005 max_time=1.0 calibration_precision=10 warmup=False warmup_iterations=100000)
    rootdir: /home/leosunix/workspace/CUHK/csci3100/asg4/asgn_4_package/tests
    plugins: benchmark-4.0.0
    collected 14 items                                                                                                       

    test_lib_benchmark.py .                                                                                            [  7%]
    test_lib_raw.py .............                                                                                      [100%]
    Saved benchmark data in: /home/leosunix/workspace/CUHK/csci3100/asg4/asgn_4_package/tests/.benchmarks/Linux-CPython-3.7-64bit/0008_unversioned_20250501_040225.json



    ------------------------------------------------------------------------------------------------- benchmark: 2 tests -------------------------------------------------------------------------------------------------
    Name (time in ms)                                      Min                 Max                Mean             StdDev              Median                IQR            Outliers     OPS            Rounds  Iterations
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    test_longest_common_substr_raw (NOW)              156.1758 (1.0)      177.4533 (1.0)      167.3609 (1.0)       9.0587 (1.0)      168.8858 (1.0)      17.2043 (1.14)          3;0  5.9751 (1.0)           6           1
    test_longest_common_substr_raw (0001_unversi)     448.2863 (2.87)     495.3566 (2.79)     459.8562 (2.75)     19.9671 (2.20)     451.9819 (2.68)     15.0699 (1.0)           1;1  2.1746 (0.36)          5           1
    ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Legend:
    Outliers: 1 Standard Deviation from Mean; 1.5 IQR (InterQuartile Range) from 1st Quartile and 3rd Quartile.
    OPS: Operations Per Second, computed as 1 / Mean
    =================================================== 14 passed in 3.63s ===================================================
    ```