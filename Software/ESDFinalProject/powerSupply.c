/*
 * powerSupply.c
 *
 *  Created on: Nov 23, 2019
 *      Author: Jerome
 */

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdint.h>
#include <stdbool.h>
#include "powerPWM.h"
#include "adc.h"

#define DESIRED_VOLTAGE     10.0
#define DIV_RATIO           0.1760
#define V_FEEDBACK          (DESIRED_VOLTAGE * DIV_RATIO)
#define REF_VOLTAGE         (V_FEEDBACK / 0.000153)         //counts


extern bool changeDutyCycleFlag;

void initPowerSupply(void) {

    initPowerPWM();
    //Port10.0 thru Port10.5 used for debug.

    //Turn Off Linear Regulator - I have concerns about the Linear regulator working properly
    //      Need to be careful about using this.  For now, keep output voltage constant.
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0 );
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0 );

}

void servicePowerSupply (void) {
    if (changeDutyCycleFlag) {
        if (getVoltage(battV) < REF_VOLTAGE ) {
            decrementDutyCycle();
        } else {
            incrementDutyCycle();
        }
        changeDutyCycleFlag = false;
    }
}
