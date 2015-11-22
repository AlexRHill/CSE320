		.global search
		.global delete
		.global insert
		
		.section ".text"
		.align 4			
		
search:
		save 	%sp, -96, %sp
		
		mov		%i0, %l0
		mov		%i1, %l1

		ld		[%l0+8], %l2		!this is the address of the array of students
				
		or		%g0, %l4, %l4		!this will be our count of the students
		
searchloop:
		ld		[%l2], %l5			!this is the id number of the student we are comparing to
		
		inc		%l4
		
		cmp		%l1, %l5
		be		searchequal
		nop
		
		cmp		%l1, %l5
		bl		searchless
		nop
		
		cmp		%l1, %l5
		bg		searchgreater
		nop
		

searchequal:
		add		%g0, 1, %i0
		
		st		%l2, [%i2]
		
		add		%g0, %l4, %g4

		ba		done
		nop
		
searchless:
		ba		done
		nop
		
searchgreater:
		add		%l2, 48, %l2
		ba		searchloop
		nop
		
delete:
		save 	%sp, -112, %sp
		
		mov		%i0, %o0
		mov		%i1, %o1
		mov		%sp, %o2
		
		call 	search
		nop
		
		cmp		%o0, 1
		be		deletefound
		nop
		
		ba		done
		nop
		
deletefound:

		ld		[%o2], %l0			!this is the address of the student to be deleted	
				
		lduh	[%i0+2], %l7		!this loads the count of the students 	
				
deleteloop:

		cmp		%g4, %l7			!if the student to be deleted is the last of the list, just move the count
		be		deleteend
		nop
		
		ld		[%l0], %l1			!this is the id number of the student we are copying the next student onto
		ld		[%l0+48], %l2		!this is the id number of the next student
		st		%l2, [%l0]
		
		add		%g0, 52, %g1
		add		%g0, 4, %g2			!these two registers will help us to loop every character
		
namemoveloop:
		ldub	[%l0+%g1], %l3
		stb		%l3, [%l0+%g2]

		add		%g1, 1, %g1
		add		%g2, 1, %g2
		
		cmp		%l3, 0
		bne		namemoveloop
		nop
		
deleteloop2:

		ld		[%l0+80], %f16
		st		%f16, [%l0+32]
		
		ld		[%l0+84], %l2		!this moves the total
		st		%l2, [%l0+36]
		
		lduh	[%l0+88], %l2		!this moves the exam1
		sth		%l2, [%l0+40]

		lduh	[%l0+90], %l2		!this moves the exam2
		sth		%l2, [%l0+42]

		lduh	[%l0+92], %l2		!this moves the homework
		sth		%l2, [%l0+44]

		inc		%g4
		
		add		%l0, 48, %l0
		
		ba		deleteloop
		nop
		
deleteend:

		dec		%l7    				!this will change the count of students that the table recognizes
		sth		%l7, [%i0+2]
		
		add		%g0, 1, %i0			!return 1 if delete succeeds
				
		ba		done
		nop

insert:
		save 	%sp, -120, %sp
		
		mov		%i0, %o0
		mov		%i1, %o1
		mov		%sp, %o2
		
		call 	search
		nop
		
		cmp		%o0, 1				!if the student is found, insert fails
		be		done
		nop
		
insertnotfound:
		
		mov		%i0, %l0
		ld		[%l0+8], %l5
		lduh	[%l0+2], %l6
		smul	%l6, 48, %l7
				
		add		%l5, %l7, %l5
		
		mov		%i1, %l1
		st		%l1, [%l5]
		
		and		%g1, %g0, %g1		!sets g1 to 0
		and		%g0, %g2, %g2		!sets g2 to 0
		add		%g2, 4, %g2
		
		mov		%i2, %l2			!sets the name to l2
		
namemoveloop2:
		ldub	[%l2+%g1], %l3
		stb		%l3, [%l5+%g2]

		add		%g1, 1, %g1
		add		%g2, 1, %g2
		
		cmp		%l3, 0
		bne		namemoveloop2
		nop
		
insertaverage:
		add		%i3, %i4, %l4
		add		%i5, %l4, %l4
		
		st		%l4, [%sp+116]
		ld		[%sp+116], %f16		!this is the total points the student has scored
		fitos	%f16, %f16
		
		ld		[%i0+4], %f17
		fitos 	%f17, %f17			!this is the total points available
		
		fdivs	%f16, %f17, %f1
		
		st		%f1, [%l5+32]
		
insertfields:
		st		%l4, [%l5+36]
		sth		%i3, [%l5+40]
		sth		%i4, [%l5+42]
		sth		%i5, [%l5+44]
		
		add		%g0, 48, %l1
		
		add		%l5, 48, %g7
		
findplaceloop:
		ld		[%l5], %l2
		sub		%l5, %l1, %l4
		ld		[%l4], %l3
		
		cmp		%l2, %l3
		bg		found	
		nop
		
		add		%l1, 48, %l1
		
		ba		findplaceloop
		nop
		
found:
		udiv	%l1, 48, %l1
		sub		%l1, 1, %l1  		!this number is how many values that still need to be moved
		
movedownloop:
		cmp		%l1, -1				!if the inserted value is already in the right place, then we're done
		be		insertfinal
		nop

		add		%l5, 48, %l4
		
		ld		[%l5], %l3
		st		%l3, [%l4]
		
		add		%g0, 4, %g2			!this register will help us to loop every character
		
namemoveloopinsert:
		ldub	[%l5+%g2], %l3
		stb		%l3, [%l4+%g2]

		add		%g2, 1, %g2
		
		cmp		%l3, 0
		bne		namemoveloopinsert
		nop

movedownloop2:
		
		ld		[%l5+32], %f16
		st		%f16, [%l4+32]
		
		ld		[%l5+36], %l2		!this moves the total
		st		%l2, [%l4+36]
		
		lduh	[%l5+40], %l2		!this moves the exam1
		sth		%l2, [%l4+40]

		lduh	[%l5+42], %l2		!this moves the exam2
		sth		%l2, [%l4+42]

		lduh	[%l5+44], %l2		!this moves the homework
		sth		%l2, [%l4+44]

		sub		%l1, 1, %l1
		
		sub		%l5, 48, %l5
		
		ba		movedownloop
		nop
		
insertfinal:
		sub 	%l4, 48, %l4

		ld		[%g7], %l2
		st		%l2, [%l4]
		
		add		%g0, 4, %g2			!this register will help us to loop every character
		
namemoveloopinsertfinal:
		ldub	[%g7+%g2], %l3
		stb		%l3, [%l4+%g2]

		add		%g2, 1, %g2
		
		cmp		%l3, 0
		bne		namemoveloopinsertfinal
		nop
		
		ld		[%g7+32], %f16
		st		%f16, [%l4+32]
		
		ld		[%g7+36], %l2		!this moves the total
		st		%l2, [%l4+36]
		
		lduh	[%g7+40], %l2		!this moves the exam1
		sth		%l2, [%l4+40]

		lduh	[%g7+42], %l2		!this moves the exam2
		sth		%l2, [%l4+42]

		lduh	[%g7+44], %l2		!this moves the homework
		sth		%l2, [%l4+44]


insertend:
		add		%l6, 1, %l6
		sth		%l6, [%i0+2]
		
		add		%g0, 1, %i0			!return 1 if insert succeeds
		
done:
		ret
		restore
		
		
