.global fact2
.type fact2,%function
.text

fact2:
    stp x29, x30, [sp, -16]! @ store fp, lr and decrease lr by 16
    mov x29, sp @ set sp as fp

    cmp x0, 1 @ if(n==1), jump to ret1
    blt ret1

    sub sp, sp, #16 @ decrease sp by 16
    str x0, [sp] @ store x0 to stack

    sub x0, x0, 1 
    bl fact2 @ fact2(n-1)

    ldr x1, [sp]
    mul x0, x0, x1 @ n*fact(n-1)

    add sp, sp, 16
    ldp x29, x30, [sp], 16 @ load fp, lr and increase lr by 16
    ret

ret1:
    mov x0, 1 @ 1!=1
    ldp x29, x30, [sp], 16 @ load fp, lr and increase lr by 16
    ret

