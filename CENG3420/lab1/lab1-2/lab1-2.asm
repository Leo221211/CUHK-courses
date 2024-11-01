.global _start

.data
array1: .word -1, 22, 8, 35, 5, 4, 11, 2, 1, 78
len: .word 10
original_pivot_index: .word 2
newline: .string "\n"

.text

# main
_start:
    
    # swap pivot to the last element
    lw t0, original_pivot_index	# a0 set to original_pivot_index
    
    lw t1, len
    addi t1, t1, -1			# a1 set to last element index
    
    jal ra, swap			# swap
    
    # perform partition
    la a0, array1			# a0: address of the array
    li a1, 0				# a1: lo = 0
    lw a2, len				
    addi a2, a2, -1			# a2: hi = len - 1
    
    jal a6, partition
    
    # print
    li t0, 0			# init, t0 == 0
    la t1, array1		# init t1 is the address of current int to print
    lw s1, len
    
    ## for_loop to output
start_for_out:
    bge t0, s1, end_for_out	# check for loop
    
    ## load the int to print to a0 and output
    lw a0, 0(t1)
    li a7, 1			# printInt
    ecall
    
    ## ouput a newline
    la a0, newline
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
    
    
    
    
# swap A[m] and A[n], 
#     where m, n is read from t0, t1
#     return to main at last
#     uses register t0 ~ t4, ra
swap:
    # in this fn, t2 is the address of A
    la t2, array1
    
    # t0 becomes the address of A[m]
    slli t0, t0, 2	# t0 = t0 * 4
    add, t0, t0, t2
    
    # t1 becomes the address of A[n]
    slli t1, t1, 2	# t1 = t1 * 4
    add, t1, t1, t2
    
    # swap
    lw t3, 0(t0)	# t1 = A[m]
    lw t4, 0(t1)	# t2 = A[n]
    
    sw t3, 0(t1)
    sw t4, 0(t0)
    
    # return
    jr ra
    

# to partition the array when pivot is the last element  
#    used register: a0 ~ a6, t6
#    a6: return address of this function
#    a0: (input param) address of array
#    a1: (input param) lo -- index
#    a2: (input param) hi -- index
#    a3: pivot
#    a4: i -- index
#    a5: j -- index
#    t6: alternate ra for swap
#
#    return: i + 1 stored in a0

partition:
    # init i
    addi a4, a1, -1
    
    # init j
    addi a5, a1, 0

    # load pivot
    slli t0, a2, 2
    add t0, t0, a0
    lw a3, 0(t0)
    
    
    # for loop
start_for:
    
    # for loop check
    addi t3, a2, -1
    bgt a5, t3, end_for	# j > hi - 1
    
    # if check
    slli t0, a5, 2
    add t0, t0, a0
    lw t3, 0(t0)		# t3 = A[j]
    bgt t3, a3, end_if		# A[j] > pivot
    
    # inside if
    addi a4, a4, 1		# i = i + 1
    
    mv t0, a4			# call swap function
    mv t1, a5
    jal ra, swap
   
end_if: 
    # end if
    addi a5, a5, 1
    j start_for
    
end_for:
    # swap
    addi t0, a4, 1
    mv t1, a2
    jal ra, swap

    # return a0
    addi a0, a4, 1
    
    # return
    jr a6
   
    
    
    
    
    

