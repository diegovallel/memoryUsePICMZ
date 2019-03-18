/*
 * File:   TPM.c
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

/** ****************************************************************************
 ** ************ TPM CONFIG ****************************************************
 ** ****************************************************************************/
#include "TPM.h"

#include "vdip.h"


/** ****************************************************************************
 ** ************ EXT VARIABLES *************************************************
 ** ****************************************************************************/
extern volatile STR_FLAGS _Events;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: TPM1_Init                                                             *
 * Desc: Initialize TPM1 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM1_Init(int frec) {

    /* configuracion de las interrupciones */

    IFS0bits.T1IF = 0; //borra la bandera de interrpcion del timer
    IEC0bits.T1IE = 1; //habilita la interrupcion del timer
    IPC1bits.T1IP = 4; //prioridad interrupcion= 4
    IPC1bits.T1IS = 1; //subprioridad interrupcion= 1


    /* Initialice TMR2 Counter */

    TMR1 = 0;
    PR1 = frec; // FCY / (PS*FREQ)


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de control */

    T1CONbits.TON = 1; // Start TPM
    T1CONbits.TSIDL = 0; // Stop in Idle
    T1CONbits.TGATE = 0; // Gate Accumulation disable
    T1CONbits.TCKPS = TCKPS_USU_1; // Prescaler configuration
    T1CONbits.TSYNC = 0;
    T1CONbits.TCS = 0; // internal clock (FOSC/4) = Fcy (16MHz)

    if (frec == TIMER_1_HIGH) {
        fl_timerHigh = TRUE;
    } else if (frec == TIMER_1_LOW) {
        fl_timerHigh = FALSE;
    }

}

/*******************************************************************************
 * Name: TPM2_Init                                                             *
 * Desc: Initialize TPM2 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM2_Init(void) {

    /* configuracion de las interrupciones */

    IFS0bits.T2IF = 0; //borra la bandera de interrpcion del timer
    IEC0bits.T2IE = 1; //habilita la interrupcion del timer
    IPC2bits.T2IP = 4; //prioridad interrupcion= 4
    IPC2bits.T2IS = 1; //subprioridad interrupcion= 1


    /* Initialice TMR2 Counter */

    TMR2 = 0;
    PR2 = TIMER_2; // FCY / (PS*FREQ)


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de control */

    T2CONbits.TON = 1; // Start TPM
    T2CONbits.TSIDL = 0; // Stop in Idle
    T2CONbits.TGATE = 0; // Gate Accumulation disable
    T2CONbits.TCKPS = TCKPS_USU_2; // Prescaler configuration
    // T2CONbits.TSYNC = 0;
    T2CONbits.TCS = 0; // internal clock (FOSC/4) = Fcy (16MHz)

}

/*******************************************************************************
 * Name: TPM1_Stop                                                             *
 * Desc: Stop TPM1 Module                                                      *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM1_Stop(void) {

    /* configuracion de las interrupciones */

    IFS0bits.T1IF = 0; // Clear Interruption Flag TPM2
    IEC0bits.T1IE = 0; // Interruption Disabled TPM2
    IPC1bits.T1IP = 4; //prioridad interrupcion= 4
    IPC1bits.T1IS = 1; //subprioridad interrupcion= 1


    /* Registro de control */

    T1CONbits.TON = 0; // Start TPM


    /* Initialice TMR2 Counter */

    TMR1 = 0;
}

/*******************************************************************************
 * Name: TPM2_Stop                                                             *
 * Desc: Stop TPM2 Module                                                      *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM2_Stop(void) {

    /* configuracion de las interrupciones */

    IFS0bits.T2IF = 0; // Clear Interruption Flag TPM2
    IEC0bits.T2IE = 0; // Interruption Disabled TPM2
    IPC2bits.T2IP = 4; //prioridad interrupcion= 4
    IPC2bits.T2IS = 1; //subprioridad interrupcion= 1


    /* Registro de control */

    T2CONbits.TON = 0; // Start TPM


    /* Initialice TMR2 Counter */

    TMR2 = 0;
}


/** ****************************************************************************
 ** ************ INTERRUPTS ****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: _T1Interrupt                                                          *
 * Desc: Interrupt T1 Module                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl4AUTO), vector(_TIMER_1_VECTOR)))_T1InterruptHandler(void) {

    IFS0bits.T1IF = 0; // external interrupt 0 T1 flag reset

    // Atiende la interrupcion
    TPM1_ISR();
}

/*******************************************************************************
 * Name: _T2Interrupt                                                          *
 * Desc: Interrupt T2 Module                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl4AUTO), vector(_TIMER_2_VECTOR)))_T2InterruptHandler(void) {

    IFS0bits.T2IF = 0; // external interrupt 0 T1 flag reset

    // Atiende la interrupcion
    TPM2_ISR();
}

/*******************************************************************************
 * Name: _T1Interrupt                                                          *
 * Desc: Interrupt T1 Module                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM1_ISR() {

    // Espacio para programar
    fl_TPM1 = TRUE;

    //chequeo estatus vnc1l
//    if ((st_vdip == VDIP_NO_MODE)) { //&& (fl_wr_vnc1l == 0)) { //si no se esta escribiendo y se requiere evaluar el status
//
//        vdip_Status_Data(INT_USB); //chequea si hay algo en el usb
//    }
}

/*******************************************************************************
 * Name: _T2Interrupt                                                          *
 * Desc: Interrupt T2 Module                                                   *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void TPM2_ISR() {

    // Espacio para programar
    fl_TPM2 = TRUE;
}

