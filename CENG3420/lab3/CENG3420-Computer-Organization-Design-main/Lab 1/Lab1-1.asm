.globl _start

.data
var1: .byte 15
var2: .byte 19
newline: .string "\n"

.text
_start:

    la a0, var1
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    la a0, var2
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    lb t1, var1
    addi t1, t1, 1
    la a0, var1
    sb t1, 0(a0)
    lb a0, var1
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    lb t1, var2
    li t2, 4
    mul t1, t1, t2
    la a0, var2
    sb t1, 0(a0)
    lb a0, var2
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    la a1, var1
    lb t1, var2
    lb t2, var1
    la a2, var2
    sb t1, 0(a1)
    sb t2, 0(a2)

    lb a0, var1
    li a7, 1
    ecall

    la a0, newline
    li a7, 4
    ecall

    lb a0, var2
    li a7, 1
    ecall
