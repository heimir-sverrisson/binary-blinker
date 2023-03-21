/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
*/

/*                                                                            */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
/*
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FLASH0  (RX) : origin=0x00000020 length=0x000FFFE0
*/
    VECTORS (X)  : origin=0x00010100 length=0x00000040
    FLASH0  (RX) : origin=0x00010140 length=0x000EFEC0

	RUNTARGET (RW)  : origin=0x08000000 length=0x00000010
    STACKS  (RW)    : origin=0x08000010 length=0x000014F0
    RAM     (RW)    : origin=0x08001500 length=0x0001EAE0
    RAMVECTORS(RWX) : origin=0x0801FFE0 length=0x00000020

/* USER CODE BEGIN (2) */
/* USER CODE END */
}

/* USER CODE BEGIN (3) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
    .text    : {} > FLASH0 
    .const   : {} > FLASH0 
    .cinit   : {} > FLASH0
    .ovly    : {} > FLASH0
    .pinit   : {} > FLASH0
    .runTarget   : {} > RUNTARGET, type = NOINIT
    .bss     : {} > RAM
    .data    : {} > RAM
    .sysmem  : {} > RAM
    .ramIntvecs  : {} load=FLASH0, run=RAMVECTORS, palign=8, table(ram_undef)

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (6) */
/* USER CODE END */
/*----------------------------------------------------------------------------*/
