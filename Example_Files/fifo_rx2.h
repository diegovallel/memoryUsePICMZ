/* 
 * File:   fifo_rx2.h
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

#ifndef FIFO_RX2_H
#define	FIFO_RX2_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "init.h"

    /** ****************************************************************************
     ** ************ FIFO RX CONFIG ************************************************
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
#define FIFO_INIT                   Fifo_Rx_Init
#define FIFO_PUT                    Fifo_Rx_Put
#define FIFO_GET                    Fifo_Rx_Get


    /** ****************************************************************************
     ** ************ FIFO RX FUNCTIONS *********************************************
     ** ****************************************************************************/

    void Fifo_Rx2_Init(void);
    volatile unsigned char Fifo_Rx2_Put(volatile unsigned char);
    volatile unsigned char Fifo_Rx2_Get(volatile unsigned char*);



#ifdef	__cplusplus
}
#endif

#endif	/* FIFO_RX2_H */

