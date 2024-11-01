.global _start

.data
# char: .ascii 'h' not working
var: .word 3

.text

_start:
    sw zero, var, t0

    li t0, 1
    slli t0, t0, 1 # cannot be -1