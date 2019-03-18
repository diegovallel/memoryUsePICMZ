/* 
 * File:   SPI.h
 * Author: FING150628
 *
 * Created on January 28, 2015, 2:06 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "init.h"

    /** ****************************************************************************
     ** ************ SPI CONFIG ****************************************************
     ** ****************************************************************************/

#define USE_FIFO_SPI1                  FALSE


    // define de prescale
#define PRESCALE_SPI                   2


    // define para baudRate
#define SPI_BAUD_RATE_1                 10000000        // Max 12000000
#define SPI_BRG_VAL_1                   (FCY/PRESCALE_SPI/SPI_BAUD_RATE_1)-1


    // define para el chip select
#define CSI_DD                          TRISDbits.TRISD9                // Output RD9 (SDC_CS1 RD9)
#define CSI_D                           LATDbits.LATD9                  // PIN RD9 Select for CS1
#define CSI_OUTPUT()                    CSI_DD = OUTPUT
#define CSI_OFF()                       CSI_D = LOW                     // Deshabilita SPI Slave
#define CSI_ON()                        CSI_D = HIGH                    // Habilita SPI Slave


    // define para el chip select
#define CSE_DD                          TRISDbits.TRISD8                // Output RD9 (SDC_CS1 RD8)
#define CSE_D                           LATDbits.LATD8                  // PIN RD9 Select for CS1
#define CSE_OUTPUT()                    CSE_DD = OUTPUT
#define CSE_OFF()                       CSE_D = LOW                     // Deshabilita SPI Slave
#define CSE_ON()                        CSE_D = HIGH                    // Habilita SPI Slave


    // define para el SPI 1
#define SCK1_DD                         TRISDbits.TRISD10               // Output RD10 (SDC_SCK RD10)
#define SDI1_DD                         TRISCbits.TRISC4                // Input RC4 (SDC_SDI RC4)
#define SDO1_DD                         TRISDbits.TRISD0                // Output RD0 (SDC_SDO RD0)



#define PHASE                           HIGH
#define POLARITY                        LOW
#define SAMPLE                          LOW


#define INTERNAL_USB                    0                               // bandera para activar USB interna
#define EXTERNAL_USB                    1                               // bandera para activar USB externa

    /** ****************************************************************************
     ** ************ SPI FUNCTIONS *************************************************
     ** ****************************************************************************/

    void SPI1_Init(void);
    void SPI1_Config(unsigned int cpol, unsigned int cpha, unsigned int sample);
    void SPI1_Off(void);

    void SPI1_WriteData(unsigned int data, volatile unsigned int* _rx, unsigned char device);

    // void __attribute__((interrupt(ipl3), vector(_SPI_1_VECTOR)))_SPI1InterruptHandler(void);
    void SPI1TX_ISR(void);
    void SPI1RX_ISR(void);



#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

