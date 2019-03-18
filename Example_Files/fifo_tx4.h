/* 
 * File:   fifo_tx4.h
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

#ifndef FIFO_TX4_H
#define	FIFO_TX4_H

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

#define TX4_INTERRUPT_EN()           IEC2bits.U4TXIE = 1;
#define TX4_INTERRUPT_DI()           IEC2bits.U4TXIE = 0;

    /** ****************************************************************************
     ** ************ FIFO TX FUNCTIONS *********************************************
     ** ****************************************************************************/

    void Fifo_Tx4_Init(void);
    volatile unsigned char Fifo_Tx4_Put(volatile unsigned char);
    volatile unsigned char Fifo_Tx4_Get(volatile unsigned char*);



#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_TX4_H */

