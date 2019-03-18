/* 
 * File:   main.c
 * Author: FING_150628
 *
 * Created on 16 de junio de 2015, 04:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <plib.h>


#ifndef PIC32MZ2048ECM144
#define PIC32MZ2048ECM144
#endif


#ifdef PIC32MZ2048ECM144
#include <p32xxxx.h>
#include <xc.h>
#endif


/*******************************************************************************
 **************** INCLUDES *****************************************************
 *******************************************************************************/

#include "init.h"
#include "TPM.h"
#include "SCI.h"
#include "fifo_rx1.h"
#include "fifo_tx1.h"



/*******************************************************************************
 ************* EVENTS VARIABLES ************************************************
 *******************************************************************************/
volatile STR_FLAGS _Events; // eventos de los perifericos y banderas de control
volatile STR_STATES _StateEvents; // estados de los diferentes modulos


#if USE_FIFO_SCI1
volatile unsigned char dataoFifo1[500];
volatile unsigned char dataiFifo1[500];
volatile unsigned char* dataOut1 = dataoFifo1;
volatile unsigned char* dataIn1 = dataiFifo1;
#endif


unsigned int cont = 0;


unsigned char DATO1 = 0;
unsigned char var = 0;

/*
 * 
 */
int main(int argc, char** argv) {


    unsigned int da = 0;

    // captura frecuencia de bus
    da = FCY;

    //    SYSKEY = 0x0;
    //    SYSKEY = 0xAA996655;
    //    SYSKEY = 0x556699AA;
    //
    //    OSCCONbits.COSC = 0x01;
    //    OSCCONbits.NOSC = 0x01;
    //
    //    OSCCONbits.OSWEN = 1;
    //
    ////    OSCCON = 0x1121;
    //
    //    while(OSCCONbits.OSWEN);
    //
    //    SYSKEY = 0x0;




    TPM1_Init();

    SCI1_Init();

    Fifo_Rx1_Init();
    Fifo_Tx1_Init();


    INTERRUPT_Init();

    TRISAbits.TRISA0 = 0;


    Fifo_Tx1_Put('H');
    //SCI1_SendChar('H');


    for (;;) {

        // interrupcion por TPM1.-
        if (fl_TPM1) {
            fl_TPM1 = FALSE;

            // espacio para programar

            cont++;

            if (cont == 1000) {
                cont = 0;

                //                LATAbits.LATA0 = !LATAbits.LATA0;
                LATAINV = 0x1;
            }
        }



        if (fl_proc_rx1) {
            fl_proc_rx1 = FALSE;

            /* Recepcion */
            dataIn1 = dataoFifo1;

            while (Fifo_Rx1_Get(dataIn1)) {
                dataIn1++;
            }

            /* transmision */
            dataOut1 = dataoFifo1;
            while ((*dataOut1 != 0) && (Fifo_Tx1_Put(*dataOut1))) {
                *dataOut1 = 0;
                dataOut1++;
            }

        }


    }


    return (EXIT_SUCCESS);
}

