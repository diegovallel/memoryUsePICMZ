/* 
 * File:   I2C.h
 * Author: FING150628
 *
 * Created on June 10, 2015, 10:17 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif



#include "init.h"


    /** ****************************************************************************
     ** ************ IIC CONFIG ****************************************************
     ** ****************************************************************************/


    // define para baudRate
#define I2C_BAUD_RATE_2                 400000        // FSCK
#define I2C_BRG_VAL_2                   0x5A          // I2CxBRG = ((1/(2*FSCK)-TPGD)*FCY)-2     // TPGD = 104ns   para 40kHz = 90 = 0x5A



#define I2C2_ENABLE()                   I2C2CONbits.ON = 1; //habilita el modulo I2C
#define I2C2_DISABLE()                  I2C2CONbits.ON = 0; //habilita el modulo I2C

#define I2C2_RX_ENABLE()                I2C2CONbits.RCEN = 1 // habilita la recepcion por el IIC

#define I2C2_ACK()                      I2C2CONbits.ACKDT = 0 // ACK is sent
#define I2C2_NACK()                     I2C2CONbits.ACKDT = 1 // NACK is sent
#define I2C2_ACKEN()                    I2C2CONbits.ACKEN = 1 // ACK is enabled

#define I2C2_START()                    I2C2CONbits.SEN = 1 // initiate start condition controled by IIC module
#define I2C2_RESTART()                  I2C2CONbits.RSEN = 1 // initiate restart condition controled by IIC module
#define I2C2_STOP()                     I2C2CONbits.PEN = 1 // initiate stop condition controled by IIC module


#define IIC_WRITE_MASK                  0xFE
#define IIC_READ_MASK                   0x01


    /** ****************************************************************************
     ** ************ IIC FUNCTIONS *************************************************
     ** ****************************************************************************/


    void I2C2_Init(void);
    void I2C2_Com(unsigned char _devAddr, unsigned char _memAddr, unsigned char _dataTx,
            unsigned char _dataRx, unsigned char *_Tx, unsigned char *_Rx);
    // void __attribute__((interrupt(ipl5), vector(_I2C_2_VECTOR)))_I2C2InterruptHandler(void);
    void I2C2TX_ISR(void);
    void I2C2RX_ISR(void);



    /** ****************************************************************************
     ** **************** FLAGS *****************************************************
     ** ****************************************************************************/
    // Bits con el fin de manejar diversas banderas del I2C

    enum { // Enum states
        IIC_Idle,
        IIC_Start,
        IIC_Restart,
        IIC_Stop,
        IIC_Ack,
        IIC_Nack,
        IIC_WriteDevAddr,
        IIC_ReadDevAddr,
        IIC_MemAddr,
        IIC_WriteData,
        IIC_ReadData
    };



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

