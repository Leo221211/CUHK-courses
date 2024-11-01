.globl _start

.data
array1: .word -1, 22, 8, 35, 5, 4, 11, 2, 1, 78
space: .string " "

.text
_start:
	la t0, array1 #t0 = array address

	li a1, 9 # hi
	li a2, 0 # lo

	jal ra, Quicksort 

Print:

	li t1, 0
	li t2, 9
	Print_loop_head:
	bgt t1, t2, Print_end
		slli a1, t1, 2
		add a1, t0, a1
		lw a0, 0(a1)
		li a7, 1
		ecall
		la a0, space
		li a7, 4
		ecall
	addi t1, t1, 1
	j Print_loop_head

Print_end:

j End

Quicksort:

	addi sp, sp, -16
	sw ra, 0(sp)
	sw a2, 4(sp)
	sw a1, 8(sp)
	sw t2, 12(sp)

	bge a2, a1, Quicksort_end
		jal ra, Partitioning
		addi a1, t2, -1
		jal ra, Quicksort
		addi a2, t2, 1
		lw a1, 8(sp)
		jal ra, Quicksort

Quicksort_end:

	lw ra, 0(sp)
	lw a2, 4(sp)
	lw a1, 8(sp)
	lw t2, 12(sp)
	addi sp, sp, 16
	jr ra

Partitioning:

	addi sp, sp, -4
	sw ra, 0(sp)

	slli t1, a1, 2
	add t1, t0, t1
	lw t1, 0(t1)					# pivot
	addi t2, a2, -1 				# i
	mv t3, a2 						# j
	addi t4, a1, -1 				#t4 = end condition
	loop_head:
	bgt t3, t4, loop_end 			#if j > 8 then end for loop / (j<=8)
		slli t5, t3, 2 
		add t5, t0, t5 				#t5 = base address of t0 + offset
		lw t6, 0(t5) 				#store the j-th number into t6
		bgt t6, t1, if_end 			#if the array number is greater then pivot then end if
			addi t2, t2, 1 			# i = i + 1
			slli a5, t2, 2 
			add a5, t0, a5 			#a5 = base address of t0 + offset
			lw a6, 0(a5) 			#we take the value of location a5 (the i-th value)
			sw t6, 0(a5) 			#swap location a5 (i) value with j-th value
			sw a6, 0(t5) 			#swap location t5 (j) value with i-th value
		if_end:
		addi t3, t3, 1
	j loop_head
	loop_end:
	addi t2, t2, 1
	slli a5, t2, 2
	add a5, t0, a5
	lw a6, 0(a5)
	slli t5, a1, 2
	add t5, t0, t5
	lw t6, 0(t5)
	sw t6, 0(a5) 
	sw a6, 0(t5)

	lw ra, 0(sp)
	addi sp, sp, 4
	jr ra

Partitioning_end:

End:
