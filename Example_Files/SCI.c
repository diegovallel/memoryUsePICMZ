/*
 * File:   SCI.c
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

/** ****************************************************************************
 ** ************ SCI CONFIG ****************************************************
 ** ****************************************************************************/
#include "SCI.h"

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


/** ****************************************************************************
 ** ************ EXT VARIABLES *************************************************
 ** ****************************************************************************/
extern volatile STR_FLAGS _Events;
// extern unsigned char DATO1;
// extern unsigned char DATO2;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: SCI1_Init                                                             *
 * Desc: Initialize SCI1 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI1_Init(void) {


    /* Baud Rate */
    U1BRG = BRG_VAL_1;

    /* Registro de Control */
    U1MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U1MODEbits.BRGH = 1; // High Speed Enable
#endif
    U1MODEbits.PDSEL = 0; // 8 bits no parity
    U1MODEbits.STSEL = 0; // 1 stop bit

    U1MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U1MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    U1MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U1MODEbits.WAKE = 0; //no wake up
    U1MODEbits.LPBACK = 0; //no lookback mode
    U1MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U1STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U1STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI1
    //    IEC0bits.U1TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC0bits.U1TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC0bits.U1EIE = 1; //habilita la interrupcion por error
    IEC0bits.U1RXIE = 1; //habilita la interrupcion por recepcion
    IEC0bits.U1TXIE = 0; // deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC6bits.U1IP = 7; //prioridad interrupcion 5
    IPC6bits.U1IS = 1; //subprioridad 1

    IFS0bits.U1RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS0bits.U1TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U1MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U1STAbits.UTXEN = 1; //habilita la transmision
    U1STAbits.URXEN = 1; //habilita la recepcion

}

/*******************************************************************************
 * Name: SCI2_Init                                                             *
 * Desc: Initialize SCI2 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI2_Init(void) {


    /* Baud Rate */
    U2BRG = BRG_VAL_2;

    /* Registro de Control */
    U2MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U2MODEbits.BRGH = 1; // High Speed Enable
#endif
    U2MODEbits.PDSEL = 0; // 8 bits no parity
    U2MODEbits.STSEL = 0; // 1 stop bit

    U2MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U2MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    U2MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U2MODEbits.WAKE = 0; //no wake up
    U2MODEbits.LPBACK = 0; //no lookback mode
    U2MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U2STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U2STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI2
    //    IEC1bits.U2TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC1bits.U2TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC1bits.U2EIE = 1; //habilita la interrupcion por error
    IEC1bits.U2RXIE = 1; //habilita la interrupcion por recepcion
    IEC1bits.U2TXIE = 0; //deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC8bits.U2IP = 7; //prioridad interrupcion 5
    IPC8bits.U2IS = 1; //subprioridad 1

    IFS1bits.U2RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS1bits.U2TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U2MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U2STAbits.UTXEN = 1; //habilita la transmision
    U2STAbits.URXEN = 1; //habilita la recepcion

}

/*******************************************************************************
 * Name: SCI3_Init                                                             *
 * Desc: Initialize SCI3 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI3_Init(void) {


    /* Baud Rate */
    U3BRG = BRG_VAL_3;

    /* Registro de Control */
    U3MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U3MODEbits.BRGH = 1; // High Speed Enable
#endif
    U3MODEbits.PDSEL = 0; // 8 bits no parity
    U3MODEbits.STSEL = 0; // 1 stop bit

    U3MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U3MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    U3MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U3MODEbits.WAKE = 0; //no wake up
    U3MODEbits.LPBACK = 0; //no lookback mode
    U3MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U3STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U3STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI3
    //    IEC1bits.U3TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC1bits.U3TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC1bits.U3EIE = 1; //habilita la interrupcion por error
    IEC1bits.U3RXIE = 1; //habilita la interrupcion por recepcion
    IEC1bits.U3TXIE = 0; //deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC7bits.U3IP = 7; //prioridad interrupcion 5
    IPC7bits.U3IS = 1; //subprioridad 1

    IFS1bits.U3RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS1bits.U3TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U3MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U3STAbits.UTXEN = 1; //habilita la transmision
    U3STAbits.URXEN = 1; //habilita la recepcion

}

