	la a1, AL
	lw a1, 0(a1)
	la a2, BL
	lw a2, 0(a2)

    add a3, a2, a1
    
	halt

AL   .FILL 4
BL   .FILL -5