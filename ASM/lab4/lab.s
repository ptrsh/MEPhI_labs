BITS 64

section .data
    msg_scan_x  db "Input x: ", 0
    msg_scan_n  db "Input n: ", 0

    format_float    db "%f", 0
    format_int      db "%d", 0

    msg_res_custom  db "Custom result: %f", 0x0a, 0
    msg_res_library db "Library result: %f", 0x0a, 0
    msg_error       db "Incorrect input!", 0x0a, 0

    one dq 0x3FF0000000000000
    minus_one dq 0x3F8CCCCD

section .text
    extern  scanf
    extern  printf
    extern  pow
    extern  atanh
    global  main

main:
    push        rbp
    mov         rbp, rsp
    sub         rsp, 0x10
    mov         eax, 0
    call        scan_x
    movd        eax, xmm0
    mov         [rbp - 0x10], eax
    mov         eax, 0
    call        scan_n
    mov         [rbp - 0x0c], eax
    mov         edx, [rbp - 0x0c]
    mov         eax, [rbp - 0x10]
    mov         edi, edx ;edi=n
    movd        xmm0, eax ;xmm0=x
    call        custom
    movd        eax, xmm0
    mov         [rbp - 0x08], eax
    mov         eax, [rbp - 0x10]
    movd        xmm0, eax
    call        lib
    movd        eax, xmm0
    mov         [rbp - 0x04], eax
    pxor        xmm1, xmm1
    cvtss2sd    xmm1, [rbp - 0x08]
    movq        rax, xmm1
    movq        xmm0, rax
    lea         rax, [msg_res_custom]
    mov         rdi, rax
    mov         eax, 1
    call        printf
    pxor        xmm2, xmm2
    cvtss2sd    xmm2, [rbp - 0x04]
    movq        rax, xmm2
    movq        xmm0, rax
    lea         rax, [msg_res_library]
    mov         rdi, rax
    mov         eax, 1
    call        printf
    mov         eax, 0
    leave
    retn

scan_x:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x10
    mov     [rbp - 0x08], rax
    xor     eax, eax
    lea     rax, [msg_scan_x]
    mov     rdi, rax
    mov     eax, 0
    call    printf
    lea     rax, [rbp - 0x0c]
    mov     rsi, rax
    lea     rax, [format_float]
    mov     rdi, rax
    mov     eax, 0
    call    scanf
    movss   xmm0, [rbp - 0x0c]
    mov     rax, [rbp - 0x08]
    leave
    ret

scan_n:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x10
    mov     [rbp - 0x08], rax
    xor     eax, eax
    lea     rax, [msg_scan_n]
    mov     rdi, rax
    mov     eax, 0
    call    printf
    lea     rax, [rbp - 0x0c]
    mov     rsi, rax
    lea     rax, [format_int]
    mov     rdi, rax
    mov     eax, 0
    call    scanf
    mov     eax, [rbp - 0x0c]
    mov     rdx, [rbp - 0x08]
    leave
    retn

lib:
    push        rbp
    mov         rbp, rsp
    sub         rsp, 0x10
    movss       [rbp-0x4], xmm0
    cvtss2sd    xmm0, [rbp-0x4]
    call        atanh
    cvtsd2ss    xmm0, xmm0
    leave
    retn

custom:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 20h
    movss   [rbp-0x14], xmm0
    mov     [rbp-0x18], edi
    pxor    xmm0, xmm0
    movss   [rbp-0x4], xmm0
    mov     byte[rbp-0x8], 0
    jmp     .check
    .loop:
        mov     eax, [rbp-0x8]
        add     eax, eax
        add     eax, 1
        cvtsi2sd xmm1, eax      
        cvtss2sd xmm0, [rbp-0x14] 
        call    pow
        mov     eax, [rbp-0x8]
        add     eax, eax
        add     eax, 1
        cvtsi2sd xmm1, eax
        divsd   xmm0, xmm1
        movapd  xmm1, xmm0
        cvtss2sd xmm0, [rbp-0x4]
        addsd   xmm0, xmm1
        cvtsd2ss xmm0, xmm0
        movss   [rbp-0x4], xmm0
        add     byte[rbp-0x8], 1
        .check:
            mov     eax, [rbp-0x8]
            cmp     eax, [rbp-0x18]
            jl      .loop
    movss   xmm0, [rbp-0x4]
    leave
    retn


error_exit:
    lea         rax, [msg_error]
    mov         rdi, rax
    mov         eax, 1
    call        printf
    mov         eax, 0
    leave
    retn