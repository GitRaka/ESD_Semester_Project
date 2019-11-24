/*
 * powerSupply.c
 *
 *  Created on: Nov 23, 2019
 *      Author: Jerome
 */

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

}

void servicePowerSupply (void) {
    if (changeDutyCycleFlag) {
        if (getVoltage(battV) < REF_VOLTAGE ) {
            incrementDutyCycle();
        } else {
            decrementDutyCycle();
        }
        changeDutyCycleFlag = false;
    }
}
