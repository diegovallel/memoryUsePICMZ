/* 
 * File:   init.h
 * Author: FING_150628
 *
 * Created on 16 de junio de 2015, 05:00 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef PIC32MZ2048ECM144
#define PIC32MZ2048ECM144
#endif


    /** ************************************************************************
     ** ******************* INIT CONFIG ****************************************
     ** ************************************************************************/
    // <editor-fold defaultstate="collapsed" desc="INIT CONFIG">
    // #include <plib.h>

#ifdef PIC32MZ2048ECM144
#include <p32xxxx.h>
#include <xc.h>
    // #include <sys/attribs.h>
#endif

    //</editor-fold>


    /** ************************************************************************
     ** ******************* STATES DEFINES *************************************
     ** ************************************************************************/
    // <editor-fold defaultstate="collapsed" desc="STATES DEFINES">
#define TRUE                                1
#define FALSE                               0
#define INPUT                               1
#define OUTPUT                              0
#define HIGH                                1
#define LOW                                 0

#define NULL_DATA                           0

#define XTAL                                FALSE

    //</editor-fold>


    /** ************************************************************************
     ** ******************* CLOCK DEFINES **************************************
     ** ************************************************************************/
    // <editor-fold defaultstate="collapsed" desc="CLOCK DEFINES">
#ifdef PIC32MZ2048ECM144
#define FOSC                                       24000000             // Crystal de 24 MHz
#define PLLIDIV                                           3             // Divisor de PLL de entrada
#define PLLMULT                                          50             // Multiplicador del PLL
#define PLLODIV                                           2             // Divisor de PLL de salida
#define _FSYS              (FOSC*PLLMULT)/(PLLIDIV*PLLODIV)             // Frecuencia de trabajo del microcontrolador
#define FCY                                         _FSYS/2             // Frecuencia de BUS de los perifericos
#endif

    //</editor-fold>


    /** ************************************************************************
     ** ******************* FUNCTIONS ******************************************
     ** ************************************************************************/

    // void PLL_Init(void);
    void INTERRUPT_Init(void);


    /** ************************************************************************
     ** ******************* FLAGS **********************************************
     ** ************************************************************************/
    // Bits para el manejo de diversas banderas de programa, definidas por el usuario
    // <editor-fold defaultstate="collapsed" desc="STR_FLAGS Define">

    typedef union {
        unsigned int flag;

        struct {
            unsigned char flag00 : 1;
            unsigned char flag01 : 1;
            unsigned char flag02 : 1;
            unsigned char flag03 : 1;
            unsigned char flag04 : 1;
            unsigned char flag05 : 1;
            unsigned char flag06 : 1;
            unsigned char flag07 : 1;
            unsigned char flag08 : 1;
            unsigned char flag09 : 1;
            unsigned char flag10 : 1;
            unsigned char flag11 : 1;
            unsigned char flag12 : 1;
            unsigned char flag13 : 1;
            unsigned char flag14 : 1;
            unsigned char flag15 : 1;
            unsigned char flag16 : 1;
            unsigned char flag17 : 1;
            unsigned char flag18 : 1;
            unsigned char flag19 : 1;
            unsigned char flag20 : 1;
            unsigned char flag21 : 1;
            unsigned char flag22 : 1;
            unsigned char flag23 : 1;
            unsigned char flag24 : 1;
            unsigned char flag25 : 1;
            unsigned char flag26 : 1;
            unsigned char flag27 : 1;
            unsigned char flag28 : 1;
            unsigned char flag29 : 1;
            unsigned char flag30 : 1;
            unsigned char flag31 : 1;
        } Bits;
    } STR_FLAGS;
    //</editor-fold>


    // Bits para el manejo de diversos estados de programa, definidos por el usuario
    // <editor-fold defaultstate="collapsed" desc="STR_STATES Define">

    typedef union {
        unsigned int state;

        struct {
            unsigned char state00 : 4;
            unsigned char state01 : 4;
            unsigned char state02 : 4;
            unsigned char state03 : 4;
            unsigned char state04 : 4;
            unsigned char state05 : 4;
            unsigned char state06 : 4;
            unsigned char state07 : 4;
        } Nibbles;
    } STR_STATES;
    //</editor-fold>



    extern volatile STR_FLAGS _Events;
#define fl_TPM1                   _Events.Bits.flag00 //ok // bandera para atencion a interrupcion por Timer1
#define fl_proc_rx1               _Events.Bits.flag01 //ok
    //#define fl_02               _Events.Bits.flag02 //ok
    //#define fl_03               _Events.Bits.flag03 //ok
    //#define fl_04               _Events.Bits.flag04 //ok
    //#define fl_05               _Events.Bits.flag05 //ok
    //#define fl_06               _Events.Bits.flag06 //ok
    //#define fl_07               _Events.Bits.flag07 //ok
    //#define fl_08               _Events.Bits.flag08 //ok
    //#define fl_09               _Events.Bits.flag09 //ok
    //#define fl_10               _Events.Bits.flag10 //ok
    //#define fl_11               _Events.Bits.flag11 //ok
    //#define fl_12               _Events.Bits.flag12 //ok
    //#define fl_13               _Events.Bits.flag13 //ok
    //#define fl_14               _Events.Bits.flag14 //ok
    //#define fl_15               _Events.Bits.flag15 //ok
    //#define fl_16               _Events.Bits.flag16 //ok
    //#define fl_17               _Events.Bits.flag17 //ok
    //#define fl_18               _Events.Bits.flag18 //ok
    //#define fl_19               _Events.Bits.flag19 //ok
    //#define fl_20               _Events.Bits.flag20 //ok
    //#define fl_21               _Events.Bits.flag21 //ok
    //#define fl_22               _Events.Bits.flag22 //ok
    //#define fl_23               _Events.Bits.flag23 //ok
    //#define fl_24               _Events.Bits.flag24 //ok
    //#define fl_25               _Events.Bits.flag25 //ok
    //#define fl_26               _Events.Bits.flag26 //ok
    //#define fl_27               _Events.Bits.flag27 //ok
    //#define fl_28               _Events.Bits.flag28 //ok
    //#define fl_29               _Events.Bits.flag29 //ok
    //#define fl_30               _Events.Bits.flag30 //ok
    //#define fl_31               _Events.Bits.flag31 //ok


    extern volatile STR_STATES _StateEvents;
    //#define st_00               _StateEvents.Nibbles.state00 //ok
    //#define st_01               _StateEvents.Nibbles.state01 //ok
    //#define st_02               _StateEvents.Nibbles.state02 //ok
    //#define st_03               _StateEvents.Nibbles.state03 //ok
    //#define st_04               _StateEvents.Nibbles.state04 //ok
    //#define st_05               _StateEvents.Nibbles.state05 //ok
    //#define st_06               _StateEvents.Nibbles.state06 //ok
    //#define st_07               _StateEvents.Nibbles.state07 //ok



#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

