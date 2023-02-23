/*
 * interrupt_vectors_to_ram.c
 *
 * Heimir Thor Sverrisson, w1ant, heimir.sverrisson@gmail.com, February 2023
 *
 * Fill the the SRAM interrupt table with current interrupt service routines.
 *
 * This method is described in TI Application Note spna236 - March 2017
 *
 */

#include <interrupt_vectors_to_ram.h>

// Exception handlers
void undef_handler(void){
	return;
}
void swi_handler(void){
	return;
}
void pabt_handler(void){
	return;
}
void dabt_handler(void){
    /* Note: The following sequence is definitely not safe to use, but it works for the sake of this example */
    /* We need to return the instruction after the one which caused the data abort to not end up in an endless loop.
     * A Data Abort Handler is usually written in Assembly to have full control over this behavior.
     * The following statement takes the top element from the Abort stack and adds 4 to it.
     * The top element is usually the saved LR, adding 4 will cause the handler to return to the next instruction.
     * This will only work if the instruction was an ARM instruction and if the compiler actually stored the LR on the top of the stack! */
	*(volatile uint32_t*)(0x08001400 - 4) += 4ul;
	return;
}

uint32_t ramTabChangeEntry(tramTabEntry sEntry, void* pHandlerAddress)
{
    extern volatile uint32 ram_tab_undef;
    extern volatile uint32 ram_tab_swi;
    extern volatile uint32 ram_tab_pref;
    extern volatile uint32 ram_tab_dabt;

    uint32_t ui32ReturnVal = 1ul;

    if (((void*)0) != pHandlerAddress)
    {
        __asm(" dsb");
        switch (sEntry)
        {
        case ENTRY_UNDEF_ABORT:
            ram_tab_undef = (uint32_t)(pHandlerAddress);
            ui32ReturnVal = 0ul; /* Pass */
            break;
        case ENTRY_SWI:
            ram_tab_swi = (uint32_t)(pHandlerAddress);
            ui32ReturnVal = 0ul; /* Pass */
            break;
        case ENTRY_PREFETCH_ABORT:
            ram_tab_pref = (uint32_t)(pHandlerAddress);
            ui32ReturnVal = 0ul; /* Pass */
            break;
        case ENTRY_DATA_ABORT:
            ram_tab_dabt = (uint32_t)(pHandlerAddress);
            ui32ReturnVal = 0ul; /* Pass */
            break;
        default:
            ui32ReturnVal = 3ul; /* Fail */
            break;
        }
        __asm(" dsb");
    }else{
        ui32ReturnVal = 2ul; /* Fail */
    }

    return ui32ReturnVal;
}
