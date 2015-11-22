		.global main
	
		.section ".text"
		.align 4
	
main: 	save 	%sp, -96, %sp
		
		clr 	%r16 			! Initialize character count
		clr 	%r17			! Initialize newline count
		clr 	%r18 			! Initialize whitespace count
		clr		%r19			! Initialize octal count
		clr 	%r20			! Initialize decimal count
		clr 	%r21			! Initialize hexidecimal count
		clr 	%r22			! Initialize letter count
		
loop: 	call 	getchar 		! Read one character (returned in %r8)
		nop
		
		cmp 	%r8, -1 		! Compare return value to EOF
		be 		end 			! If EOF found, exit loop
		nop
		
		inc 	%r16 			! Increment character count
		

if1:	cmp 	%r8, 0x0a 		! Compare return value to newline
		bne 	endif1			! If newline not found, skip increment
		nop

then1:	inc		%r17			! increment newline
		inc		%r18			! also increment whitespace

endif1:

		
if2: 	cmp 	%r8, 0x20 		! Compare return value to blank
		bne 	endif2 			! If blank not found, skip increment
		nop
		
then2: 	inc 	%r18 			! Increment whitespace count

endif2: 

if3:	cmp		%r8, 0x09		! compare return value to tab
		bne 	endif3			! if not a tab, skip
		nop

then3:	inc		%r18			! increment whitespace

endif3:

if4:	cmp		%r8, 0x2F		! compare to the value before 0
		ble		endif4			! if less than 0, skip
		nop

then4:	cmp 	%r8, 0x38		! compare to the value after 7
		bge		endif4			! if greater than 7, skip
		nop

else4:	inc		%r19			! increment octal

endif4:

if5:	cmp		%r8, 0x2F		! compare to the value before 0
		ble		endif5			! if less than 0, skip
		nop

then5:	cmp 	%r8, 0x3A		! compare to the value after 9
		bge		endif5			! if greater than 9, skip
		nop

else5:	inc		%r20			! increment decimal
		inc 	%r21			! increment hexidecimal, I will increment hex for A-F and a-f later

endif5:

if6:	cmp		%r8, 0x40		! compare to the value before A
		ble		endif6			! if less than A, skip
		nop

then6:	cmp 	%r8, 0x47		! compare to the value after F
		bge		endif6			! if greater than F, skip
		nop

else6:	inc 	%r21			! increment hexidecimal
		
endif6:

if7:	cmp		%r8, 0x60		! compare to the value before a
		ble		endif7			! if less than a, skip
		nop

then7:	cmp 	%r8, 0x67		! compare to the value after f
		bge		endif7			! if greater than f, skip
		nop

else7:	inc 	%r21			! increment hexidecimal for a-f

endif7:

if8:	cmp		%r8, 0x40		! compare to the value before A
		ble		endif8			! if less than A, skip
		nop

then8:	cmp 	%r8, 0x5B		! compare to the value after Z
		bge		endif8			! if greater than Z, skip
		nop

else8:	inc 	%r22			! increment letter for A-Z

endif8:

if9:	cmp		%r8, 0x60		! compare to the value before a
		ble		endif9			! if less than a, skip
		nop

then9:	cmp 	%r8, 0x7B		! compare to the value after z
		bge		endif9			! if greater than z, skip
		nop

else9:	inc 	%r22			! increment letter for a-z

endif9:
		ba 		loop 			! Branch to top of loop
		nop
		
end: 	set 	fmt1, %r8 		! First arg -- address of format string
		mov 	%r16, %r9 		! character count
		
		call 	printf
		nop
		
		mov 	%r17, %r10		! newline count
		mov 	%r18, %r11		! whitespace count
		mov 	%r19, %r12		! octal count
		mov 	%r20, %r13		! decimal count
		mov 	%r21, %r25		! hexidecimal count
		mov 	%r22, %r26		! letter count

		
		ret
		restore
		
fmt1: .asciz "\nThe line contained %d characters\n"

