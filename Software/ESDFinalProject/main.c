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
#include "powerSupply.h"
#include "adc.h"




int main(void)
{
    /* Halting the watchdog */
    WDT_A_holdTimer();

    //Port10.0 thru Port10.5 used for debug.
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P10,
                            GPIO_PIN0 |
                            GPIO_PIN1 |
                            GPIO_PIN2 |
                            GPIO_PIN3 |
                            GPIO_PIN4 |
                            GPIO_PIN5 );
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P10,
                            GPIO_PIN0 |
                            GPIO_PIN1 |
                            GPIO_PIN2 |
                            GPIO_PIN3 |
                            GPIO_PIN4 |
                            GPIO_PIN5 );

    initSystemClocks();
    initPowerSupply();
    initADC();

    MAP_Interrupt_enableMaster();


    while (1)
    {
        serviceADC();
    }
}
