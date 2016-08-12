
ENTRY (start)
SECTIONS{
    . =  0x00100000;
    .setup : 
    {
    	*(.setup)
    }
   
    . +=  0xBFF00000;

    .data : AT(ADDR(.data) - 0xBFF00000)
    {
        *(.data)
    }

    .text ALIGN (0x1000) : AT(ADDR(.text) - 0xBFF00000)
    {
        *(.text)
    }



    .rodata ALIGN (0x1000) : AT(ADDR(.rodata) - 0xBFF00000)
    {
        *(.rodata)
    }


    .bss :  AT(ADDR(.bss) - 0xBFF00000)
    {
        _sbss = .;
        *(COMMON)
        *(.bss)
        _ebss = .;
    }
}
