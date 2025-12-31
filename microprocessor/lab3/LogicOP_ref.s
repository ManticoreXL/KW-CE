.data
strNOT : .asciz "NOT X = %08X (%d)\n"
strAND : .asciz "X AND Y = %08X (%d)\n"
strOR : .asciz "X OR Y = %08X (%d)\n"
strXOR : .asciz "X XOR X = %08X (%d)\n"
x : .word 13 @ x=13
y : .word 15 @ y=15
z : .word     @ uninitalized

.text
.global main

main :

#NOT
ldr x1, = x 
ldr w2, [x1] @ load x to w2

#ldr x3, = y
#ldr w4, [x3] @ load y to x3

ldr x5, = z

mvn w6, w2 @ w6 = ~w2
str w6, [x5] @ store w6 to z

ldr x0,=strNOT
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

#AND
ldr x1, = x
ldr w2, [x1] @ load x to w2

ldr x3, = y
ldr w4, [x3] @ load y to x3

ldr x5, = z

and w6, w2, w4 @ w6 = w2 & w4
str w6, [x5] @ store w6 to z

ldr x0,=strAND
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

#OR
ldr x1, = x
ldr w2, [x1] @ load x to w2

ldr x3, = y
ldr w4, [x3] @ load y to x3

ldr x5, = z

orr w6, w2, w4 @ w6 = w2 | w4
str w6, [x5] @ store w6 to z

ldr x0,=strOR
ldr w1, [x5]
mov w2, w1 
bl printf @ print the result

#XOR
ldr x1, = x
ldr w2, [x1] @ load x to w2

ldr x3, = y
ldr w4, [x3] @ load y to x3

ldr x5, = z

eor w6, w2, w4 @ w6 = w2 ^ w4
str w6, [x5] @ store w6 to z

ldr x0,=strXOR
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

mov x8, #94
mov x0, #0
svc 0 


