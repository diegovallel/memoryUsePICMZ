/*
 * File:   init.c
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */


/** ****************************************************************************
 ** ************ INIT CONFIG ***************************************************
 ** ****************************************************************************/
#include "init.h"


/** ****************************************************************************
 ** ************ PLL CONFIG ****************************************************
 ** ****************************************************************************/

#ifdef PIC32MX795F512L

//-----------------------XTAL CONFIG--------------------------------------------//
#pragma config POSCMOD      = XT                                                // Extern XTAL 8MHz
#pragma config FNOSC        = PRIPLL                                            // Primary OSC with PLL (XT+HS+EC+PLL)
#pragma config FPLLIDIV     = DIV_2                                             // PLL Divide by 2
#pragma config FPLLMUL      = MUL_20                                            // 20x PLL Multiplier
#pragma config FPLLODIV     = DIV_1                                             // PLL Output divider
#pragma config FPBDIV       = DIV_1                                             // BUS Divider

//------------------------WATCH DOG TIMER---------------------------------------//
#pragma config FWDTEN       = OFF                                               // Watchdog Timer disable
#pragma config WDTPS        = PS1                                               // Watchdog Timer Postscaler
#pragma config FCKSM        = CSDCMD                                            // Clock Switching & Fail Safe Monitor
#pragma config OSCIOFNC     = ON                                                // CLKO Enable
#pragma config IESO         = ON                                                // Internal/External Switch-over
#pragma config FSOSCEN      = OFF                                               // Secundary OSC Disabled
#pragma config CP           = OFF                                               // Code Protection disable
#pragma config BWP          = OFF                                               // Flash Boot Write Prtection disable
#pragma config PWP          = OFF                                               // Flash Program Write Prtection disable
#pragma config ICESEL       = ICS_PGx2                                          // ICE/ICD Comm Channel Select
#pragma config DEBUG        = ON                                                // Debug Enable

#endif


/** ****************************************************************************
 ** ************ PLL CONFIG ****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: PLL_Init                                                              *
 * Desc: Initialize PLL to 16 Mhz                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
//void PLL_Init(void) {
//
//#if dsPIC33FJ256GP710
//    // Configure Oscillator to operate the device a 16MHz (Fcy)
//    // FOSC = Fin*M/(N1*N2),  Fcy = Fosc/2
//    // Fin = 8MHz
//    // M = PLLFB+2
//    // N1 = PLLPRE + 2
//    // N2 = 2*(PLLPOST + 1)
//
//    // Configure PLL prescaler, PLL postcaler, PLL divisor
//    PLLFBD = 14; // M = 16
//    CLKDIVbits.PLLPOST = 0; // N1 = 2
//    CLKDIVbits.PLLPRE = 0; // N2 = 2
//
//    // Fosc = 32 MHz
//
//    OSCTUN = 0;
//    RCONbits.SWDTEN = 0;
//
//    // wait for PLL to Lock
//    while (OSCCONbits.LOCK != 1);
//#endif
//
//}

