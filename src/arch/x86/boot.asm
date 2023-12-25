section .multiboot_header
    ; Multiboot macros defined by the specification
    align 4
    dd 0xE85250D6                  ; magic number
    dd 0x00000000                  ; flags
    dd - (0xE85250D6 + 0x00000000) ; checksum

section .text
    align 0x1000                   ; Align at 4KB boundary

    global start                   ; Make 'start' accessible from outside this file
    extern kernel_main             ; External reference to the kernel's C entry point

start:
    cli                            ; Clear interrupts
    mov ax, 0                      ; Data segment selector
    mov ds, ax                     ; Set data segment
    mov es, ax                     ; Set extra segment
    mov fs, ax                     ; Set more segments
    mov gs, ax

    mov ebp, 0                     ; Clear the base pointer
    mov esp, stack_space           ; Set the stack pointer to the stack space defined later

    ; Call the C kernel entry point
    call kernel_main

    ; If kernel_main returns, hang the system
hang:
    jmp hang                       ; Infinite loop

section .bss
resb 8192                         ; Reserve 8KB for the stack
stack_space:
