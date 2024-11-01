.global _start

.data
var1: .word 5

.text

_start:

lw a1, var1
sw a2, var1, zero

li t1, 1
li t2, 2
sub t3, t1, t2

li t4, -3

li a7, 1
# add a0, t3, zero
add a0, t4, zero
ecall


addi t5, t4, 1
# addi t5, 1, t4
