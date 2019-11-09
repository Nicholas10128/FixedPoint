.code
_Div128_64 proc
	mov rax, rcx
	idiv r8
	mov [r9], rdx
	ret
ret;
_Div128_64 endp
END