/*******************************************************************************
 * Name: SCI4_Init                                                             *
 * Desc: Initialize SCI4 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI4_Init(void) {


    /* Baud Rate */
    U4BRG = BRG_VAL_4;

    /* Registro de Control */
    U4MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U4MODEbits.BRGH = 1; // High Speed Enable
#endif
    U4MODEbits.PDSEL = 0; // 8 bits no parity
    U4MODEbits.STSEL = 0; // 1 stop bit

    U4MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U4MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    // U4MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U4MODEbits.WAKE = 0; //no wake up
    U4MODEbits.LPBACK = 0; //no lookback mode
    U4MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U4STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U4STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI4
    //    IEC2bits.U4TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC2bits.U4TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC2bits.U4EIE = 1; //habilita la interrupcion por error
    IEC2bits.U4RXIE = 1; //habilita la interrupcion por recepcion
    IEC2bits.U4TXIE = 0; //deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC12bits.U4IP = 7; //prioridad interrupcion 5
    IPC12bits.U4IS = 1; //subprioridad 1

    IFS2bits.U4RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS2bits.U4TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U4MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U4STAbits.UTXEN = 1; //habilita la transmision
    U4STAbits.URXEN = 1; //habilita la recepcion

}

/*******************************************************************************
 * Name: SCI5_Init                                                             *
 * Desc: Initialize SCI5 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI5_Init(void) {


    /* Baud Rate */
    U5BRG = BRG_VAL_5;

    /* Registro de Control */
    U5MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U5MODEbits.BRGH = 1; // High Speed Enable
#endif
    U5MODEbits.PDSEL = 0; // 8 bits no parity
    U5MODEbits.STSEL = 0; // 1 stop bit

    U5MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U5MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    // U5MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U5MODEbits.WAKE = 0; //no wake up
    U5MODEbits.LPBACK = 0; //no lookback mode
    U5MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U5STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U5STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI5
    //    IEC2bits.U5TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC2bits.U5TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC2bits.U5EIE = 1; //habilita la interrupcion por error
    IEC2bits.U5RXIE = 1; //habilita la interrupcion por recepcion
    IEC2bits.U5TXIE = 0; //deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC12bits.U5IP = 5; //prioridad interrupcion 5
    IPC12bits.U5IS = 1; //subprioridad 1

    IFS2bits.U5RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS2bits.U5TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U5MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U5STAbits.UTXEN = 1; //habilita la transmision
    U5STAbits.URXEN = 1; //habilita la recepcion

}

/*******************************************************************************
 * Name: SCI6_Init                                                             *
 * Desc: Initialize SCI6 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SCI6_Init(void) {


    /* Baud Rate */
    U6BRG = BRG_VAL_6;

    /* Registro de Control */
    U6MODEbits.ABAUD = 0; // autobaud disable
#if HIGH_SPEED
    U6MODEbits.BRGH = 1; // High Speed Enable
#endif
    U6MODEbits.PDSEL = 0; // 8 bits no parity
    U6MODEbits.STSEL = 0; // 1 stop bit

    U6MODEbits.SIDL = 0; // operacion continua en modo habilitado
    U6MODEbits.IREN = 0; //encoder para infrarrojo desabilitado
    // U6MODEbits.UEN = 0; //los pines u1tx y u1rx habilitados y controlados; uxcts y uxrts/uxbclk controlados por el puerto
    U6MODEbits.WAKE = 0; //no wake up
    U6MODEbits.LPBACK = 0; //no lookback mode
    U6MODEbits.RXINV = 0; //estado activo de rx es en alto


    /* Registro de Status */
    U6STAbits.UTXISEL = 1; // interrupcion cuando se transmite el caracter
    U6STAbits.URXISEL = 0; // interrupcion cuando se recibe el caracter

    //#if USE_FIFO_SCI6
    //    IEC2bits.U6TXIE = 1; // Interruption Tx Enabled SCI1
    //#else
    //    IEC2bits.U6TXIE = 0; // Interruption Tx Disabled SCI1
    //#endif

    /* Configuracion de las interrupciones */
    IEC2bits.U6EIE = 1; //habilita la interrupcion por error
    IEC2bits.U6RXIE = 1; //habilita la interrupcion por recepcion
    IEC2bits.U6TXIE = 0; //deshabilita la interrupcion por transmision


    //prioridad de interrupciones
    IPC12bits.U6IP = 7; //prioridad interrupcion 5
    IPC12bits.U6IS = 1; //subprioridad 1

    IFS2bits.U6RXIF = 0; // Clear Interruption Rx Flag SCI1
    IFS2bits.U6TXIF = 0; // Clear Interruption Tx Flag SCI1


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    U6MODEbits.ON = 1; //habilita el modulo UART


    /* Habilita la transmision y recepcion */
    U6STAbits.UTXEN = 1; //habilita la transmision
    U6STAbits.URXEN = 1; //habilita la recepcion

}

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
 * Name: SCI2_SendChar                                                         *
 * Desc: Send Data SCI2 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI2_SendChar(int val) {

    U2TXREG = val;
    while (!U2STAbits.TRMT);

}

