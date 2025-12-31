.data
num : .asciz "%d"
Enter1 : .asciz "Enter n1: "
Enter2 : .asciz "Enter n2: "
Enter3 : .asciz "Enter n3: "
str4 : .asciz "The smallest number is %d\n"

.align
n1 : .space 4
n2 : .space 4
n3 : .space 4
min : .space 4

.text
.global main

main : 

#Enter 1
ldr x0, = Enter1
bl printf
ldr x0, = num
ldr x1, = n1
bl scanf

#Enter 2
ldr x0, = Enter2
bl printf
ldr x0, = num
ldr x1, = n2
bl scanf

#Enter 3
ldr x0, = Enter3
bl printf
ldr x0, = num
ldr x1, = n3
bl scanf

ldr x1, =n1
ldr x2, =n2
ldr x3, =n3
ldr x4, = min

ldr w5, [x1] @ load n1 to w5
ldr w6, [x2] @ load n2 to w6
ldr w7, [x3] @ load n3 to w7

#comparing

if1:
cmp w5, w6 @ compare n1 with n2
bge else1 @ if n1 >= n2, jump to else1

if11:
cmp w5, w7 @ compare n1 with n3
bge else11 @ if n1 >= n3, jump to else11
str w5, [x4] @ store n1 to min
b prt

else11:
str w7, [x4] @ stroe n3 to min
b prt

else1:
if2:
cmp w6, w7 @ compare n2 with n3
bge else21 @ if n2 >= n3, jump to else21
str w6, [x4] @ store n2 to min
b prt

else21:
str w7, [x4] @ store n3 to min

prt:
ldr x0, = str4
ldr w1, [x4]
bl printf @ print the result

mov x8, #94
mov x0, #0
svc 0



