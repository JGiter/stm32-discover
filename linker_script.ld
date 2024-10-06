ENTRY(_reset)

MEMORY {
  SRAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 64K
  CCMRAM (xrw)      : ORIGIN = 0x10000000, LENGTH = 16K
  FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 512K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS 
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
  } > FLASH

  /* The program code and other data goes into FLASH */
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

    /*. = ALIGN(4);*/
    /*_etext = .;        /* define a global symbols at end of code */*/
  } >FLASH

  .data : 
  {
    *(.data)
  } > SRAM
}



