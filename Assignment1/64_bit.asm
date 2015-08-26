.globl addtwo
addtwo:
        pushq %rbp             
        movq  %rsp, %rbp       
        
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)

	movl	-20(%rbp), %ebx
	movl	-24(%rbp), %ecx

        addl  %ecx, %ebx

        movl  %ebx, -4(%rbp)   
        movl  -4(%rbp), %eax   

        popq  %rbp

        ret
