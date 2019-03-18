/* 
 * File:   TPM.h
 * Author: FING150628
 *
 * Created on July 18, 2015, 4:29 PM
 */

#ifndef TPM_H
#define	TPM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "init.h"


    /** ****************************************************************************
     ** ************ TPM CONFIG ****************************************************
     ** ****************************************************************************/


    // definicion de prescaler timer 1
#define PRESCALE_1                        8                               // prescale de 8
#define FREQ_1                         1000                               // 1 kHz


#if PRESCALE_1 == 1
#define TCKPS_USU_1                       0                               // divide por 1
#elif PRESCALE_1 == 8
#define TCKPS_USU_1                       1                               // divide por 8
#elif PRESCALE_1 == 64
#define TCKPS_USU_1                       2                               // divide por 64
#elif PRESCALE_1 == 256
#define TCKPS_USU_1                       3                               // divide por 256
#endif


    // definicion de prescaler timer 2
#define PRESCALE_2                        8                               // prescale de 8
#define FREQ_2                            1000                            // 1 kHz


#if PRESCALE_2 == 1
#define TCKPS_USU_2                       0                               // divide por 1
#elif PRESCALE_2 == 2
#define TCKPS_USU_2                       1                               // divide por 2
#elif PRESCALE_2 == 4
#define TCKPS_USU_2                       2                               // divide por 4
#elif PRESCALE_2 == 8
#define TCKPS_USU_2                       3                               // divide por 8
#elif PRESCALE_2 == 16
#define TCKPS_USU_2                       4                               // divide por 16
#elif PRESCALE_2 == 32
#define TCKPS_USU_2                       5                               // divide por 32
#elif PRESCALE_2 == 64
#define TCKPS_USU_2                       6                               // divide por 64
#elif PRESCALE_2 == 256
#define TCKPS_USU_2                       7                               // divide por 256
#endif


    // definicion de periodo

#define TIMER_1                         FCY/PRESCALE_1/FREQ_1
#define TIMER_2                         FCY/PRESCALE_2/FREQ_2



    /** ****************************************************************************
     ** ************ TPM FUNCTIONS *************************************************
     ** ****************************************************************************/

    void TPM1_Init(void);
    void TPM2_Init(void);
    void TPM1_Stop(void);
    void TPM2_Stop(void);

    // void __attribute__((interrupt(ipl4), vector(_TIMER_1_VECTOR)))_T1InterruptHandler(void);
    // void __attribute__((interrupt(ipl4), vector(_TIMER_2_VECTOR)))_T2InterruptHandler(void);

    void TPM1_ISR();
    void TPM2_ISR();



#ifdef	__cplusplus
}
#endif

#endif	/* TPM_H */

