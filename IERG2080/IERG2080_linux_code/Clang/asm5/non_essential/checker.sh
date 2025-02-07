# !/bin/bash
# input exe name, check compress and decompress using diff from a to d

gcc asm5.c -o non_essential/atest.out -O3 -std=gnu11

for file in {a..d} ; do
    echo check file $file:

    # compress
    non_essential/atest.out c samples/${file}.txt non_essential/checker_out
    cmp non_essential/checker_out samples/${file}.bin

    # decompress
    non_essential/atest.out d samples/${file}.bin non_essential/checker_out
    cmp non_essential/checker_out samples/${file}.txt
done