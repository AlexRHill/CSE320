		.global negate
		.global absolute
		.global add
		.global sub
		.global mul
		.global divide
		.global remain
		.global factorial
		.global power
		.section ".text"
		.align 4

negate:
		save 	%sp, -96, %sp

		smulcc	%i0, -1, %l7	! multiply by -1
		mov		%l7, %i0
		ba		done
		nop

absolute:
		save 	%sp, -96, %sp
		
		cmp		%i0, 0			! compare to 0
		bl		absoluteneg
		mov 	%i0, %i0
		ba 		done
		nop

absoluteneg:
		smulcc	%i0, -1, %l7	! multiply by -1
		mov		%l7, %i0
		ba		done
		nop


add:
		save 	%sp, -96, %sp
		
		addcc 	%i0, %i1, %l7 	! Add the operands, set NZVC
		mov		%l7, %i0		! Store result
		
		bvs		overflow
		nop

		ba		done
		nop
		
sub:
		save 	%sp, -96, %sp
		
		subcc 	%i0, %i1, %l7 	! Subtract the operands, set NZVC
		mov		%l7, %i0		! Store result 
		
		bvs		overflow
		nop

		
		ba		done
		nop

mul:
		save 	%sp, -96, %sp
		
		smulcc 	%i0, %i1, %l7 	! multiply the operands, set NZVC
		mov		%l7, %i0		! Store result 
		ba		done
		nop

divide:
		save 	%sp, -96, %sp
				
		cmp		%i0, 0
		bl		divfirstneg
		nop
		
		sdivcc 	%i0, %i1, %l7 	! divide the operands, set NZVC
		mov		%l7, %i0		! Store result 
		
		bvs		overflow
		nop
		
		ba		done
		nop
		
divfirstneg:

		cmp		%i1, 0
		bge		divfirstnegsecondpos
		nop
		
		sdivcc 	%i0, %i1, %l7 	! divide the operands, set NZVC
		mov		%l7, %i0		! Store result 
		ba		done
		nop
		
divfirstnegsecondpos:			! I was having troubles when dividing a negative number by a positive number
		
		smul 	%i0, -1, %i0	! so my quick fix was just to multiply it by -1
		
		sdivcc 	%i0, %i1, %l7 	! divide the operands, set NZVC
		
		smul	%l7, -1, %l7	! gotta multiply it back
		
		mov		%l7, %i0		! Store result 
		ba		done
		nop

remain:
		
		save 	%sp, -96, %sp
		
		cmp		%i0, 0			! compare the first operand to 0
		bge		firstpos 		! branch if positive
		nop

		cmp		%i0, 0
		bl		firstneg
		nop
		
firstpos:
		cmp		%i1, 0
		bge		firstpossecondpos
		nop
		
		cmp		%i1, 0
		bl		firstpossecondneg
		nop

firstneg:
		cmp		%i1, 0
		bge		firstnegsecondpos
		nop
		
		cmp		%i1, 0
		bl		firstnegsecondneg
		nop
		
firstpossecondpos:
		sdiv 	%i0, %i1, %l7 	! divide the operands
		smul	%l7, %i1, %l6	! multiply the result by the divisor
		sub		%i0, %l6, %l5	! subtract the multiplication result from the first number
		
		smul	%l5, -1, %l5
		
		mov		%l5, %i0
		
		ba		done
		nop

firstpossecondneg:
		smul	%i1, -1, %i1	! multiply i1 by -1 to make things easy

		sdiv 	%i0, %i1, %l7 	! divide the operands
		smul	%l7, %i1, %l6	! multiply the result by the divisor
		sub		%i0, %l6, %l5	! subtract the multiplication result from the first number
		
		smul	%l5, -1, %l5	! now we multiply by -1 to make the remainder correct

		mov		%l5, %i0

		ba		done
		nop

firstnegsecondpos:
		smul	%i0, -1, %i0	! multiply i0 by -1 to make things easy

		sdiv 	%i0, %i1, %l7 	! divide the operands
		smul	%l7, %i1, %l6	! multiply the result by the divisor
		sub		%i0, %l6, %l5	! subtract the multiplication result from the first number
		
		mov		%l5, %i0
				
		ba		done
		nop

firstnegsecondneg:
		smul	%i0, -1, %i0	! multiply i1 by -1 to make things easy
		smul	%i1, -1, %i1	! multiply i1 by -1 to make things easy

		sdiv 	%i0, %i1, %l7 	! divide the operands
		smul	%l7, %i1, %l6	! multiply the result by the divisor
		sub		%i0, %l6, %l5	! subtract the multiplication result from the first number
		
		smul	%l5, -1, %l5	! now we multiply by -1 to make the remainder correct
		
		mov		%l5, %i0
		
		ba		done
		nop

factorial:
		
		save 	%sp, -96, %sp
		
		cmp		%i0, 0
		be		factorial0
		nop
		
		cmp		%i0, 0
		bl		overflow
		nop

		mov		%i0, %l0		! we move the original value into the l0 register
		mov		%l0, %l1		! we move the original value into the l1 register


factorial1:
		dec		%l1				! decrement l1
		smul	%l0, %l1, %l0	! multiply l0 by l1 and store in l0
		
		cmp		%l1, 1			! compare the value in l1 to 1
		bne		factorial1		! loop if it isn't 1
		
		mov		%l0, %i0
		ba		done
		nop
		
factorial0:
		mov		1, %i0
		ba		done
		nop
				
		
power:
		save 	%sp, -96, %sp
		
		cmp		%i1, 0			! compare the power to zero
		bl		negpower		! if it's negative, branch to the error condition
		nop	

		mov		%i0, %l0		! original value will become our final value
		mov		%i0, %l1		! original value
		mov		%i1, %l2		! power
		mov		1, %l3			! count
		
		ba 		power2
		
power2:
		cmp		%l2, %l3
		be		powerfinal
		nop
		
		smul	%l0, %l1, %l0	!multiply l0 by l1, place in l0
		inc		%l3				!increment the count, we are now on that power
		
		ba		power2
		nop
		
powerfinal:
		mov 	%l0, %i0
		ba		done
		nop
		
negpower:
		set		0x80000000, %i0		!negative power is an error condition
		ba		done
		nop
overflow:
		set		0x80000000, %i0		!overflow is an error condition
		ba		done
		nop
done:
		ret
		restore
		