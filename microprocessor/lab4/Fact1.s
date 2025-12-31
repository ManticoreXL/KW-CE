.global fact1
.type fact1, %function
.text

fact1:
    stp x29, x30, [sp, -16]! @ store fp, lr and decrease lr by 16
    mov x29, sp @ set sp as fp
    mov x0, x0 @ x0 = n

    mov x1, 1 @ initialize x1 by 1
    mov x2, 1 @ initialize x2 by 1

loop:
    cmp x2, x0 @ if(i<n), jump to end
    bgt end

    mul x1, x1, x2 @ n *= i;
    add x2, x2, 1 @ i++;
    b loop

end:
    mov x0, x1
    ldp x29, x30, [sp], 16 @ load fp, lr and increase lr by 16
    ret
