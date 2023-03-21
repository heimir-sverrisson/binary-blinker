/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
*/

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "het.h"
#include "bl_run_target.h"

/* USER CODE END */

/* USER CODE BEGIN (2) */
#define DELAY_VALUE 10000000

#define PIN_RED 0
#define PIN_YELLOW 1
#define PIN_GREEN 2

void set_value(int pin, int value){
	if(value == 0){
		hetREG1->DOUT &= ~(1 << pin);
	} else {
		hetREG1->DOUT |= (1 << pin);
	}
}

int toggle(int value){
	return (value == 1) ? 0 : 1;
}

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
	int red;
	int yellow;
	int green;
    int i;
    int counter = 7;
    int restart_counter = 0;

	// All three pins are output
	hetREG1->DIR |= (1 << PIN_RED);
	hetREG1->DIR |= (1 << PIN_YELLOW);
	hetREG1->DIR |= (1 << PIN_GREEN);

    for(;;)
    {
    	red = counter & 0x1;
    	yellow = counter & 0x2;
    	green = counter & 0x4;
    	set_value(PIN_RED, red);
    	set_value(PIN_YELLOW, yellow);
    	set_value(PIN_GREEN, green);
    	for(i = DELAY_VALUE; i > 0; i--)
    		;
    	counter--;
    	counter = (counter == -1) ? 7 : counter;
    	if(++restart_counter > 16){
    	    set_target(FLASH_LOADER);
    		softReset();
    	}
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
