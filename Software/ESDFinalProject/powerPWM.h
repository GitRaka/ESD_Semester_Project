/*
 * Name: powerPWM.h
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

#ifndef POWERPWM_H_
#define POWERPWM_H_

/*
 *  Function Name: initPowerPWM
 *  Function Description: Initializes the power supply PWM signals
 *  Inputs:  none
 *  Outputs: none
 *  Author: Jerome Hittle
 *  Last updated: 11/25/2019
 */
void initPowerPWM(void);

/*
 *  Function Name: turnOffPowerSupply
 *  Function Description: Turns off all of the switches on the power supply
 *  Inputs:  none
 *  Outputs: none
 *  Author: Jerome Hittle
 *  Last updated: 12/4/2019
 */
void turnOffPowerSupply (void);

/*
 *  Function Name: incrementBoostDutyCycle
 *  Function Description: Increments the duty cycle of the power supply in boost mode
 *      by one step of resolution.
 *  Inputs:  none
 *  Outputs: none
 *  Author: Jerome Hittle
 *  Last updated: 11/25/2019
 */
void incrementBoostDutyCycle(void);

/*
 *  Function Name: decrementBoostDutyCycle
 *  Function Description: Decrements the duty cycle of the power supply in boost mode
 *      by one step of resolution.
 *  Inputs:  none
 *  Outputs: Returns the current count of the duty cycle as a function of the period counts.
 *      example: if the period is 1200 counts and the nMOS count is 1150, returns 50.
 *  Author: Jerome Hittle
 *  Last updated: 11/25/2019
 */
uint16_t decrementBoostDutyCycle(void);

uint16_t incrementBuckDutyCycle(void);
void decrementBuckDutyCycle(void);


#endif /* POWERPWM_H_ */
