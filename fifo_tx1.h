/* 
 * File:   fifo_tx1.h
 * Author: FING150628
 *
 * Created on 18 de noviembre de 2015, 12:28 PM
 */

#ifndef FIFO_TX1_H
#define	FIFO_TX1_H

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

#define TX1_INTERRUPT_EN()           IEC3bits.U1TXIE = 1;
#define TX1_INTERRUPT_DI()           IEC3bits.U1TXIE = 0;

    /** ****************************************************************************
     ** ************ FIFO TX FUNCTIONS *********************************************
     ** ****************************************************************************/

    void Fifo_Tx1_Init(void);
    volatile unsigned char Fifo_Tx1_Put(volatile unsigned char);
    volatile unsigned char Fifo_Tx1_Get(volatile unsigned char*);



#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_TX2_H */

