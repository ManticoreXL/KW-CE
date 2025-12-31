.data
.equ SIZE , 5
EnterIntStr : .asciz "Enter an Integer:"
PrintIntStr : .asciz "The numbers are: "
IntStr1 : .asciz "%d"
IntStr2 : .asciz "%d "
spaceStr : .asciz " \n"

.text
.global main

main:

stp x29, x30, [sp, #-32]! @ save fp, lr on the stack
add x29, sp , #0 @ set fp as sp

mov w1, #0 @ initialize w1 to 0
str w1, [x29,#16] /* Idx */


StackLoop:
ldr x0, = EnterIntStr @ load EnterIntStr into x0
bl printf @ call printf to print the prompt message

ldr x0, = IntStr1 @ load address of IntStr1 into x0
add x1, x29, #24 @ push input onto the stack
bl scanf @ call scanf to read next input

ldr w0, [x29, #24] @ load input from the stack into w0
str w0, [sp, #-16]! @ push input onto the stack

ldr w0, [x29, #16] @ load the current index from fp into w0
add w0, w0, #1 @ increment index
str w0, [x29, #16] @ store updated index to fp
cmp x0, #SIZE @ if(index != size(5)), repeat StackLoop
bne StackLoop 

mov w0, #0 @ set w0 to 0
str w0, [x29, #16] @ store the final index(0) at fp

ldr x0, = PrintIntStr @ load address of PrintIntStr into x0
bl printf @ call printf to print the message before numbers

PrintLoop :
ldr x0, = IntStr2 @ load address of IntStr2 into x0

ldr w1, [sp], #16 @ load the next integer from stack into w1 and increment sp
bl printf @ call printf to print the integer

ldr w0, [x29, #16] @ load the current index from fp into w0
add w0,w0,#1 @ increment index
str w0, [x29, #16] store the updated index back in fp
cmp w0, #SIZE @ if(index != size(5)), repeat Printloop
bne PrintLoop

ldr x0, = spaceStr @ load address of spaceStr into x0
bl printf @ call printf to print \n


ldp x29, x30, [sp], #32 @ restore fp, lr from stack
ret @ return of main
