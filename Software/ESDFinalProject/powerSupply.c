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

//Nominal Output Voltage
#define DESIRED_VOLTAGE     10.0
#define DIV_RATIO           0.1760
#define V_FEEDBACK          (DESIRED_VOLTAGE * DIV_RATIO)
#define REF_VOLTAGE         (V_FEEDBACK / 0.000153)         //counts

//Input Voltage Shutdown thresholds
#define LO_VOLTAGE          7.0
#define LO_V_FEEDBACK       (LO_VOLTAGE * DIV_RATIO)
#define LO_V_TRIP           (LO_V_FEEDBACK / 0.000153)      //counts
#define HI_VOLTAGE          14.0
#define HI_V_FEEDBACK       (HI_VOLTAGE * DIV_RATIO)
#define HI_V_TRIP           (HI_V_FEEDBACK / 0.000153)      //counts

extern bool changeDutyCycleFlag;
extern bool adcBufferFull;

typedef enum powerSupplyState {
    START,
    BUCK,
    BOOST,
    PASS,
    SHUTDOWN
} POWER_SUPPLY_STATE;

volatile POWER_SUPPLY_STATE supplyState = START;

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
    supplyState = START;
    //supplyState = BUCK;
}

void servicePowerSupply (void) {
    int16_t diffV;
    static int16_t storeV;          //Stores the voltage when BOOST or BUCK states transition to PASS

    if (changeDutyCycleFlag & adcBufferFull) {
        //Check for valid input voltage
        if (getVoltage(saV) < LO_V_TRIP | getVoltage(saV) > HI_V_TRIP ) {
            turnOffPowerSupply();
            supplyState = SHUTDOWN;
        }

        switch (supplyState) {
        case START:
            turnOffPowerSupply();
            diffV = getVoltage(saV) - REF_VOLTAGE;  //Make best guess on which operation mode to go to
            if (diffV > 20) {
                supplyState = BUCK;
            } else if (diffV < -20) {
                supplyState = BOOST;
            } else {
                supplyState = PASS;
            }
            break;
        case BOOST:
            if ( getVoltage(battV) < REF_VOLTAGE ) {
                incrementBoostDutyCycle();
            } else {
                if (decrementBoostDutyCycle() == 0) {
                    storeV = getVoltage(saV);
                    supplyState = PASS;
                }
            }
            break;
        case BUCK:
            if ( getVoltage(battV) < REF_VOLTAGE ) {
                if (decrementBuckDutyCycle() == 0) {
                    storeV = getVoltage(saV);
                    supplyState = PASS;
                }
            } else {
                incrementBuckDutyCycle();
            }
            break;
        case PASS:
            passMode();
            diffV =  getVoltage(saV) - storeV;
            if (diffV > 100) {
                supplyState = BUCK;
            } else if (diffV < -100) {
                supplyState = BOOST;
            }
            break;
        case SHUTDOWN:
            break;
        }

        changeDutyCycleFlag = false;
    }
}
