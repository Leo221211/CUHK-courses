.global _start

.data
welcome_msg: .asciz "Welcome"

.text
_start:
	la a1, welcome_msg
	
	ecall
	