	.arch msp430g2553
	.p2align 1,0
	.text			;jt is the jmp table

jt:
	.word case0		;
	.word case1		;
	.word case2		;
	.word case3		;
	.word case4		;
	.word case5		;
	.word case6		;
	.word case7		;
	.word default		;

	.extern convertNote	;
	.global scaleSongStateMachine
scaleSongStateMachine:
	SUB #2, R1		;make room in the stack for a short
	MOV #0, 0(R1)		;note = 0
	CMP #0, R12		;state - 0
	JLO default		;state < 0 (signed comparison)
	CMP #8, R12		;state - 8
	JC  default		;state >= 8 (unsigned comparison)
	ADD R12, R12		;r12 = 2*state
	MOV jt(R12), R0		;jmp jt[state]

case0:
	MOV #261, 0(R1)		;note = 261
	JMP convert		;
case1:
	MOV #294, 0(R1)		;note = 294
	JMP convert		;
case2:
	MOV #330, 0(R1)		;note = 330
	JMP convert		;
case3:
	MOV #349, 0(R1)		;note = 349
	JMP convert		;
case4:
	MOV #392, 0(R1)		;note = 392
	JMP convert		;
case5:
	MOV #440, 0(R1)		;note = 440
	JMP convert		;
case6:
	MOV #494, 0(R1)		;note = 494
	JMP convert		;
case7:
	MOV #523, 0(R1)		;note = 523
	JMP convert		;
default:
	MOV #0, 0(R1)		;note = 0
	JMP end			;
convert:
	MOV 0(R1), R12		;move note into the parameter
	CALL #convertNote	;call convertNote(note)
	JMP end			;
end:	
	ADD #2, R1		;reset the stack
	POP R0			;return
	
	
