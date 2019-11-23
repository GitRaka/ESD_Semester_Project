//timer_a_updown_compare_multiple_pwm.c


/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************/

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "powerPWM.h"

/* Application Defines */
#define TIMER_PERIOD 1200
#define DUTY_CYCLE_N (TIMER_PERIOD-840)
#define DUTY_CYCLE_P (DUTY_CYCLE_N-50)

/* Timer_A UpDown Configuration Parameter */
const Timer_A_UpDownModeConfig upDownConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock SOurce
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // SMCLK/1 = 3MHz
        TIMER_PERIOD,                           // 127 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value

};

/* Timer_A Compare Configuration Parameter  (PWM1) */
const Timer_A_CompareModeConfig compareConfig_PWM1 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output
        DUTY_CYCLE_N
};

/* Timer_A Compare Configuration Parameter (PWM2) */
const Timer_A_CompareModeConfig compareConfig_PWM2 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output
        DUTY_CYCLE_P
};

/* Timer_A Compare Configuration Parameter (PWM3) */
const Timer_A_CompareModeConfig compareConfig_PWM3 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output
        0
};

/* Timer_A Compare Configuration Parameter (PWM4) */
const Timer_A_CompareModeConfig compareConfig_PWM4 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR4
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output
        0
};

void initPowerPWM(void) {

    /* Configuring GPIO2.4 as peripheral output for PWM  and P6.7 for button
     * interrupt */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, \
                                                GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, \
                                                GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring Timer_A to have a period of approximately 500ms and
     * an initial duty cycle of 10% of that (3200 ticks)  */
    MAP_Timer_A_configureUpDownMode(TIMER_A0_BASE, &upDownConfig);
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);

    /* Initialize compare registers to generate PWM1 */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM1);

    /* Initialize compare registers to generate PWM2 */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM2);

}
