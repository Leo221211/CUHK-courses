# lab1-1

.global _start

.data 
var1: .word 15
var2: .word 19

.text

_start:
    # print var1
    li a7, 1	# set to print integer
    lw a0, var1	# set int to print
    ecall	# print 
    
    # print var2
    li a7, 1	# set to print integer
    lw a0, var2	# set int to print
    ecall	# print 
    
    # increase var1 by 1
    lw t1, var1 
    addi t1, t1, 1
    sw var1, t1
    
    # multiply var2 by 4
    lw t2, var2
    add t2, t2, t2	# *2
    add t2, t2, t2	# *2
    
    # print 



    
    