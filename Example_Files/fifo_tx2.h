/* 
 * File:   fifo_tx2.h
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

#ifndef FIFO_TX2_H
#define	FIFO_TX2_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "init.h"

    /** ****************************************************************************
     ** ************ FIFO TX CONFIG ************************************************
     ** ****************************************************************************/

    // Tamano de la FIFO
#define FIFO_SIZE                   4800

    // elimina deficiones previas
#ifdef FIFO_INIT
#undef FIFO_INIT
#undef FIFO_PUT
#undef FIFO_GET
#endif

    // definicion del nombre de cada funcion
#define FIFO_INIT                   Fifo_Tx_Init
#define FIFO_PUT                    Fifo_Tx_Put
#define FIFO_GET                    Fifo_Tx_Get

#define TX2_INTERRUPT_EN()           IEC1bits.U2TXIE = 1;
#define TX2_INTERRUPT_DI()           IEC1bits.U2TXIE = 0;

    /** ****************************************************************************
     ** ************ FIFO TX FUNCTIONS *********************************************
     ** ****************************************************************************/

    void Fifo_Tx2_Init(void);
    volatile unsigned char Fifo_Tx2_Put(volatile unsigned char);
    volatile unsigned char Fifo_Tx2_Get(volatile unsigned char*);



#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_TX2_H */

