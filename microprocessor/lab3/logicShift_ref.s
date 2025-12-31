.data
str1 : .asciz "X << Y = %08X (%d)\n"
str2 : .asciz "X >> Y = %08X (%d)\n"
str3 : .asciz "~X << Y = %08X (%d)\n"
str4 : .asciz "~X >> Y = %08X (%d)\n"
x : .word 15 @ x=15
y : .word 3 @ y=3;
z : .word @ uninitalized

.text
.global main

main :

#X << Y

ldr x1, = x
ldr w2, [x1] @ load x to w2

ldr x3, = y
ldr w4, [x3] @ load y to w4

ldr x5, = z

lsl w6, w2, w4 @ logical shift left x by y (15<<3)
str w6, [x5] @ store w6 to z

ldr x0,=str1
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

#X >> Y

ldr x1, = x
ldr w2, [x1] @ load x to w2

ldr x3, = y
ldr w4, [x3] @ load y to w4

ldr x5, = z

lsr w6, w2, w4 @ logical shift right x by y (15>>3)
str w6, [x5] @ store w6 to z

ldr x0,=str2
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

#~X << Y

ldr x1, = x 
ldr w2, [x1] @ load x to w2
mvn w2, w2 @ invert w2

ldr x3, = y
ldr w4, [x3] @ load y to w4

ldr x5, = z

lsl w6, w2, w4 @ logical shift left ~x by y (-15<<3)
str w6, [x5] @ store w6 to z

ldr x0,=str3
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

#~X >> Y

ldr x1, = x
ldr w2, [x1] @ load x to w2
mvn w2, w2 @ invert w2

ldr x3, = y
ldr w4, [x3] @ load y to w4

ldr x5, = z
#ldr w6, w2, w4
asr w6, w2, w4 @ arithmetic shift right ~x by y (-15>>3)
str w6, [x5] @ store w6 to z

ldr x0,=str4
ldr w1, [x5]
mov w2, w1
bl printf @ print the result

mov x8, 94
mov x0, 0
svc 0
