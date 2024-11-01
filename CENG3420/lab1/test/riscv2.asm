.global _start

.data 
	a: .word -1, 0xaaaaaaaa
	
.text
_start:

	la t0, a
	lb t1, 0(t0)
	lbu t2, 0(t0)
	sb t1, 4(t0)
	li, t3, 0xF
	li, t4, -1