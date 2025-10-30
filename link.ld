/* File: fun_kernal/link.ld */
ENTRY(start)

SECTIONS
{
    . = 0x100000;

    .text :
    {
        /* This is the critical fix: */
        *(.multiboot_header)
        
        /* The rest of your code follows */
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}