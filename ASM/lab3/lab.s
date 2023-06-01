BITS 64

section .data
error_invalid_file db "Error: invalid file", 0x0a, 0
error_no_args db "Error: you have to specify a filename", 0x0a, 0
filename db 0
data db 0

section .text
    global _start

_start:

main:
    mov     rax, [rsp]
    cmp     eax, 1 ;check arguments
    je      _error_no_args

    mov     rdi, [rsp + 16] ; move 2nd argument (filename) to rdi
    mov     rdi, [rdi]
    mov     [filename], rdi
	
    call    load_file
    mov     edi, data

    call    process_lines
    mov     edi, data
	
    call    print
    .end:
    jmp     _exit_normal

process_lines:
    .loop:
        cmp     byte [edi], 0
        je      .end
        call    process_line
        inc     edi
        jmp     .loop
    .end:
    ret

process_line:
        cmp     byte [edi], 0x0a
        je      .end
        cmp     byte [edi], 0
        je      .end
        push    rdi
        push    rsi
        call    clean_dividers
        pop     rsi
        pop     rdi
        push    rdi
        push    rsi
        call    get_bound
        mov     r11, rsi
        pop     rsi
        pop     rdi

    .loop:
        cmp     byte [edi], 0x0a
        je      .end
        cmp     byte [edi], 0
        je      .end
        push    rdi
        push    rsi
        call    clean_dividers
        pop     rsi
        pop     rdi
        call    get_bound
        push    rdi
        push    rsi
        call    check_last_letter
        pop     rsi
        pop     rdi
        inc     esi
        sub     esi, edi
        cmp     eax, 1
        je .skip
            push    rdi
            call    delete_characters
            pop     rdi
            mov     esi, 0
            jmp     .continue
        .skip:
            add     edi, esi
            cmp     byte [edi], 0
            mov     esi, 0
            je      .continue
            inc     edi
        .continue:
        push    rdi
        push    rsi
        call    clean_dividers
        pop     rsi
        pop     rdi
        add     edi, esi
        jmp     .loop
        
    .end:
    cmp     byte [rdi], 0x0a
    je      .dont_clean
    dec     rdi
    push    rdi
    push    rsi
    call    clean_dividers
    pop     rsi
    pop     rdi
    .dont_clean:
    ret

	
clean_dividers:
    .loop:
        cmp     byte [edi], 0x20    ; check if space
        jne     .no_space
        jmp     .delete
        .no_space:
        cmp     byte [edi], 0x09    ; check if tab
        jne     .end
        .delete:
        push    rdi
        mov     esi, 1
        call    delete_characters
        pop     rdi
        jmp     .loop
    .end:
    ret

delete_characters:
    mov     ecx, esi
    .loop:
        cmp     ecx, 0
        jle     .end
        mov     ebx, edi
        .inner:
            cmp     byte [ebx], 0
            je      .continue
            mov     al, byte [ebx + 1]
            mov     byte [ebx], al
            inc     ebx
            jmp     .inner
        .continue:
        loop    .loop
    .end:
    ret

get_bound:
    mov     esi, edi
    .loop:
        cmp     byte [esi], 0x20    ; check if space
        je      .end
        cmp     byte [esi], 0x09    ; check if tab
        je      .end
        cmp     byte [esi], 0x0a    ; check if \n
        je      .end
        cmp     byte [esi], 0       ; check if \0
        je      .end
        inc     esi
        jmp     .loop
    .end:
    dec esi
    ret

check_last_letter:
    mov     al, byte [esi] ;last symbol
    cmp     al, byte [r11] 
    jne     .false
    .true:
        mov     eax, 1
        ret
    .false:
        mov     eax, 0
        ret

print:
    mov     esi, edi
    mov     edi, 1      ; File descriptor for stdout
    mov     edx, 1
    .loop:
        mov     eax, 1          ; System call for write
        syscall
        cmp     byte [esi], 0
        je      .end
        inc     esi
        jmp     .loop
    .end:
    ret

load_file:
    ; Open the file for reading
    mov     eax, 2
    mov     edi, filename
    xor     esi, esi        ; No flags
    mov     edx, 0644       ; rw-r--r--
    syscall
    cmp     eax, 0
    jl      _invalid_file
    mov     ebp, eax        ; Save the file descriptor in ebp

    mov esi, data
    mov edx, 1
    .loop:
        mov     eax, 0      ; system call read
        mov     edi, ebp
        syscall
        test    eax, eax    ; check for ctrl+D
        je      .end
        add     esi, eax
        jmp     .loop
    .end:
    mov     byte [esi], 0

    ; Close the file
    mov eax, 3
    mov edi, ebp
    syscall
    ret

_exit_normal:
    ; Exit program normally
    mov     rdi, 0
    jmp     _exit

_error_no_args:
    push error_no_args
    jmp _exit_error

_invalid_file:
    push error_invalid_file
    jmp _exit_error

_exit_error:
    ; Exit program with error code 1
    pop     rdi
    call    print
    mov     rdi, 1
    jmp     _exit

_exit:
    mov     rax, 60     ; Syscall for exit
    syscall
