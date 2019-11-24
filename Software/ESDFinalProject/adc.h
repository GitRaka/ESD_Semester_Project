/*
 * adc.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Jerome
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef enum adc_channel {
    battV,
    battI,
    A8,
    A9,
    A10,
    A11,
    A12,
    A13
} ADC_CHANNEL;

void initADC (void);
void serviceADC (void);
void startADCCapture (void);
uint16_t getVoltage (ADC_CHANNEL channel);




#endif /* ADC_H_ */
