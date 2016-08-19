
ENTRY (start)
SECTIONS{
    . =  0x00100000;
    .text.multiboot : 
    {
    	*(.text.multiboot)
    }
   
    . +=  0xC0000000;

    .data : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    .text ALIGN (0x1000) : AT(ADDR(.text) - 0xC0000000)
    {
        *(.text)
    }



    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata)
    }


    .bss :  AT(ADDR(.bss) - 0xC0000000)
    {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
}
