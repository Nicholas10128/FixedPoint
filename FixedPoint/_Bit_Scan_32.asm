.code
_bsf_32 proc
	bsf eax, ecx
	ret
ret;
_bsf_32 endp

_bsr_32 proc
	bsr eax, ecx
	ret
ret;
_bsr_32 endp
END