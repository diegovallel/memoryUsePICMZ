/*
 * File:   SCI.c
 * Author: FING_150628
 *
 * Created on 18 de noviembre de 2015, 12:28 PM
 */

/** ****************************************************************************
 ** ************ SCI CONFIG ****************************************************
 ** ****************************************************************************/
#include "SCI.h"

// <editor-fold defaultstate="collapsed" desc="FIFOS_USE">

#if USE_FIFO_SCI1
#include "fifo_rx1.h"
#include "fifo_tx1.h"
#endif
#if USE_FIFO_SCI2
#include "fifo_rx2.h"
#include "fifo_tx2.h"
#endif
#if USE_FIFO_SCI3
#include "fifo_rx3.h"
#include "fifo_tx3.h"
#endif
#if USE_FIFO_SCI4
#include "fifo_rx4.h"
#include "fifo_tx4.h"
#endif
#if USE_FIFO_SCI5
#include "fifo_rx5.h"
#include "fifo_tx5.h"
#endif
#if USE_FIFO_SCI6
#include "fifo_rx6.h"
#include "fifo_tx6.h"
#endif
// </editor-fold>

/** ****************************************************************************
 ** ************ EXT VARIABLES *************************************************
 ** ****************************************************************************/
extern volatile STR_FLAGS _Events;
extern unsigned char DATO1;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: SCI1_Init                                                             *
 * Desc: Initialize SCI1 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
// <editor-fold defaultstate="collapsed" desc="SCI1_INIT">

void SCI1_Init(void) {


    /* Remmap Pins Register */
    CFGCONbits.IOLOCK = 0;
    U1RXPIN_DIR(); // 
    U1RXPIN_DEF(); // definicion de puerto de entrada
    U1TXPIN_DEF(); // definicion de puerto de salida
    CFGCONbits.IOLOCK = 1;

    /* Baud Rate */
    U1BRG = BRG_VAL_1;

    /* Control Register */
    U1MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U1MODEbits.BRGH = 1; // High Speed Enable
#endif
    U1MODEbits.PDSEL = 0; // 8 bits no parity
    U1MODEbits.STSEL = 0; // 1 stop bit

    U1MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U1MODEbits.IREN = 0; // encoder para infrarrojo desabilitado
    U1MODEbits.UEN = 0; // los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U1MODEbits.WAKE = 0; // no wake up
    U1MODEbits.LPBACK = 0; // no lookback mode
    U1MODEbits.RXINV = 0; // estado activo de rx es en alto


    /* Status Register */
    U1STAbits.UTXISEL = 0; // interrupcion cuando se transmite el caracter
    U1STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter


    /* Interrupt Config */
    IEC3bits.U1EIE = 1; // habilita la interrupcion por error
    IEC3bits.U1RXIE = 1; // habilita la interrupcion por recepcion
    IEC3bits.U1TXIE = 0; // deshabilita la interrupcion por transmision

    /* Interrupt Priority */
    IPC28bits.U1RXIP = 7; // prioridad de interrupcion 7
    IPC28bits.U1TXIP = 7; // prioridad de interrupcion 7
    IPC28bits.U1EIP = 7; // prioridad de interrupcion 7
    IPC28bits.U1RXIS = 1; // subprioridad de interrupcion 1
    IPC28bits.U1TXIS = 1; // subprioridad de interrupcion 1
    IPC28bits.U1EIS = 1; // subprioridad de interrupcion 1

    /* Transmition Reception Enabled */
    U1STAbits.UTXEN = 1; //habilita la transmision
    U1STAbits.URXEN = 1; //habilita la recepcion
    U1STAbits.OERR = 0;

    /* Control Register */
    U1MODEbits.ON = 1; // habilita el modulo UART

    /* Interrupt Flags */
    IFS3bits.U1EIF = 0; // habilita la interrupcion por error
    IFS3bits.U1RXIF = 0; // habilita la interrupcion por recepcion
    IFS3bits.U1TXIF = 0; // deshabilita la interrupcion por transmision

}
// </editor-fold>

/*******************************************************************************
 * Name: SCI1_SendChar                                                         *
 * Desc: Send Data SCI1 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI1_SendChar(int val) {

    U1TXREG = val;
    while (!U1STAbits.TRMT);

}

/*******************************************************************************
 * Name: SCI1_SendLoad                                                         *
 * Desc: Send Load SCI1 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI1_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI1_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: _U1InterruptHandler                                                   *
 * Desc: Interrupt SCI1 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/

void __attribute__((interrupt(ipl7AUTO), vector(_UART1_RX_VECTOR)))_U1RxInterruptHandler(void) {

    IFS3bits.U1RXIF = 0; // external interrupt SCI1 Rx flag reset

    U1RX_ISR();

}

void __attribute__((interrupt(ipl7AUTO), vector(_UART1_TX_VECTOR)))_U1TxInterruptHandler(void) {

    IFS3bits.U1TXIF = 0; // external interrupt SCI1 Tx flag reset

    U1TX_ISR();

}

void __attribute__((interrupt(ipl7AUTO), vector(_UART1_FAULT_VECTOR)))_U1ErInterruptHandler(void) {

    IFS3bits.U1EIF = 0; //borra la bandera de interrupcion por error

}

/*******************************************************************************
 * Name: _U1TXInterrupt                                                        *
 * Desc: Interrupt SCI1 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U1TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI1
    volatile unsigned char datoSCI1;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx1_Get(&datoSCI1) == 1) {
        // escribo dato en el registro de Tx.-
        U1TXREG = (volatile unsigned int) datoSCI1;
    } else {

        TX1_INTERRUPT_DI();
    }

#endif


}

/*******************************************************************************
 * Name: _U1RXInterrupt                                                        *
 * Desc: Interrupt SCI1 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U1RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI1
    volatile unsigned int datoSCI;

    datoSCI = U1RXREG;
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx1 = 1;
    } else { // si se recibio un dato

        if (!Fifo_Rx1_Put(datoSCI)) {
            // fl_Dummy_rx1 = 1;
            Fifo_Rx1_Init();
        }

        fl_proc_rx1 = TRUE;
    }

    U1STAbits.OERR = 0;
#else
    volatile unsigned int datoSCI;

    datoSCI = U1RXREG;

    if ((datoSCI == CHAR_NULL)) {

    } else {
        fl_proc_rx1 = 1;

        DATO1 = datoSCI;
    }

    U1STAbits.OERR = 0;
#endif

}





