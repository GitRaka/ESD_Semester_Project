/*
 * systemClocks.h
 *
 *  Created on: Nov 21, 2019
 *      Author: Jerome
 */

#ifndef SYSTEMCLOCKS_H_
#define SYSTEMCLOCKS_H_


/* Function: initSystemClocks
 * Description: Initializes the onboard clocks as follows
 *      MCLK = 64kHz
 *      SMCLK = 48MHz <- Do NOT change this as power supply duty cycle
 *              depends on this frequency.
 * Inputs:  none
 * Outputs: none
 * Author:  J. Hittle
 * Last Updated: 11/21/2019
 */
void initSystemClocks(void);

#endif /* SYSTEMCLOCKS_H_ */
