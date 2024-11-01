.global _start

.data
space: .string " "
array: .word 0

# reg variables 
## s1: length of the array

.text
_start:
    # input
    ## input lenth and store in len
    li a7, 5
    ecall
    mv s1, a0

    ## input the array
    ### t0: for_loop counter
    ### t1: the address of current spot for the array
    la t1, array
    
start_for:
    bge t0, s1, end_for	# check for loop, initially t0 == 0
    
    ### input, a7 == 5 already
    ecall
    
    ### store
    sw a0, 0(t1)  
    
    ### update
    addi t0, t0, 1		# t0 ++
    addi t1, t1, 4		# t1 = t1 + 4
    
    ### jump
    j start_for
end_for:

    # qsort
    la a0, array
    li t0, 0			# index of lo
    addi t1, s1, -1		# index of hi = s1 - 1
    jal ra, qsort		# quick sort    

    # output
    ## vars:
    ### t0: for_loop counter
    ### t1: the address of current spot for the array
    li t0, 0			# init, t0 == 0
    la t1, array		# init t1 is the address of current int to print
    
    ## for_loop to output
start_for_out:
    bge t0, s1, end_for_out	# check for loop
    
    ## load the int to print to a0 and output
    lw a0, 0(t1)
    li a7, 1			# printInt
    ecall
    
    ## ouput a space
    la a0, space
    li a7, 4			# printString
    ecall    

    ## update
    addi t0, t0, 1		# t0 ++
    addi t1, t1, 4		# t1 = t1 + 4
    
    ## jump
    j start_for_out
end_for_out:
    
    # exit
    li a7, 10
    ecall
    
# qsort(hi, lo)    
qsort:
    # description: given lo, hi INDEX of an array, sort it in ascending order (assume last element is pivot)
    # input
    ## t0: lo idx
    ## t1: hi idx
    # var_used:
    ## a0: address of array
    ## a1: (from input param t0) lo -- index
    ## a2: (from input param t1) hi -- index
    ## a3: pivot
    ## a4: i -- index
    ## a5: j -- index
    ## temporary registers
    
    # push
    addi sp, sp, -24
    sw ra, 20(sp)
    sw a1, 16(sp)
    sw a2, 12(sp)
    sw a3, 8(sp)
    sw a4, 4(sp)
    sw a5, 0(sp)
    
    # read input param
    mv a1, t0
    mv a2, t1
    
    # check if end recursion
    ble a2, a1, return_qsort
    
    # partition
    ## init i
    addi a4, a1, -1
    
    ## init j
    addi a5, a1, 0

    ## load pivot
    slli t0, a2, 2
    add t0, t0, a0
    lw a3, 0(t0)
    
    
    ## for loop
start_for_par:
    
    ## for loop check
    addi t3, a2, -1
    bgt a5, t3, end_for_par	# j > hi - 1
    
    ## if check
    slli t0, a5, 2
    add t0, t0, a0
    lw t3, 0(t0)		# t3 = A[j]
    bgt t3, a3, end_if_par		# A[j] > pivot
    
    ## inside if
    addi a4, a4, 1		# i = i + 1
    
    mv t0, a4			# call swap function
    mv t1, a5
    jal ra, swap
   
end_if_par: 
    ## end if
    addi a5, a5, 1
    j start_for_par
    
end_for_par:
    ## swap
    addi t0, a4, 1
    mv t1, a2
    jal ra, swap


    # qsort 2 subarrays
    addi t2, a4, 1		# t2 <- pivot_idx = i + 1
    addi t3, t2, -1		# t3 <- the array that is smaller than pivot's hi = t0 - 1
    addi t4, t2, 1		# t4 <- the array that is bigger than pivot's hi = t0 + 1
    
    ## sort lower array
    mv t0, a1			# lo_lo = lo
    mv t1, t3			# lo_hi = pivot_idx - 1
    jal ra, qsort
    
    ## sort higher array
    mv t0, t4			# hi_lo = pivot_idx + 1
    mv t1, a2			# lo_hi = hi
    jal ra, qsort
    
return_qsort:
    # pop stack
    lw a5, 0(sp)
    lw a4, 4(sp)
    lw a3, 8(sp)
    lw a2, 12(sp)
    lw a1, 16(sp)
    lw ra, 20(sp)
    addi sp, sp, 24
    
    # return
    jr ra
    
    
# swap(m, n)
swap:
    # desc: swap A[m] and A[n]
    # input: t0, t1 is m, n 
    # uses register: t0 ~ t4
    # note: it is more like a macro not a function. Only modifies temp registers
    
    # t0 becomes the address of A[m]
    slli t0, t0, 2	# t0 = t0 * 4
    add, t0, t0, a0	# a0 is the address of the array 
    
    # t1 becomes the address of A[n]
    slli t1, t1, 2	# t1 = t1 * 4
    add, t1, t1, a0
    
    # swap
    lw t3, 0(t0)	# t1 = A[m]
    lw t4, 0(t1)	# t2 = A[n]
    
    sw t3, 0(t1)
    sw t4, 0(t0)
    
    # return
    jr ra
    
    
