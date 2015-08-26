.globl addtwo
addtwo:
        pushl %ebp             
        movl  %esp, %ebp       
        
        pushl %ebx             
        pushl %ecx

        movl   8(%ebp), %ebx   
        movl  12(%ebp), %ecx

        addl  %ecx, %ebx

        movl  %ebx, -4(%ebp)   
        movl  -4(%ebp), %eax   

        popl  %ebp

        ret