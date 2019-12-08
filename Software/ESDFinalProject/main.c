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
#include "lcd16x2_msp43x.h"
#include "i2c.h"
uint16_t data;

int main(void)
{
    /* Halting the watchdog */
    WDT_A_holdTimer();

    volatile uint16_t a;

    initSystemClocks();
    initPowerSupply();
    initADC();
    lcd16x2_Init();
    MAP_Interrupt_enableMaster();
    Print_Welcome();
    init_registers_ina219();
    //uint16_t recv_data = 0;
    read_register(0x00);
    uint16_t dat1 = data;


    read_register(0x05);
    uint16_t dat2 = data;
    //__delay_cycles(500000);

    read_register(0x00);
    dat2 = data;
    //__delay_cycles(500000);
//    uint16_t dat3 = data;
    lcd16x2_SetPosition(4,2);
            lcd16x2_PrintInt(dat1);          // convert and print integer - internal function (limited)
            lcd16x2_Wait(10);

            lcd16x2_SetPosition(4,8);
            lcd16x2_PrintInt(dat2);
    while (1)
    {
        serviceADC();
        servicePowerSupply();
        Print_ADC_Data();
    }
}
