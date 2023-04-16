bits	64
;	Sorting rows of matrix by min elements
section	.data
n:
	dw	4
m:
	dw	5
matrix:
	dw	7, 8, 9, 4, 6	
	dw	16, 15, 14, 13, 1
	dw	9, 10, 13, 12, 11
	dw	1, 3, 2, 9, 5
min:
	dw	0, 0, 0, 0
section	.text
global	_start
_start:
	mov r8w, [n]					; r8w = n = number of rows
	mov r9w, [m]					; r9w = m = number of columns
	cmp r8w, 1						; check if n == 1
	jle exit						; if rows <= 1 exit
	
	xor ecx, ecx					; rcx unused bits is 0
	mov cx, r8w						; cx = n = number of rows
	mov rbx, matrix					; rbx = matrix
	mov r10, min					; r10 = min
	xor r11d, r11d					; r11d - index of current row

find_min:
	xor edi, edi					; edi - local index in row
	mov ax, [rbx]					; ax - first element in the row
	push rcx						; save number of rows
	mov cx, r9w						; cx = m = number of columns
	dec cx							; make cx zero-based
	jecxz store_min					; if cx == 0 write result in min array

next_element:
	inc di		       				; move to the next row element
	cmp ax, [rbx+rdi*2]   			; compare min with current
	cmovg ax, [rbx+rdi*2]  			; if min greater than current - replace 
	loop next_element       		; check all elements in row

store_min:
	mov [r10+r11*2], ax     		; store min element in min array
	inc r11w						; increment current row index
	lea rbx, [rbx + r9*2]   		; move rbx to the next row in matrix 
	pop rcx		        			; restore the number of rows
	loop find_min	        		; check all columns

	xor ebx, ebx					; ebx = 0
	mov cx, r8w 					; ecx = n = number of rows
	dec cx							; make ecx zero-based

main_sort_loop:
	mov r12b, 1						; set flag sorted = true
	mov r13b, 1						; set flag isOddLoop = true
	xor edi, edi					; edi - index in inner loop

odd_loop:
	mov ax, [r10+rdi*2]				; ax = min[rdi]
	mov dx, [r10+rdi*2+2]			; dx = min[rdi+1]
	cmp ax, dx						; if min[rdi] > min[rdi+1]
	%ifidni SORT_ORDER, ASC
	jg swap                 		; swap rdi and rdi+1 matrix rows
	%else
	jl swap							; swap rdi and rdi+1 matrix rows
	%endif

next_iter_odd_loop:	
	add di, 2               		; di += 2
	cmp cx, di						; if n-1 > index
	jg odd_loop						; continue
	mov di, 1						; index in inner loop starts with 1
	xor r13b, r13b					; set flag isOddLoop = false

even_loop:
	mov ax, [r10+rdi*2]				; ax = min[rdi]
	mov dx, [r10+rdi*2+2]			; dx = min[rdi+1]
	cmp ax, dx						; if min[rdi] > min[rdi+1]
	%ifidni SORT_ORDER, ASC
	jg swap                 		; swap rdi and rdi+1 matrix rows
	%else
	jl swap							; swap rdi and rdi+1 matrix rows
	%endif

next_iter_even_loop:
	add di, 2               		; di += 2
	cmp cx, di						; if n-1 > index
    jg even_loop            		; continue
	or r12w, r12w					; check sorted flag
	jz main_sort_loop				; if sorted = false continue sorting
	jmp exit						; skip swapping not in a loop

swap:
    mov [r10+rdi*2], dx				; min[rdi] = min[rdi+1]
	mov [r10+rdi*2+2], ax			; min[rdi+1] = min[rdi]
	xor r12b, r12b					; set flag sorted = false
	push rcx						; save ecx
	mov cx, r9w						; cx = m = number of rows
	mov r14w, r9w					; r14 = m = offset
	imul r14w, di					; r14 = m * index of swapping row
	shl r14w, 1						; r14 *= 2 because of shorts

swap_rows_loop:
	mov ax, [matrix+r14] 	        ; ax = matrix[rdi][rcx]
	mov dx, [matrix+r14+r9*2]       ; dx = matrix[rdi+1][rcx]
	mov [matrix+r14], dx            ; matrix[rdi][rcx] = matrix[rdi+1][rcx]
	mov [matrix+r14+r9*2], ax       ; matrix[rdi+1][rcx] = matrix[rdi][rcx]
	; shift offset to the next item
    add r14w, 2		        		; equals to '+rcx*4' in previous lines
	loop swap_rows_loop	        	; check all rows
	pop rcx			        		; restore rcx
	or r13b, r13b		        	; check isOddLoop flag
	jz next_iter_even_loop	        ; if isOddLoop = false go to the even loop
	jmp next_iter_odd_loop          ; else to the odd loop

exit:	
	mov	eax, 60
	mov edi, 0
	syscall
