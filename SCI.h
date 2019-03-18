/* 
 * File:   SCI.h
 * Author: FING_150628
 *
 * Created on 18 de noviembre de 2015, 12:28 PM
 */

#ifndef SCI_H
#define	SCI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "init.h"


    /* *****************************************************************************
     * *****************************************************************************
     * ***************** WIRING DEFINITION *****************************************
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |              RX1(PTD)|-------|DOUT            |			   *
     * |    UART1     TX1(PTD)|-------|DIN    DEV      |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************/


    /** ****************************************************************************
     ** ************ SCI CONFIG ****************************************************
     ** ****************************************************************************/

    // <editor-fold defaultstate="collapsed" desc="SCI CONFIG">
#define HIGH_SPEED                      TRUE
#define USE_FIFO_SCI1                   TRUE
#define USE_FIFO_SCI2                   FALSE
#define USE_FIFO_SCI3                   FALSE
#define USE_FIFO_SCI4                   FALSE
#define USE_FIFO_SCI5                   FALSE
#define USE_FIFO_SCI6                   FALSE


    // define de prescale
#if HIGH_SPEED
#define PRESCALE_UART                   4
#else
#define PRESCALE_UART                   16
#endif


    // define para baudRate

#define BAUD_RATE_1                     115200     // Max 1000000 //
#define BAUD_RATE_2                     9600       // Max 1000000 //
#define BAUD_RATE_3                     9600       // Max 1000000 //
#define BAUD_RATE_4                     9600       // Max 1000000 //
#define BAUD_RATE_5                     9600       // Max 1000000 //
#define BAUD_RATE_6                     9600       // Max 1000000 //
#define BRG_VAL_1                       (FCY/PRESCALE_UART/BAUD_RATE_1)-1
#define BRG_VAL_2                       (FCY/PRESCALE_UART/BAUD_RATE_2)-1
#define BRG_VAL_3                       (FCY/PRESCALE_UART/BAUD_RATE_3)-1
#define BRG_VAL_4                       (FCY/PRESCALE_UART/BAUD_RATE_4)-1
#define BRG_VAL_5                       (FCY/PRESCALE_UART/BAUD_RATE_5)-1
#define BRG_VAL_6                       (FCY/PRESCALE_UART/BAUD_RATE_6)-1


    // define para caracteres especiales

#define LF                              0x0A        //Caracter avance de linea
#define CR                              0x0D        //Caracter retorno de carro
#define CHAR_NULL                       0x00        //Caracter nulo

#define _CTR_CHAR_SCI1                  ']'         //Caracter de control para interpretar datos de
#define _CTR_CHAR_SCI2                  ']'         //Caracter de control para interpretar datos de
#define _CTR_CHAR_SCI3                  ']'         //Caracter de control para interpretar datos de
#define _CTR_CHAR_SCI4                  ']'         //Caracter de control para interpretar datos de
#define _CTR_CHAR_SCI5                  ']'
#define _CTR_CHAR_SCI6                  ']'


    // define para puertos de entrada y salida remapeables

#define U1RXPIN_DIR()                    ANSELCbits.ANSC1 = 0  // Entrada
#define U1RXPIN_DEF()                    U1RXRbits.U1RXR = 0b1010  // RPC1
#define U1TXPIN_DEF()                    RPE5Rbits.RPE5R = 1   // RPE5




    //</editor-fold>

    /** ****************************************************************************
     ** ************ SCI FUNCTIONS *************************************************
     ** ****************************************************************************/

    // <editor-fold defaultstate="collapsed" desc="SCI FUNCTIONS">
    void SCI1_Init(void);
    void SCI2_Init(void);
    void SCI3_Init(void);
    void SCI4_Init(void);
    void SCI5_Init(void);
    void SCI6_Init(void);
    void SCI1_SendChar(int val);
    void SCI2_SendChar(int val);
    void SCI3_SendChar(int val);
    void SCI4_SendChar(int val);
    void SCI5_SendChar(int val);
    void SCI6_SendChar(int val);
    void SCI1_SendLoad(char* load, int len);
    void SCI2_SendLoad(char* load, int len);
    void SCI3_SendLoad(char* load, int len);
    void SCI4_SendLoad(char* load, int len);
    void SCI5_SendLoad(char* load, int len);
    void SCI6_SendLoad(char* load, int len);

    //    void __attribute__((interrupt(ipl5), vector(_UART_1_VECTOR)))UART1Handler(void);
    //    void __attribute__((interrupt(ipl5), vector(_UART_2_VECTOR)))UART2Handler(void);
    //    void __attribute__((interrupt(ipl5), vector(_UART_3_VECTOR)))UART3Handler(void);
    //    void __attribute__((interrupt(ipl5), vector(_UART_4_VECTOR)))UART4Handler(void);
    //    void __attribute__((interrupt(ipl5), vector(_UART_5_VECTOR)))UART5Handler(void);
    //    void __attribute__((interrupt(ipl5), vector(_UART_6_VECTOR)))UART6Handler(void);
    void U1TX_ISR(void);
    void U1RX_ISR(void);
    void U2TX_ISR(void);
    void U2RX_ISR(void);
    void U3TX_ISR(void);
    void U3RX_ISR(void);
    void U4TX_ISR(void);
    void U4RX_ISR(void);
    void U5TX_ISR(void);
    void U5RX_ISR(void);
    void U6TX_ISR(void);
    void U6RX_ISR(void);
    //</editor-fold>


#ifdef	__cplusplus
}
#endif

#endif	/* SCI_H */