/*******************************************************************************
 * Name: SCI3_SendChar                                                         *
 * Desc: Send Data SCI3 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI3_SendChar(int val) {

    U3TXREG = val;
    while (!U3STAbits.TRMT);

}

/*******************************************************************************
 * Name: SCI4_SendChar                                                         *
 * Desc: Send Data SCI4 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI4_SendChar(int val) {

    U4TXREG = val;
    while (!U4STAbits.TRMT);

}

/*******************************************************************************
 * Name: SCI5_SendChar                                                         *
 * Desc: Send Data SCI5 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI5_SendChar(int val) {

    U5TXREG = val;
    while (!U5STAbits.TRMT);

}

/*******************************************************************************
 * Name: SCI6_SendChar                                                         *
 * Desc: Send Data SCI6 Module                                                 *
 * Parameter: val                                                              *
 * Return: None                                                                *
 *******************************************************************************/
void SCI6_SendChar(int val) {

    U6TXREG = val;
    while (!U6STAbits.TRMT);

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
 * Name: SCI2_SendLoad                                                         *
 * Desc: Send Load SCI2 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI2_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI2_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: SCI3_SendLoad                                                         *
 * Desc: Send Load SCI3 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI3_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI3_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: SCI4_SendLoad                                                         *
 * Desc: Send Load SCI4 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI4_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI4_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: SCI5_SendLoad                                                         *
 * Desc: Send Load SCI5 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI5_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI5_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: SCI6_SendLoad                                                         *
 * Desc: Send Load SCI6 Module                                                 *
 * Parameter: *load, len                                                       *
 * Return: None                                                                *
 *******************************************************************************/
void SCI6_SendLoad(char* load, int len) {

    int i;

    for (i = 0; i < len; i++) {
        SCI6_SendChar(load[i]);
    }

}

/*******************************************************************************
 * Name: _U1InterruptHandler                                                   *
 * Desc: Interrupt SCI1 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl7AUTO), vector(_UART_1_VECTOR)))_U1InterruptHandler(void) {
    if (IFS0bits.U1TXIF == 1) {//si hubo interrupcion por transmision

        IFS0bits.U1TXIF = 0; // external interrupt SCI1 Tx flag reset

        U1TX_ISR();

    }
    if (IFS0bits.U1RXIF == 1) { //si hubo interrupcion por recepcion

        IFS0bits.U1RXIF = 0; // external interrupt SCI1 Rx flag reset

        U1RX_ISR();

    }
    if (IFS0bits.U1EIF == 1) { //si hubo interrupcion por error
        IFS0bits.U1EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _U2InterruptHandler                                                   *
 * Desc: Interrupt SCI2 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl7AUTO), vector(_UART_2_VECTOR)))_U2InterruptHandler(void) {
    if (IFS1bits.U2TXIF == 1) {//si hubo interrupcion por transmision

        IFS1bits.U2TXIF = 0; // external interrupt SCI1 Tx flag reset

        U2TX_ISR();

    }
    if (IFS1bits.U2RXIF == 1) { //si hubo interrupcion por recepcion

        IFS1bits.U2RXIF = 0; // external interrupt SCI1 Rx flag reset

        U2RX_ISR();

    }
    if (IFS1bits.U2EIF == 1) { //si hubo interrupcion por error
        IFS1bits.U2EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _U3InterruptHandler                                                   *
 * Desc: Interrupt SCI3 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl7AUTO), vector(_UART_3_VECTOR)))_U3InterruptHandler(void) {
    if (IFS1bits.U3TXIF == 1) {//si hubo interrupcion por transmision

        IFS1bits.U3TXIF = 0; // external interrupt SCI1 Tx flag reset

        U3TX_ISR();

    }
    if (IFS1bits.U3RXIF == 1) { //si hubo interrupcion por recepcion

        IFS1bits.U3RXIF = 0; // external interrupt SCI1 Rx flag reset

        U3RX_ISR();

    }
    if (IFS1bits.U3EIF == 1) { //si hubo interrupcion por error
        IFS1bits.U3EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _U4InterruptHandler                                                   *
 * Desc: Interrupt SCI4 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl7AUTO), vector(_UART_4_VECTOR)))_U4InterruptHandler(void) {
    if (IFS2bits.U4TXIF == 1) {//si hubo interrupcion por transmision

        IFS2bits.U4TXIF = 0; // external interrupt SCI1 Tx flag reset

        U4TX_ISR();

    }
    if (IFS2bits.U4RXIF == 1) { //si hubo interrupcion por recepcion

        IFS2bits.U4RXIF = 0; // external interrupt SCI1 Rx flag reset

        U4RX_ISR();

    }
    if (IFS2bits.U4EIF == 1) { //si hubo interrupcion por error
        IFS2bits.U4EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _U5InterruptHandler                                                   *
 * Desc: Interrupt SCI5 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl5AUTO), vector(_UART_5_VECTOR)))_U5InterruptHandler(void) {
    if (IFS2bits.U5TXIF == 1) {//si hubo interrupcion por transmision

        IFS2bits.U5TXIF = 0; // external interrupt SCI1 Tx flag reset

        U5TX_ISR();

    }
    if (IFS2bits.U5RXIF == 1) { //si hubo interrupcion por recepcion

        IFS2bits.U5RXIF = 0; // external interrupt SCI1 Rx flag reset

        U5RX_ISR();

    }
    if (IFS2bits.U5EIF == 1) { //si hubo interrupcion por error
        IFS2bits.U5EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _U6InterruptHandler                                                   *
 * Desc: Interrupt SCI6 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl7AUTO), vector(_UART_6_VECTOR)))_U6InterruptHandler(void) {
    if (IFS2bits.U6TXIF == 1) {//si hubo interrupcion por transmision

        IFS2bits.U6TXIF = 0; // external interrupt SCI1 Tx flag reset

        U6TX_ISR();

    }
    if (IFS2bits.U6RXIF == 1) { //si hubo interrupcion por recepcion

        IFS2bits.U6RXIF = 0; // external interrupt SCI1 Rx flag reset

        U6RX_ISR();

    }
    if (IFS2bits.U6EIF == 1) { //si hubo interrupcion por error
        IFS2bits.U6EIF = 0; //borra la bandera de interrupcion por error
    }
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
    } else if (datoSCI == _CTR_CHAR_SCI1) { // si llego el caractr de control desde el modulo ECG (,)

        Fifo_Rx1_Put(datoSCI); // agrega la coma
        fl_proc_rx1 = TRUE; // se interpretan los datos recibidos
    } else if ((datoSCI >= 0x65 && datoSCI <= 0x69) || (datoSCI >= 0x30 && datoSCI <= 0x39)) { // si son caracteres validos para la trama


        if (!Fifo_Rx1_Put(datoSCI)) {
            // fl_Dummy_rx1 = 1;
            Fifo_Rx1_Init();
        }

        // fl_proc_rx1 = 1;
    }

    U1STAbits.OERR = 0;
#else
    //    fl_SCI1 = 1;
    //
    //    DATO1 = U1RXREG;
#endif

}

/*******************************************************************************
 * Name: _U2TXInterrupt                                                        *
 * Desc: Interrupt SCI1 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U2TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI2
    volatile unsigned char datoSCI2;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx2_Get(&datoSCI2) == 1) {
        // escribo dato en el registro de Tx.-
        U2TXREG = (volatile unsigned char) datoSCI2;
    } else {

        TX2_INTERRUPT_DI();
    }

#endif

}

/*******************************************************************************
 * Name: _U2RXInterrupt                                                        *
 * Desc: Interrupt SCI1 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U2RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI2
    volatile unsigned int datoSCI;

    datoSCI = U2RXREG;
    // if ((datoSCI == _CTR_CHAR_SCI2) || (datoSCI == CHAR_NULL)) {
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx2 = 1;
    } else if (datoSCI == _CTR_CHAR_SCI2) { // si llego el caracter de control desde el modulo SPO (,)

        Fifo_Rx2_Put(datoSCI); // agrega la coma
        fl_proc_rx2 = TRUE; // se interpretan los datos recibidos
    } else  if ((datoSCI >= 0x65 && datoSCI <= 0x67) || (datoSCI >= 0x30 && datoSCI <= 0x39)) { // si son caracteres validos para la trama

        if (!Fifo_Rx2_Put(datoSCI)) {
            // fl_Dummy_rx2 = 1;
            Fifo_Rx2_Init();
        }
        // fl_proc_rx2 = 1;
    }

    U2STAbits.OERR = 0; // limpia la fifo interna

#else
    // fl_proc_rx2 = 1;

    volatile unsigned int datoSCI;

    datoSCI = U2RXREG;

    SCI2_SendChar(datoSCI);

    U2STAbits.OERR = 0;

#endif

}

/*******************************************************************************
 * Name: _U3TXInterrupt                                                        *
 * Desc: Interrupt SCI3 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U3TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI3
    volatile unsigned char datoSCI3;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx3_Get(&datoSCI3) == 1) {
        // escribo dato en el registro de Tx.-
        U3TXREG = (volatile unsigned char) datoSCI3;
    } else {

        TX3_INTERRUPT_DI();
    }

#endif

}

/*******************************************************************************
 * Name: _U3RXInterrupt                                                        *
 * Desc: Interrupt SCI3 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U3RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI3
    volatile unsigned int datoSCI;

    datoSCI = U3RXREG;
    // if ((datoSCI == _CTR_CHAR_SCI3) || (datoSCI == CHAR_NULL)) {
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx3 = 1;
    } else if (datoSCI == _CTR_CHAR_SCI3) { // si llego el caracter de control desde el modulo NIP (,)

        Fifo_Rx3_Put(datoSCI); // agrega la coma
        fl_proc_rx3 = TRUE; // se interpretan los datos recibidos
    } else  if ((datoSCI >= 0x65 && datoSCI <= 0x68) || (datoSCI >= 0x30 && datoSCI <= 0x39)) { // si son caracteres validos para la trama

        if (!Fifo_Rx3_Put(datoSCI)) {
            // fl_Dummy_rx3 = 1;
            Fifo_Rx3_Init();
        }
        // fl_proc_rx3 = 1;
    }

    U3STAbits.OERR = 0; // limpia la fifo interna

#else
    // fl_proc_rx3 = 1;

    volatile unsigned int datoSCI;

    datoSCI = U3RXREG;

    SCI3_SendChar(datoSCI);

    U3STAbits.OERR = 0;

#endif

}

/*******************************************************************************
 * Name: _U4TXInterrupt                                                        *
 * Desc: Interrupt SCI4 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U4TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI4
    volatile unsigned char datoSCI4;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx4_Get(&datoSCI4) == 1) {
        // escribo dato en el registro de Tx.-
        U4TXREG = (volatile unsigned char) datoSCI4;
    } else {

        TX4_INTERRUPT_DI();
    }

#endif

}

/*******************************************************************************
 * Name: _U4RXInterrupt                                                        *
 * Desc: Interrupt SCI4 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U4RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI4
    volatile unsigned int datoSCI;

    datoSCI = U4RXREG;
    // if ((datoSCI == _CTR_CHAR_SCI4) || (datoSCI == CHAR_NULL)) {
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx4 = 1;
//    } else if (datoSCI == _CTR_CHAR_SCI4) { // si llego el caracter de control desde el modulo RN171 (0x0A)
//
//        Fifo_Rx4_Put(datoSCI); // agrega la coma
//        fl_proc_rx4 = TRUE; // se interpretan los datos recibidos
//    } else if (datoSCI == _CTR_CHAR_SCI4_1) { // si llego el caracter de control desde el modulo RN171 (0x0A)
//
//        Fifo_Rx4_Put(datoSCI); // agrega la coma
//        fl_proc_rx4 = TRUE; // se interpretan los datos recibidos
//    } else if (datoSCI == _CTR_CHAR_SCI4_3) { // si llego el caracter de control desde el modulo RN171 (0x0A)
//
//        Fifo_Rx4_Put(datoSCI); // agrega la coma
//        fl_proc_rx4 = TRUE; // se interpretan los datos recibidos
//    } else if (datoSCI == _CTR_CHAR_SCI4_2) { // si llego el caracter de control desde el modulo RN171 (0x0A)
//
//        //        Fifo_Rx4_Put(datoSCI); // agrega la coma
//        //        fl_proc_rx4 = TRUE; // se interpretan los datos recibidos
    } else {

        if (!Fifo_Rx4_Put(datoSCI)) {
            // fl_Dummy_rx4 = 1;
            Fifo_Rx4_Init();
        }

//        if (fl_openPort) { // si el puerto esta abierto
            fl_proc_rx4 = TRUE;
//        }
    }

    U4STAbits.OERR = 0; // limpia la fifo interna

#else
    // fl_proc_rx4 = 1;

    volatile unsigned int datoSCI;

    datoSCI = U4RXREG;

    SCI4_SendChar(datoSCI);

    U4STAbits.OERR = 0;

#endif

}

/*******************************************************************************
 * Name: _U5TXInterrupt                                                        *
 * Desc: Interrupt SCI5 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U5TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI5
    volatile unsigned char datoSCI5;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx5_Get(&datoSCI5) == 1) {
        // escribo dato en el registro de Tx.-
        U5TXREG = (volatile unsigned char) datoSCI5;
    } else {

        TX5_INTERRUPT_DI();
    }

#endif

}

/*******************************************************************************
 * Name: _U5RXInterrupt                                                        *
 * Desc: Interrupt SCI5 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U5RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI5
    volatile unsigned int datoSCI;

    datoSCI = U5RXREG;
    // if ((datoSCI == _CTR_CHAR_SCI5) || (datoSCI == CHAR_NULL)) {
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx5 = 1;
    } else {

        if (!Fifo_Rx5_Put(datoSCI)) {
            // fl_Dummy_rx5 = 1;
            Fifo_Rx5_Init();
        }
        fl_proc_rx5 = 1;
    }

    U5STAbits.OERR = 0; // limpia la fifo interna

#else
    // fl_proc_rx5 = 1;

    volatile unsigned int datoSCI;

    datoSCI = U5RXREG;

    SCI5_SendChar(datoSCI);

    U5STAbits.OERR = 0;

#endif

}

/*******************************************************************************
 * Name: _U6TXInterrupt                                                        *
 * Desc: Interrupt SCI6 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U6TX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI6
    volatile unsigned char datoSCI6;

    // Intento sacar un dato de la FIFO para que se escriba en SCDR
    if (Fifo_Tx6_Get(&datoSCI6) == 1) {
        // escribo dato en el registro de Tx.-
        U6TXREG = (volatile unsigned char) datoSCI6;
    } else {

        TX6_INTERRUPT_DI();
    }

#endif

}

/*******************************************************************************
 * Name: _U6RXInterrupt                                                        *
 * Desc: Interrupt SCI6 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void U6RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SCI6
    volatile unsigned int datoSCI;

    datoSCI = U6RXREG;
    // if ((datoSCI == _CTR_CHAR_SCI6) || (datoSCI == CHAR_NULL)) {
    if ((datoSCI == CHAR_NULL)) {
        // fl_proc_rx6 = 1;
    } else {

        if (!Fifo_Rx6_Put(datoSCI)) {
            // fl_Dummy_rx6 = 1;
            Fifo_Rx6_Init();
        }
        fl_proc_rx6 = 1;
    }

    U6STAbits.OERR = 0; // limpia la fifo interna

#else
    // fl_proc_rx6 = 1;

    volatile unsigned int datoSCI;

    datoSCI = U6RXREG;

    SCI6_SendChar(datoSCI);

    U6STAbits.OERR = 0;

#endif

}

