PAGE_OFFSET = 0xC0000000;
ENTRY (start)
SECTIONS{
    . =  0x00100000;
    .text.multiboot : 
    {
    	*(.text.multiboot)
    }
   
    . +=  PAGE_OFFSET;

    .data : AT(ADDR(.data) - PAGE_OFFSET)
    {
        *(.data)
    }

    .text ALIGN (0x1000) : AT(ADDR(.text) - PAGE_OFFSET)
    {
        *(.text)
    }



    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - PAGE_OFFSET)
    {
        *(.rodata)
    }


    .bss :  AT(ADDR(.bss) - PAGE_OFFSET)
    {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
}
