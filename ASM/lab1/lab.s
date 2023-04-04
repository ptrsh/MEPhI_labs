bits 64     
                                                                                                             
; Expression: b*c + a/(d + e) - d**2/(b*e) + a*e
; Answer = 540 will be in RBP

section .data
a dw 24      
b dw 5      
c dw 100 
d dw 10    
e dw 2

section .text
global _start
_start:
    ; init variables
    movsx eax, word[a] 
    movsx ebx, word[b]
    movsx ecx, word[c]
    movsx edi, word[d]
    movsx esi, word[e]

    ; calculate b*c
    push rax            ; save eax = a
    mov eax, ebx        ; eax = ebx = b
    imul ecx            ; eax = b * ecx = b * c
    mov ebp, eax        ; ebp = eax = b * c
    pop rax             ; restore eax = a

    ; calculate +a/(d + e)
    push rdi            ; save edi = d
    add edi, esi        ; edi = d + esi = d + e
    cmp edi, 0          ; compare edi=(d + e) to zero
    je division_by_zero ; jump to division_by_zero if edi is zero
    push rax            ; save eax = a
    idiv edi            ; eax = eax / edi = a/(d + e)
    add ebp, eax        ; ebp = b*c + edi = b*c + a/(d + e)
    pop rax             ; restore eax = a
    pop rdi             ; restore edi = d

    ; calculate -d**2/(b*e)
    push rax            ; save eax = a
    mov eax, ebx        ; eax = ebx = b
    imul esi            ; eax = b * esi = b * e
    push rcx            ; save ecx = c;
    mov ecx, eax        ; ecx = eax = b * e
    cmp ecx, 0          ; compare ecx=b*e to zero
    je division_by_zero ; jump to division_by_zero if ecx is zero
    mov eax, edi        ; eax = edi = d
    imul eax            ; eax = d * eax = d ** 2
    idiv ecx            ; eax = eax / ecx = d ** 2 / (b*e)
    sub ebp, eax        ; ebp = b*c + a/(d + e) - eax = b*c + a/(d + e) - d ** 2 / (b*e)
    pop rcx             ; restore ecx = c
    pop rax             ; restore eax = a

    ; calculate +a*e
    push rax            ; save eax = a
    imul esi            ; eax = eax * esi = a * e
    add ebp, eax        ; ebp = b*c + a/(d + e) - d ** 2 / (b*e) + eax = b*c + a/(d + e) -
                        ; - d**2/(b*e) + a*e
    pop rax             ; restore eax = a

    mov edi, 0
    jmp exit

exit:
    mov eax, 60
    syscall

division_by_zero:
    mov edi, 1
    jmp exit
