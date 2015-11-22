		.global absolute
		.global modulo
		.global factorial
		.global power
		.global sine
		.section ".text"
		.align 4
		
		

absolute:
		save	%sp, -104, %sp
		
		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f0
		ld		[%sp+100], %f1
		
		fabss	%f0, %f0
				
		ba		done
		nop
		
modulo:
		save	%sp, -112, %sp
		
		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f2
		ld		[%sp+100], %f3
		
		st		%i2, [%sp+96]
		st		%i3, [%sp+100]
		
		ld		[%sp+96], %f4
		ld		[%sp+100], %f5
		
		set		0, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f6		!this is 0.0
		fitod	%f6, %f6

		fcmpd	%f4, %f6
		fbe		y0
		nop
		
		fabss	%f2, %f2
		fabss	%f4, %f4

		fsubd	%f2, %f4, %f0
		
		fcmpd	%f0, %f4
		fbge	modulo2
		nop
		
		fcmpd	%f0, %f4
		fble	modulo2
		nop

		
		ba		done
		nop
		
modulo2:

		fsubd	%f0, %f4, %f0

		fcmpd	%f0, %f4
		fbge	modulo2
		nop
		
		ba		modulodone
		nop
		
y0:
		set		0x7ff00000, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f0		!this is NaN
		
		set		0x00000001, %l1
		st		%l1, [%sp+100]
		ld		[%sp+100], %f1		!this is NaN

		ba		done
		nop
		
modulodone:

		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f2
		ld		[%sp+100], %f3
				
		ld		[%sp+96], %f4
		ld		[%sp+100], %f5
		
		fabss	%f4, %f4
		fdivd	%f2, %f4, %f6
		
		fmuld	%f6, %f0, %f0		
		
		ba 		done
		nop
		
factorial:
		save 	%sp, -104, %sp

		st		%i0, [%sp+96]
		
		ld		[%sp+96], %f0		!this is the input
		fitod	%f0, %f0

		ld		[%sp+96], %f2		!this is also the input
		fitod	%f2, %f2
		
		set		1, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f4		!this is 1.0
		fitod	%f4, %f4
		
		fcmpd	%f0, %f4
		fbe		done
		nop
		
		set		0, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f10		!this is 0.0
		fitod	%f10, %f10

		fcmpd	%f0, %f10
		fbe		factorialzero
		nop

		
factorial1:

		fsubd	%f2, %f4, %f2		! decrement f2
		fmuld	%f0, %f2, %f0		! multiply f0 by f2 and store in f0
		
		fcmpd	%f2, %f4			! compare the value in f2 to 1
		fbne	factorial1			! loop if it isn't 1
		nop
		
		ba		done
		nop
		
factorialzero:
		fmovs	%f4, %f0
		ba		done
		nop


		
power:
		save	%sp, -104, %sp
		
		st		%i0, [%sp+96]
		st		%i1, [%sp+100]

		ld		[%sp+96], %f0		!this is our value
		ld		[%sp+100], %f1
		
		fmovs	%f0, %f2			!this is a second copy of our value
		fmovs	%f1, %f3
		
		st		%i2, [%sp+96]
		ld		[%sp+96], %f4		!this is our power
		fitod	%f4, %f4
		
		set		1, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f6		!this is 1.0
		fitod	%f6, %f6
		
		fmovs	%f6, %f8			!this will be our count
		
		set		0, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f10		!this is 0.0
		fitod	%f10, %f10
		
		fcmpd	%f4, %f10
		fbe		powerzero
		nop
		
powerloop:
		fcmpd	%f4, %f8
		fbe		done
		nop
		
		fmuld	%f0, %f2, %f0
		faddd	%f8, %f6, %f8
		
		ba		powerloop
		nop
		
powerzero:
		fmovs	%f6, %f0
		ba		done
		nop
		
sine:
		save	%sp, -104, %sp
		
		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f0
		ld		[%sp+100], %f1
		
		ld		[%sp+96], %f2
		ld		[%sp+100], %f3
		
		ld		[%sp+96], %f4
		ld		[%sp+100], %f5
		
		ld		[%sp+96], %f6
		ld		[%sp+100], %f7
		
		set		6, %l0
		st		%l0, [%sp+100]
		ld		[%sp+100], %f12		!this is 6.0, 3!
		fitod	%f12, %f12
		
		set		120, %l1
		st		%l1, [%sp+100]
		ld		[%sp+100], %f14		!this is 120, 5!
		fitod	%f14, %f14
		
		set		5040, %l1
		st		%l1, [%sp+100]
		ld		[%sp+100], %f16		!this is 5040, 7!
		fitod	%f16, %f16
		
		set		362880, %l1
		st		%l1, [%sp+100]
		ld		[%sp+100], %f18		!this is 362880, 9!
		fitod	%f18, %f18
		
		fmuld	%f2, %f2, %f2		!this makes x^3
		fmuld	%f0, %f2, %f2
		
		fdivd	%f2, %f12, %f2		!this makes x^3/3!
		
		fsubd	%f0, %f2, %f0		!now f0 is x-x^3/3!
		
		fmuld	%f4, %f6, %f6
		fmuld	%f4, %f6, %f6
		fmuld	%f4, %f6, %f6
		fmuld	%f4, %f6, %f6		!this makes x^5
		
		fdivd	%f6, %f14, %f6
		faddd	%f0, %f6, %f0
		
		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f2
		ld		[%sp+100], %f3
		
		fmuld	%f2, %f2, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6		!this makes x^7
		
		fdivd	%f6, %f16, %f6
		fsubd	%f0, %f6, %f0

		st		%i0, [%sp+96]
		st		%i1, [%sp+100]
		
		ld		[%sp+96], %f2
		ld		[%sp+100], %f3
		
		fmuld	%f2, %f2, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6
		fmuld	%f2, %f6, %f6		!this makes x^9
		
		fdivd	%f6, %f18, %f6
		faddd	%f0, %f6, %f0
				
		ba 		done
		nop


done:
		
		ret
		restore