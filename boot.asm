; File: fun_kernal/boot.asm

[BITS 32]


section .multiboot_header
align 8
header_start:
    dd 0xE85250D6      ; Multiboot 2 magic number
    dd 0            
    dd header_end - header_start 
    dd -(0xE85250D6 + 0 + (header_end - header_start)) ; Checksum


    dw 0               
    dw 0              
    dd 8              
header_end:

; --- Boot Code ---
section .text
global start
extern kmain
extern gdt_ptr;

start:
    cli             
    
    ; Set up segments
    mov esp, 0x200000   
    call kmain
    lgdt [gdt_ptr]
    jmp 0x08:flush_cs
  
flush_cs:
    mov ax, 0x10         ; Data segment selector (0x10)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax   
hang:
    hlt
    jmp hang