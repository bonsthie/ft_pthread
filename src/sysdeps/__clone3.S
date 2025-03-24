/* 
   Userspace implementation of __clone3 syscall wrapper.

   int __clone3(struct clone_args *cl_args, size_t cl_args_size, 
                int (*fn)(void *args), void *args)

   Parameters (userland ABI registers):
     rdi: cl_args
     rsi: cl_args_size
     rdx: fn
     rcx: args
*/

.text
.globl __clone3
.type __clone3, @function
.align 16

__clone3:
    .cfi_startproc
    endbr64
    movl $-1, %eax          # Default error value (EINVAL)

    test %rdx, %rdx         # fn pointer
    jz __syscall_error

    test %rdi, %rdi         # cl_args pointer
    jz __syscall_error

    mov %rcx, %r8           # Save 'args'

    movl $435, %eax         # clone3 syscall number
	.cfi_endproc
    syscall

    cmp $0, %rax
    jl __syscall_error
    je __start_thread
    ret

__start_thread:
	.cfi_startproc
	.cfi_undefined rip
    xorq %rbp, %rbp
    mov %r8, %rdi
    call *%rdx
    mov %rax, %rdi
    movl $60, %eax          # exit syscall number
    syscall

__syscall_error:
    ret
    .cfi_endproc

.section .note.GNU-stack,"",@progbits
