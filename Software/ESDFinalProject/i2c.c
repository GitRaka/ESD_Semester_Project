/* Name: i2c.c
 * Author: Rakesh Kumar
 * Tools Used: CCS
 * Leveraged Code:  TI SimpleLink v3.30.00.13, MSP432P401R DriverLib Examples:
 *              msp432p401x_euscib0_i2c_master_multislave_MSP_EXP432P401R_nortos_ccs.c
 * Links:
 */

#include "i2c.h"

const uint8_t TXData[] = {0x80,0x00,0x7B,0xC7,0x80,0x00,0x81};
extern uint16_t data;
/* I2C Master Configuration Parameter */
// Baud rate selectable (100KBPS, 400KBPS)
#if 1
const eUSCI_I2C_MasterConfig i2cConfig =
{
        EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        //3000000,                                // SMCLK = 3MHz (default)
        48000000,                               //SMCLK = 48MHz
        EUSCI_B_I2C_SET_DATA_RATE_100KBPS,      // Desired I2C Clock of 100khz
        3,                                      // No byte counter threshold
        EUSCI_B_I2C_NO_AUTO_STOP                // No Autostop
};
#endif

//void read_register(uint8_t i2c_register, uint16_t data)
void read_register(uint8_t i2c_register)
{
    data = 0;
    //uint8_t temp_clr = 0;
    //MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE,TXData[1]);
    MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE,i2c_register);
    //MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, TXData[6]);
    ////////MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE, TXData[6]);
    while(!(EUSCI_B1->IFG & EUSCI_B_IFG_TXIFG0));
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;

    // Send the restart condition, read one byte, send the stop condition right away
    EUSCI_B1->CTLW0 &= ~(EUSCI_B_CTLW0_TR);
    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

    while(MAP_I2C_masterIsStartSent(EUSCI_B1_BASE));

    //EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
    while(!(EUSCI_B1->IFG & EUSCI_B_IFG_RXIFG0));
    //__delay_cycles(100000);
    //RXData = EUSCI_B1->RXBUF;
    data = EUSCI_B1->RXBUF;

    //__delay_cycles(100000);
    while(!(EUSCI_B1->IFG & EUSCI_B_IFG_RXIFG0));
    data = (data << 8);

    //Data available in this variable
    data |= EUSCI_B1->RXBUF;
    //__delay_cycles(900000);
//    while(!(EUSCI_B1->IFG & EUSCI_B_IFG_RXIFG0));
//    //__DELAY_CYCLES(100000);
//    //RXDATA = EUSCI_B1->RXBUF;
//    temp_clr = EUSCI_B1->RXBUF;
    //EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
}

void init_registers_ina219(void)
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
               GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
    /* Initializing I2C Master to SMCLK at 100khz with no autostop */
    MAP_I2C_initMaster(EUSCI_B1_BASE, &i2cConfig);

    /* Specify slave address */
    MAP_I2C_setSlaveAddress(EUSCI_B1_BASE, SLAVE_ADDRESS);

    /* Enable I2C Module to start operations */
    MAP_I2C_enableModule(EUSCI_B1_BASE);

    /* Making sure the last transaction has been completely sent out */
    //while (MAP_I2C_masterIsStopSent(EUSCI_B1_BASE));

    MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, TXData[0]);  // Start + 1Byte
    //MAP_I2C_master
    //MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, TXData[1]); // Poll for TXINT,Send 1Byte
    //MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, TXData[0]);  // Start + 1Byte

    //MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, TXData[1]);  // Start + 1Byte
    MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, TXData[2]);
    //        __delay_cycles(100);
    MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE, TXData[3]);

    ///////////////

    MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE, 0x85);  // Start + 1Byte

    MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, 0x10);

    MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE, 0x00);
}

