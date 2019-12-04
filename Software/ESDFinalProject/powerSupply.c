/*
 * Name: powerSupply.c
 * Author: Jerome Hittle
 * Tools Used: Code Composer Studio 9.2.0
 * Leveraged Code:
 * Links:
 *
 * (c) j. hittle 2019 - All rights reserved.
 * This file may not be reused, shared, or copied without written permission
 *   of the author for any reason, except where applicable by law.  The
 *   author retains all rights to the intellectual property herein.
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

typedef enum powerSupplyState {
    START,
    BUCK,
    BOOST,
    PASS
} POWER_SUPPLY_STATE;

volatile POWER_SUPPLY_STATE supplyState = BOOST;

void initPowerSupply(void) {

    //Turn Off Linear Regulator - I have concerns about the Linear regulator working properly
    //      Need to be careful about using this.  For now, keep output voltage constant.
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0 );
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN0 );

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


    initPowerPWM();

}

void servicePowerSupply (void) {
    int16_t diffV;
    static int16_t storeV;
    if (changeDutyCycleFlag) {
        switch (supplyState) {
        case BOOST:
            if (getVoltage(battV) < REF_VOLTAGE ) {
                incrementBoostDutyCycle();
            } else {
                if (decrementBoostDutyCycle() == 0) {
                    //stopBoost();
                    storeV = getVoltage(saV);
                    supplyState = PASS;
                }
            }
            break;
        case BUCK:
            supplyState = PASS;
            break;
        case PASS:
            //
            diffV =  getVoltage(saV) - storeV;
            if (diffV > 100) {
                supplyState = BUCK;
            } else if (diffV < -100) {
                supplyState = BOOST;
            }
            break;
        }

        changeDutyCycleFlag = false;
    }
}
