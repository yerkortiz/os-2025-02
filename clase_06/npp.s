.section .data
n:      .word 5

.section .text
.global _start

_start:
    ldr w0, =n
    ldr w1, [w0]
    add w1, w1, #1
    str w1, [w0]

    mov x8, 93
    mov x0, 0
    svc 0
