/*
 * File:   fifo_tx3.c
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

/** ****************************************************************************
 ** ************ FIFO TX CONFIG ************************************************
 ** ****************************************************************************/
#include "fifo_tx3.h"


/** ****************************************************************************
 ** ************ VARIABLES *************************************************
 ** ****************************************************************************/
volatile static unsigned char Fifo[FIFO_SIZE];
volatile static unsigned char * GetPtr;
volatile static unsigned char * PutPtr;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: Fifo_Tx3_Init                                                         *
 * Desc: Initialize TX3 Fifo                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void Fifo_Tx3_Init(void) {

    GetPtr = &Fifo[0];
    PutPtr = &Fifo[0];
}

/*******************************************************************************
 * Name: Fifo_Tx3_Put                                                          *
 * Desc: Put Data in TX3 Fifo                                                  *
 * Parameter: volatile unsigned int c                                          *
 * Return: volatile unsigned int                                               *
 *******************************************************************************/
volatile unsigned char Fifo_Tx3_Put(volatile unsigned char c) {

    // Verificar si PUT no alcanzara GET y si no se lleno totalmente
    if (((PutPtr + 1) == GetPtr) || ((PutPtr - GetPtr) == (FIFO_SIZE - 1))) {
        // if ( ( (PutPtr + 1) == GetPtr) || ( (PutPtr == &Fifo[FIFO_SIZE - 1]) && (GetPtr == &Fifo[0]) ) )
        return (0); // Fifo llena
    } else {

        *PutPtr = c; // salvar dato en la cola

        // actualizar el apuntador, mirando si se debe ir al principio
        if (PutPtr == &Fifo[FIFO_SIZE - 1]) {

            PutPtr = &Fifo[0];
        } else {

            PutPtr++;
        }

        TX3_INTERRUPT_EN();

        return (1);
    }

}

/*******************************************************************************
 * Name: Fifo_Tx3_Get                                                          *
 * Desc: Get Data from TX3 Fifo                                                *
 * Parameter: volatile unsigned int* DataPtr                                   *
 * Return: volatile unsigned int                                               *
 *******************************************************************************/
volatile unsigned char Fifo_Tx3_Get(volatile unsigned char* DataPtr) {

    if (PutPtr == GetPtr) { // Verificar si la cola esta vacia

        return (0);
    } else {

        *DataPtr = *GetPtr;

        // actualizar apuntador
        if (GetPtr == &Fifo[FIFO_SIZE - 1]) {
            GetPtr = &Fifo[0];
        } else {

            GetPtr++;
        }

        return (1);
    }
}

