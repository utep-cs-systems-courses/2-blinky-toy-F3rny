	.arch msp430g2553
	.p2align 1,0
	.text

	.global green_on
	.extern P1OUT

green_on:
	bis #64 , P1OUT 	; P1.6
	and #~1 , P1OUT		; P1.0
	ret
