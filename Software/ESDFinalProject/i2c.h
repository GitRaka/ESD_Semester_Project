/*
 * Name: i2c.h
 * Author: Rakesh Kumar
 * Tools Used: CCS
 * Leveraged Code:
 * Links:
 *
 */
#ifndef _I2C_H_
#define _I2C_H_

/* DriverLib Defines */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Defines */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Slave Address for I2C Slave */
#define SLAVE_ADDRESS       0x40
#define NUM_OF_REC_BYTES    1

/* Variables */
//const uint8_t TXData[] = {0x80,0x00,0x21,0x20,0x80,0x00,0x81};
//void read_register(uint8_t i2c_register, uint16_t data);
void read_register(uint8_t i2c_register);
void init_registers_ina219(void);

#endif /* _I2C_H_ */
