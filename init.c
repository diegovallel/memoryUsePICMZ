/*
 * File:   init.c
 * Author: FING_150628
 *
 * Created on 16 de junio de 2015, 05:00 PM
 */


/** ************************************************************************
 ** ******************* INIT CONFIG ****************************************
 ** ************************************************************************/
#include "init.h"


/** ************************************************************************
 ** ******************* PLL CONFIG *****************************************
 ** ************************************************************************/
// <editor-fold defaultstate="collapsed" desc="Configuration Bits">
#ifdef PIC32MZ2048ECM144

#if XTAL==TRUE

// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USBID Selection (Controlled by the USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3         // System PLL Input Divider (3x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (Bypass)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_100        // System PLL Multiplier (PLL Multiply by 100)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = ON              // USB PLL Enable (USB PLL is enabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Enable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = ON               // Background Debugger Enable (Debugger is enabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// SEQ0

// DEVADC1

// DEVADC2

// DEVADC3

// DEVADC4

// DEVADC5

// DEVSN0

// DEVSN1

#else

//--------------------------------- DEVCFG3 ------------------------------------//
#pragma config USERID = 0xFFFF                                                  // User ID
#pragma config FMIIEN = ON                                                      // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON                                                      // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON                                                     // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON                                                    // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON                                                     // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON                                                    // USB USBID Selection (Controlled by the USB Module)

//--------------------------------- DEVCFG2 ------------------------------------//
#pragma config FPLLIDIV = DIV_8                                                 // System PLL Input Divider (8x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ                                         // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC                                               // System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_50                                                // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2                                                 // System PLL Output Clock Divider (2x Divider)
#pragma config UPLLFSEL = FREQ_24MHZ                                            // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
#pragma config UPLLEN = ON                                                      // USB PLL Enable (USB PLL is enabled)

//--------------------------------- DEVCFG1 ------------------------------------//
#pragma config FNOSC = SPLL                                                     // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128                                            // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = ON                                                     // Secondary Oscillator Enable (Enable SOSC)
#pragma config IESO = ON                                                        // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = HS                                                     // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF                                                   // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME                                                   // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576                                                // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP                                                   // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL                                                  // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF                                                     // Watchdog Timer Enable (WDT Enabled)
#pragma config FWDTWINSZ = WINSZ_25                                             // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31                                                   // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF                                                     // Deadman Timer Enable (Deadman Timer is enabled)

//--------------------------------- DEVCFG0 ------------------------------------//
#pragma config DEBUG = ON                                                       // Background Debugger Enable (Debugger is enabled)
#pragma config JTAGEN = OFF                                                     // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2                                                // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = OFF                                                      // Trace Enable (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32                                                 // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED                                           // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF                                                     // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2                                               // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config EJTAGBEN = NORMAL                                                // EJTAG Boot (Normal EJTAG functionality)

//--------------------------------- DEVCP0 -------------------------------------//
#pragma config CP = OFF                                                         // Code Protect (Protection Disabled)

//--------------------------------- BF1SEQ0 ------------------------------------//
#pragma config TSEQ = 0xFFFF
#pragma config CSEQ = 0xFFFF
#endif
#endif
// </editor-fold>


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
//
//}

/*******************************************************************************
 * Name: PLL_Init                                                              *
 * Desc: Initialize PLL to 16 Mhz                                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void INTERRUPT_Init(void){


    INTCONbits.MVEC = 1;
    
    asm volatile("ei");  // activa las interrupciones

    __builtin_enable_interrupts();    // Set the CP0 Status register IE bit high to globally enable interrupts

}



