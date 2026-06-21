global _start

extern kmain

section .text

bits 64

_start:
    call kmain

.hang:
    hlt
    jmp .hang

section .note.GNU-stack noalloc noexec nowrite progbits
