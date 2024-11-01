.global _start

.data 
var1: .word 0
var2: .word 0
var3: .word 0
newline: .asciz "\n"

.text

_start:
    ### load variable from console
    # read input1
    li a7, 5
    ecall
    # put input into var1
    la t1, var1		# t1 is the address of var1
    sw a0, 0(t1)
    
    # read input2
    li a7, 5
    ecall
    # put input into var2
    la t2, var2		# t2 is the address of var2
    sw a0, 0(t2)
    
    # read input3
    li a7, 5
    ecall
    # put input into var3
    la t3, var3		# t3 is the address of var3
    sw a0, 0(t3)
    
    
    ### increase var1 by 3
    # addi t4, var1, 3	# add
    lw t4, 0(t1)	
    addi t4, t4, 3
    sw t4, 0(t1)	# t4 is value of var1
    
    
    ### multiply var2 by 2
    lw t5, 0(t2)
    add t5, t5, t5	# multiply
    sw t5, 0(t2)	# t5 is value of var2
    
    
    ### increase var3
    lw t6, 0(t3)	# t0 is temp sum, now var3
    add t6, t6, t4
    add t6, t6, t5
    sw t6, 0(t3)
    
    
    ### print vars
    # print var1
    li a7, 1	# set to print integer
    lw a0, var1	# set int to print
    ecall	# print 
    
    # print new line
    li a7, 4
    la a0, newline
    ecall
    
    # print var2
    li a7, 1	# set to print integer
    lw a0, var2	# set int to print
    ecall	# print 
    
    # print new line
    li a7, 4
    la a0, newline
    ecall
    
    # print var3
    li a7, 1	# set to print integer
    lw a0, var3	# set int to print
    ecall	# print 
    
    # exit
    li a7, 10
    ecall
    
    
    
    
