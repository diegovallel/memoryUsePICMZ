/*
 * File:   I2C.c
 * Author: FING150628
 *
 * Created on June 10, 2015, 10:17 AM
 */

/** ****************************************************************************
 ** ************ IIC CONFIG ****************************************************
 ** ****************************************************************************/
#include "I2C.h"


/** ****************************************************************************
 ** ************ EXT VARIABLES *************************************************
 ** ****************************************************************************/
extern volatile STR_FLAGS _Events;

volatile unsigned char IIC2_State = IIC_Idle; // inicializacion de estados de I2C2

volatile unsigned char counter_tx = 0;
volatile unsigned char counter_rx = 0;
volatile unsigned char dev_addr = 0;
volatile unsigned char mem_addr = 0;
volatile unsigned char *ptr_tx;
volatile unsigned char *ptr_rx;


/** ****************************************************************************
 ** ************ FUNCTIONS *****************************************************
 ** ****************************************************************************/

/*******************************************************************************
 * Name: I2C2_Init                                                             *
 * Desc: Initialize IIC2 Module                                                *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void I2C2_Init(void) {


    /* Baud Rate */
    I2C2BRG = I2C_BRG_VAL_2;

    /* Registro de Control */
    I2C2CONbits.SIDL = 0; // Operacion continua en modo habilitado
    I2C2CONbits.STRICT = 0; // Strict IIC reserved address rule not enabled
    I2C2CONbits.A10M = 0; // Slave Address 7-bit
    I2C2CONbits.DISSLW = 0; // High Speed Mode 400kHz
    I2C2CONbits.ACKEN = 1; // ACK controlado por el modulo en modo maestro

    I2C2CONbits.RCEN = 0; // habilita la recepcion por el IIC
    //    I2C2CONbits.ACKDT = 0; // ACK is sent
    //    I2C2CONbits.PEN = 1; // initiate stop condition controled by IIC module
    //    I2C2CONbits.RSEN = 1; // initiate restart condition controled by IIC module
    //    I2C2CONbits.SEN = 1; // initiate start condition controled by IIC module


    /* Registro de Status */


    /* Configuracion de las interrupciones */
    IEC1bits.I2C2BIE = 1; //deshabilita la interrupcion por colision de bus
    IEC1bits.I2C2SIE = 1; //deshabilita la interrupcion por esclavo
    IEC1bits.I2C2MIE = 1; //deshabilita la interrupcion por maestro


    //prioridad de interrupciones
    IPC8bits.I2C2IP = 5; //prioridad interrupcion 5
    IPC8bits.I2C2IS = 1; //subprioridad 1

    IFS1bits.I2C2BIF = 0; // Clear Interruption bus collision Flag I2C2
    IFS1bits.I2C2SIF = 0; // Clear Interruption Slave Flag I2C2
    IFS1bits.I2C2MIF = 0; // Clear Interruption Master Flag I2C2


    /* Habilita el modulo */
    // INTEnableSystemMultiVectoredInt(); //se habilitan las interrupciones con varios vectores

    /* Registro de Control */
    I2C2CONbits.ON = 1; //habilita el modulo I2C


}

/*******************************************************************************
 * Name: I2C2_Com                                                              *
 * Desc: send vars and first data                                              *
 * Parameter: _devAddr, _memAddr, _dataTx, _dataRx, *_Tx, *_Rx                 *
 * Return: None                                                                *
 *******************************************************************************/
void I2C2_Com(unsigned char _devAddr, unsigned char _memAddr, unsigned char _dataTx,
        unsigned char _dataRx, unsigned char *_Tx, unsigned char *_Rx) {

    // carga de variables
    dev_addr = _devAddr;
    mem_addr = _memAddr;
    counter_tx = _dataTx;
    counter_rx = _dataRx;
    ptr_tx = _Tx;
    ptr_rx = _Rx;


    if (IIC2_State == IIC_Idle) {
        // se genera el Start y se envia el primer dato
        I2C2_START();
        IIC2_State = IIC_Start;

    }

}

