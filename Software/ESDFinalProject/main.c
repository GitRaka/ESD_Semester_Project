/*
 * main.c
 *
 *  Created on: Nov 21, 2019
 *      Author: Jerome
 */


/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "systemClocks.h"
#include "powerPWM.h"

int main(void)
{
    /* Halting the watchdog */
    WDT_A_holdTimer();

    initSystemClocks();
    initPowerPWM();


    while (1)
    {
        //MAP_PCM_gotoLPM0();
    }
}


