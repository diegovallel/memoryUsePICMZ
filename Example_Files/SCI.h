/* 
 * File:   SCI.h
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
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
     * |              RX1(RF2)|-------|DOUT            |			   *
     * |    UART1     TX1(RF8)|-------|DIN    ECG      |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |              RX2(RF4)|-------|DOUT            |			   *
     * |    UART2     TX2(RF5)|-------|DIN    SPO2     |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |              RX3(RG7)|-------|DOUT            |			   *
     * |    UART3     TX3(RG8)|-------|DIN    NIBP     |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |             RX4(RD14)|-------|DOUT            |			   *
     * |    UART4    TX4(RD15)|-------|DIN    RN171    |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |             RX5(RF12)|-------|DOUT            |			   *
     * |    UART5    TX5(RF13)|-------|DIN    FT232    |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************
     *  ______________________         ________________				   *
     * |              RX6(RG9)|-------|DOUT            |			   *
     * |    UART6     TX6(RG6)|-------|DIN    VENT     |			   *
     * |______________________|       |________________|                           *
     *                                                                             *
     * 										   *
     * *****************************************************************************
     * *****************************************************************************/





    /** ****************************************************************************
     ** ************ SCI CONFIG ****************************************************
     ** ****************************************************************************/

#define HIGH_SPEED                      TRUE
#define USE_FIFO_SCI1                   TRUE
#define USE_FIFO_SCI2                   TRUE
#define USE_FIFO_SCI3                   TRUE
#define USE_FIFO_SCI4                   TRUE
#define USE_FIFO_SCI5                   TRUE
#define USE_FIFO_SCI6                   TRUE


    // define de prescale
#if HIGH_SPEED
#define PRESCALE_UART                   4
#else
#define PRESCALE_UART                   16
#endif


    // define para baudRate
#define BAUD_RATE_1                     125000       // Max 500000 // ECG
#define BAUD_RATE_2                     125000       // Max 500000 // SPO
#define BAUD_RATE_3                     125000       // Max 500000 // NIP
#define BAUD_RATE_4                     230400       // Max 500000 // WIFI
#define BAUD_RATE_5                     230400       // Max 500000 // FT232
#define BAUD_RATE_6                     57600        // Max 500000 // VEN
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

#define _CTR_CHAR_SCI1                  ','         //Caracter de control para interpretar datos de ECG
#define _CTR_CHAR_SCI2                  ','         //Caracter de control para interpretar datos de SPO
#define _CTR_CHAR_SCI3                  ','         //Caracter de control para interpretar datos de NIP
#define _CTR_CHAR_SCI4                  LF          //Caracter de control para interpretar datos de RN171
#define _CTR_CHAR_SCI4_1                '>'         //Caracter de control para interpretar datos de RN171
#define _CTR_CHAR_SCI4_2                '$'         //Caracter de control para interpretar datos de RN171
#define _CTR_CHAR_SCI4_3                '*'         //Caracter de control para interpretar datos de RN171
#define _CTR_CHAR_SCI5                  ']'
#define _CTR_CHAR_SCI6                  ']'




    /** ****************************************************************************
     ** ************ SCI FUNCTIONS *************************************************
     ** ****************************************************************************/

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



#ifdef	__cplusplus
}
#endif

#endif	/* SCI_H */

