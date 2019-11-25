/*
 * ********* Fall 2019 ESD - Final Project *************
 * ********** Maximum Power Point Tracker **************
 * Name: main.c
 * Author: Jerome Hittle, Nitik Gupta, Rakesh Kumar
 * Tools Used: Code Composer Studio 9.2.0
 * Leveraged Code:
 * Links:
 *
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Local Includes */
#include "systemClocks.h"
#include "powerSupply.h"
#include "adc.h"


int main(void)
{
    /* Halting the watchdog */
    WDT_A_holdTimer();


    initSystemClocks();
    initPowerSupply();
    initADC();

    MAP_Interrupt_enableMaster();


    while (1)
    {
        serviceADC();
        servicePowerSupply();
    }
}
