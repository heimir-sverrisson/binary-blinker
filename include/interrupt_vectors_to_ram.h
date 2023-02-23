/*
 * interrupt_vectors_to_ram.h
 *
 * Heimir Thor Sverrisson, w1ant, heimir.sverrisson@gmail.com, February 2023
 *
 * Fill the the SRAM interrupt table with current interrupt service routines.
 *
 * This method is described in TI Application Note spna236 - March 2017
 *
 */

#ifndef __INTERRUPT_VECTORS_TO_RAM_H__
#define __INTERRUPT_VECTORS_TO_RAM_H__

#include "hal_stdtypes.h"

typedef enum {
    ENTRY_UNDEF_ABORT,
    ENTRY_SWI,
    ENTRY_PREFETCH_ABORT,
    ENTRY_DATA_ABORT
} tramTabEntry;

uint32_t ramTabChangeEntry(tramTabEntry, void*);

__attribute__((interrupt( "UDEF" ) ))         void undef_handler( void );
__attribute__((interrupt( "SWI" ) ))          void swi_handler( void );
__attribute__((interrupt( "PABT" ) ))         void pabt_handler( void );
__attribute__((interrupt( "DABT" ) ))         void dabt_handler( void );

// Exception handlers
void undef_handler(void);
void swi_handler(void);
void pabt_handler(void);
void dabt_handler(void);


#endif