/*******************************************************************************
 * Name: _I2C2InterruptHandler                                                   *
 * Desc: Interrupt SCI1 Module                                                 *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void __attribute__((interrupt(ipl5AUTO), vector(_I2C_2_VECTOR)))_I2C2InterruptHandler(void) {
    unsigned int status;

    status = I2C2STAT;


    // reconocimento de la interrupcion
    if (IFS1bits.I2C2MIF == 1) {//si hubo interrupcion por transmision
        IFS1bits.I2C2MIF = 0; // external interrupt SCI1 Tx flag reset

        I2C2TX_ISR();

    }
    if (IFS1bits.I2C2SIF == 1) { //si hubo interrupcion por recepcion
        IFS1bits.I2C2SIF = 0; // external interrupt SCI1 Rx flag reset

        I2C2RX_ISR();

    }
    if (IFS1bits.I2C2BIF == 1) { //si hubo interrupcion por error
        IFS1bits.I2C2BIF = 0; //borra la bandera de interrupcion por error
    }
}

/*******************************************************************************
 * Name: _I2C2TX_ISR                                                           *
 * Desc: Interrupt Service Routine I2C2 TX Module                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void I2C2TX_ISR(void) {

    switch (IIC2_State) {
        case IIC_Start:
            (void) I2C2CONbits.SEN; // limpia la bandera de start
            I2C2TRN = dev_addr & IIC_WRITE_MASK; // envia la direccion del dispositivo para escritura
            IIC2_State = IIC_WriteDevAddr;
            break;

        case IIC_WriteDevAddr:
            // (void)I2C2STATbits.TRSTAT; // limpia la bandera de transmision en progreso
            // (void)I2C2STATbits.ACKSTAT; // recupera el ACK de la comunicacion

            if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                I2C2TRN = mem_addr; // envia la direccion de memoria del dispositivo para escritura
                IIC2_State = IIC_MemAddr;
                // }
            }
            break;

        case IIC_MemAddr:

            if (counter_tx) {
                counter_tx--;
                if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                    // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                    I2C2TRN = *(ptr_tx)++; // envia la cadena de datos
                    // }
                }
            } else {
                if (counter_rx) {
                    if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                        // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                        I2C2_RESTART(); // envia secuencia de restart
                        IIC2_State = IIC_Restart;
                        // }
                    }
                } else {
                    if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                        // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                        I2C2_STOP(); // se envia la secuencia de stop
                        IIC2_State = IIC_Stop;
                        // }
                    }
                }

            }
            break;

        case IIC_Restart:
            (void) I2C2CONbits.RSEN; // limpia la bandera de restart
            I2C2TRN = dev_addr | IIC_READ_MASK; // envia la direccion del dispositivo para lectura
            // I2C2_RX_ENABLE(); // habilita la lectura de datos
            IIC2_State = IIC_ReadDevAddr;
            break;

        case IIC_Stop:
            (void) I2C2CONbits.PEN; // limpia la bandera de stop
            IIC2_State = IIC_Idle;
            fl_i2c2ProcRx = TRUE;
            break;

        case IIC_ReadDevAddr:
            if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                I2C2_RX_ENABLE(); // habilita la lectura de datos
                IIC2_State = IIC_ReadData;
                // }
            }
            break;

        case IIC_ReadData:

            if (counter_rx) { // se esperan datos
                if (!I2C2CONbits.RCEN) {
                    if (counter_rx == 1) {
                        I2C2_NACK(); // se envia el Nack
                        I2C2_ACKEN();
                        IIC2_State = IIC_Nack;
                    } else {
                        I2C2_ACK(); // se envia el Ack
                        I2C2_ACKEN();
                        IIC2_State = IIC_Ack;
                    }
                }
                // almacenamos datos en el vector
                *(ptr_rx)++ = I2C2RCV;
                counter_rx--;
            }
            break;

        case IIC_Ack:
            (void) I2C2CONbits.ACKEN; // limpia la bandera del ACK
            I2C2_RX_ENABLE(); // habilita la lectura de datos
            IIC2_State = IIC_ReadDevAddr;
            break;

        case IIC_Nack:
            (void) I2C2CONbits.ACKEN; // limpia la bandera del ACK
            IIC2_State = IIC_Stop;
            (void) I2C2CONbits.PEN; // limpia la bandera de stop
            IIC2_State = IIC_Idle;
            fl_i2c2ProcRx = TRUE;
            break;

    }

}

/*******************************************************************************
 * Name: _I2C2RX_ISR                                                           *
 * Desc: Interrupt Service Routine I2C2 RX Module                              *
 * Parameter: None                                                             *
 * Return: None                                                                *
 *******************************************************************************/
void I2C2RX_ISR(void) {


    switch (IIC2_State) {

        case IIC_Stop:
            (void) I2C2CONbits.PEN; // limpia la bandera de stop
            IIC2_State = IIC_Idle;
            fl_i2c2ProcRx = 1;
            break;

        case IIC_ReadDevAddr:
            if (I2C2STATbits.TRSTAT == 0) { // limpia la bandera de transmision en progreso
                // if (I2C2STATbits.ACKSTAT == 1) { // recupera el ACK de la comunicacion
                I2C2_RX_ENABLE(); // habilita la lectura de datos
                IIC2_State = IIC_ReadData;
                // }
            }
            break;

        case IIC_ReadData:
            if (counter_rx) { // se esperan datos
                if (!I2C2CONbits.RCEN) {
                    if (counter_rx == 1) {
                        I2C2_NACK(); // se envia el Nack
                        I2C2_ACKEN();
                        IIC2_State = IIC_Nack;
                    } else {
                        I2C2_ACK(); // se envia el Ack
                        I2C2_ACKEN();
                        IIC2_State = IIC_Ack;
                    }
                }
                // almacenamos datos en el vector
                *(ptr_rx)++ = I2C2RCV;
                counter_rx--;
            }
            break;

        case IIC_Ack:
            (void) I2C2CONbits.ACKEN; // limpia la bandera del ACK
            I2C2_RX_ENABLE(); // habilita la lectura de datos
            IIC2_State = IIC_ReadDevAddr;
            break;

        case IIC_Nack:
            (void) I2C2CONbits.ACKEN; // limpia la bandera del ACK
            IIC2_State = IIC_Stop;
            (void) I2C2CONbits.PEN; // limpia la bandera de stop
            IIC2_State = IIC_Idle;
            fl_i2c2ProcRx = TRUE;
            break;

    }

}




