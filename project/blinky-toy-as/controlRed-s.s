	.arch msp430g2553
	.p2align 1,0
	.text

	.global red_on
	.extern P1OUT

red_on:
	bis #1 , P1OUT 		; P1.0
	and #~64 , P1OUT	; P1.6
	ret
	
