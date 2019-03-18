/*
 * File:   SPI.c
 * Author: FING150628
 *
 * Created on January 28, 2015, 2:06 PM
 */

/** ****************************************************************************
 ** ************ SPI CONFIG ****************************************************
 ** ****************************************************************************/
#include "SPI.h"

#if USE_FIFO_SPI1
#include "fifo_sdi1.h"
#include "fifo_sdo1.h"
#endif

#include "vdip.h"


/** ****************************************************************************
 ** ************ EXT VARIABLES *************************************************
 ** ****************************************************************************/
extern volatile STR_FLAGS _Events;
extern volatile STR_STATES _StateEvents;

volatile unsigned int* ptr_rx;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: SPI1_Init                                                             *
 * Desc: Initialize SPI2 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1_Init(void) {

    SCK1_DD = OUTPUT; // Output RD10/SCK1
    SDI1_DD = INPUT; // Input  RC4/SDI1
    SDO1_DD = OUTPUT; // Output RD0/SDO1
    CSI_OUTPUT(); // Output RD9 (SDC_CS RD9)
    CSE_OUTPUT(); // Output RD8 (SDC_CS RD8)

    CSI_OFF(); // deshabilitar RD9 (SDC_CS RD9)
    CSE_OFF(); // deshabilitar RD8 (SDC_CS RD8)

    SPI1_Config(POLARITY, PHASE, SAMPLE); // MODO 00 CON MUESTREO EN MITAD
}

/*******************************************************************************
 * Name: SPI1_Config                                                           *
 * Desc: Configure SPI1 Module                                                 *
 * Parameter: cpol, cpha, sample                                               *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1_Config(unsigned int cpol, unsigned int cpha, unsigned int sample) {


    /* Registro de control */
    SPI1CONbits.ON = 0; // habilita SPI1
    SPI1CONbits.ENHBUF = 0; // deshabilita el uso de fifos para SPI
    SPI1CONbits.SMP = sample; // muestreo
    SPI1CONbits.CKE = cpha; // fase
    SPI1CONbits.CKP = cpol; // polaridad
    SPI1CONbits.MODE32 = 0; // modo 32 bits
    SPI1CONbits.MODE16 = 1; // modo 16 bits
    SPI1CONbits.SRXISEL = 1; // seleccion de interrupcion por recepcion
    SPI1CONbits.STXISEL = 1; // seleccion de interrupcion por transmision

    SPI1CONbits.MSTEN = 1; // Master mode

    /* Baud Rate */
    SPI1BRG = SPI_BRG_VAL_1;

    /* Registro de control */
    SPI1CONbits.ENHBUF = 0; // deshabilita el uso de fifos para SPI

    /* Limpia buffer de SPI */
    (void) SPI1BUF;

    /* Configuracion de las interrupciones */
    IEC0bits.SPI1EIE = 1; // Interruption Enabled SPI1 by Error
    IEC0bits.SPI1RXIE = 1; // Interruption Enabled SPI1 by RX
    IEC0bits.SPI1TXIE = 0; // Interruption Disabled SPI1 by TX

    IFS0bits.SPI1EIF = 0; // Clear Interruption Flag SPI1 by Error
    IFS0bits.SPI1RXIF = 0; // Clear Interruption Flag SPI1 by RX
    IFS0bits.SPI1TXIF = 0; // Clear Interruption Flag SPI1 by TX

    IPC5bits.SPI1IP = 6; // priority Level
    IPC5bits.SPI1IS = 1; // priority Level

    /* Registro de estado */
    SPI1STATbits.SPIROV = 0; // limpia flag por overflow
    SPI1CONbits.ON = 1; // habilita SPI1

}

/*******************************************************************************
 * Name: SPI1_Off                                                              *
 * Desc: Disable SPI1 Module                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1_Off(void) {

    IEC0bits.SPI1EIE = 1; // Interruption Disabled SPI1 by Error
    IEC0bits.SPI1RXIE = 1; // Interruption Disabled SPI1 by RX
    IEC0bits.SPI1TXIE = 1; // Interruption Disabled SPI1 by TX

    SPI1STAT = 0; // deshabilita SPI1

    SPI1CON = 0; // deshabilita SPI1

}

/*******************************************************************************
 * Name: SPI1_WriteData                                                        *
 * Desc: Interrupt SCI6 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1_WriteData(unsigned int data, volatile unsigned int* _rx, unsigned char device) {

    // asigna apuntador de variable a leer en respuesta a SPI
    ptr_rx = _rx;

    if (device == INTERNAL_USB) {

        CSI_ON(); // activa modulo para memoria interna
    } else if (device == EXTERNAL_USB) {

        CSE_ON(); // activa modulo para memoria externa
    }

    SPI1BUF = data; // escribe el dato en el buffer de salida
}

/*******************************************************************************
 * Name: _SPI1InterruptHandler                                                 *
 * Desc: Interrupt SCI6 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl6AUTO), vector(_SPI_1_VECTOR)))_SPI1InterruptHandler(void) {
    if (IFS0bits.SPI1TXIF == 1) {//si hubo interrupcion por transmision

        IFS0bits.SPI1TXIF = 0; // external interrupt SPI1 Tx flag reset

        SPI1TX_ISR();

    }
    if (IFS0bits.SPI1RXIF == 1) { //si hubo interrupcion por recepcion

        (void) SPI1BUF; // limpia buffer de entrada

        IFS0bits.SPI1RXIF = 0; // external interrupt SPI1 Rx flag reset

        SPI1RX_ISR();

    }
    if (IFS0bits.SPI1EIF == 1) { //si hubo interrupcion por error
        IFS0bits.SPI1EIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _SPI1TXInterrupt                                                      *
 * Desc: Interrupt SCI1 TX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1TX_ISR(void) {

    // Espacio para programar


}

/*******************************************************************************
 * Name: _SPI1RXInterrupt                                                      *
 * Desc: Interrupt SCI1 RX Module                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void SPI1RX_ISR(void) {

    // Espacio para programar

#if USE_FIFO_SPI1
    volatile unsigned int datoSPI;

    datoSPI = SPI1BUF;

    if (!Fifo_Sdi1_Put(datoSPI)) { // agrega dato a la fifo
        Fifo_Sdi1_Init();
    }

    fl_SPI1 = TRUE; // se interpretan los datos recibidos

#else

    *ptr_rx = SPI1BUF; // lee dato del registro de entrada
    CSI_OFF(); // desactiva esclavo
    CSE_OFF(); // desactiva esclavo

    fl_SPI1 = TRUE; // activa bandera de interrupcion

    vdip_RxData(); //rutina recepcion vnc1l


#endif

}









