	.arch msp430g2553
	.p2align 1,0
	.data
soundOn:
	.word 0
jt:
	.word case0
	.word case1
	
	.text

	.global state_advance
	.extern tone

state_advance:
	mov &soundOn , r12
	cmp #2 , r12
	jhs case0
	add r12 , r12
	mov jt(r12) , r0

case0:
	mov &soundOn , r12
	add #50 , &tone
	cmp #3000, &tone
	jl else0
	mov #1 , &soundOn
	jmp buzzer_set_period

case1:
	sub #50 , &tone
	cmp #1500 , &tone
	jge else1
	mov #0 , &soundOn
	jmp buzzer_set_period

else0:
else1:
	jmp buzzer_set_period

buzzer_set_period:
	mov r13 , &tone
	call #buzzer_set_period
	ret
