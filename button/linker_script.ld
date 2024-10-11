ENTRY(main)

MEMORY {
  SRAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 64K
  CCMRAM (xrw)      : ORIGIN = 0x10000000, LENGTH = 16K
  FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 512K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS 
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    /**(.glue_7)         /* glue arm to thumb code */*/
    /**(.glue_7t)        /* glue thumb to arm code */*/
    /**(.eh_frame)*/
    /**/
    /*KEEP (*(.init))*/
    /*KEEP (*(.fini))*/

    . = ALIGN(4);
    _etext = .;
  } >FLASH

  .data : 
  {
    *(.data)
  } > SRAM
}



