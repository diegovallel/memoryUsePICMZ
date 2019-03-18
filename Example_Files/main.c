
/* 
 * File:   main.c
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <plib.h>


#ifndef PIC32MX795F512L
#define PIC32MX795F512L
#endif


#ifdef PIC32MX795F512L
#include <p32xxxx.h>
#endif

/*******************************************************************************
 **************** INCLUDES *****************************************************
 *******************************************************************************/
#include "init.h"
#include "SCI.h"
//#include "SPI.h"
#include "TPM.h"
#include "I2C.h"

#include "wifly.h"
//#include "vdip.h"
#include "max17043.h"

#include "concentData.h"
#include "adquireData.h"
#include "peripheral.h"
//#include "vdipData.h"
//#include "wiflyData.h"


#if USE_FIFO_SCI1
#include "fifo_rx1.h"
#include "fifo_tx1.h"
#endif
#if USE_FIFO_SCI2
#include "fifo_rx2.h"
#include "fifo_tx2.h"
#endif
#if USE_FIFO_SCI3
#include "fifo_rx3.h"
#include "fifo_tx3.h"
#endif
#if USE_FIFO_SCI4
#include "fifo_rx4.h"
#include "fifo_tx4.h"
#endif
#if USE_FIFO_SCI5
#include "fifo_rx5.h"
#include "fifo_tx5.h"
#endif
#if USE_FIFO_SCI6
#include "fifo_rx6.h"
#include "fifo_tx6.h"
#endif


/*******************************************************************************
 ******************** DEFINES **************************************************
 *******************************************************************************/
#ifdef PIC32MX795F512L

//#define LED1_DD             TRISBbits.TRISB0
//#define LED1_D              LATBbits.LATB0
//
//#define LED2_DD             TRISBbits.TRISB1
//#define LED2_D              PORTBbits.RB1
//
//#define LED3_DD             TRISBbits.TRISB2
//#define LED3_D              PORTBbits.RB2

#endif


//#define LED1_OUTPUT()       LED1_DD = OUTPUT
//#define LED1_ON()           LED1_D = HIGH
//#define LED1_OFF()          LED1_D = LOW
//#define LED1_TOGGLE()       LED1_D = !LED1_D
//
//#define LED2_OUTPUT()       LED2_DD = OUTPUT
//#define LED2_ON()           LED2_D = HIGH
//#define LED2_OFF()          LED2_D = LOW
//#define LED2_TOGGLE()       LED2_D = !LED2_D
//
//#define LED3_OUTPUT()       LED3_DD = OUTPUT
//#define LED3_ON()           LED3_D = HIGH
//#define LED3_OFF()          LED3_D = LOW
//#define LED3_TOGGLE()       LED3_D = !LED3_D


/*******************************************************************************
 ************* EVENTS VARIABLES ************************************************
 *******************************************************************************/
volatile STR_FLAGS _Events; // eventos de los perifericos y banderas de control
volatile STR_FLAGS _ModulesEvents; // banderas de control de los modulos
volatile STR_STATES _StateEvents; // estados de los diferentes modulos


unsigned int counterDataSecurity = 0; // contador de seguridad para parar muestre en caso que no se soliciten datos

//#if USE_FIFO_SCI6
//volatile unsigned char dataoFifo6[100];
//volatile unsigned char dataiFifo6[100];
//volatile unsigned char* dataOut6 = dataoFifo6;
//volatile unsigned char* dataIn6 = dataiFifo6;
//#endif

unsigned char jsonConvert[4800]; // Vector para almacenar la cadena JSON completa
unsigned char jsonConvertCopy[4800]; // Vector que contiene cadena JSON copia para memoria
unsigned char jsonEncript[4800]; // Vector para almacenar la cadena JSON encriptada completa
unsigned long key; // llave de encriptacion

/** ****************************************************************************
 ** ****************************************************************************
 ** **********  CONSOLIDACION DE LOS DATOS *************************************
 ** ****************************************************************************
 ** ****************************************************************************/

// vector que almacena la cadena JSON de ECG
unsigned char ecgData[3400];
// vector que almacena la cadena JSON de SPO2
unsigned char spoData[1000];
// vector que almacena la cadena JSON de NIBP
unsigned char nipData[400];
// vector que almacena la cadena JSON de VENT
unsigned char venData[1000];


/** ****************************************************************************
 ** ****************************************************************************
 ** **********  ADQUISICION DE LOS DATOS ***************************************
 ** ****************************************************************************
 ** ****************************************************************************/

// vectores para adquisicion de datos desde modulo ECG
unsigned char ed1ECGData[1200]; // Derivacion 1
unsigned char ed2ECGData[1200]; // Derivacion 2
unsigned char ed3ECGData[1200]; // Derivacion 3
unsigned char efeECGData[120]; // Frecuencia ECG
unsigned char sclECGData[120]; // Escala ECG
unsigned char smpECGData[120]; // Muestreo ECG

// vectores para adquisicion de datos desde modulo SPO
unsigned char spoSPOData[1000]; // Senal SPO
unsigned char efeSPOData[120]; // Frecuencia SPO
unsigned char satSPOData[120]; // Saturacion SPO
unsigned char smpSPOData[120]; // Muestreo ECG

// vectores para adquisicion de datos desde modulo NIP
unsigned char npsNIPData[120]; // Presion sistolica
unsigned char npdNIPData[120]; // Presion diastolica
unsigned char npmNIPData[120]; // Presion media
unsigned char nfpNIPData[120]; // Frecuencia Cardiaca

// vectores para adquisicion de estado de carga de bateria (SOC)
unsigned char batLevel[8];
unsigned char batLevelPrint[8];

// vector que almacena la longitud a escribir
unsigned char lengText[8];



#if USE_FIFO_SCI4
volatile unsigned char dataoFifo4[100];
volatile unsigned char dataiFifo4[100];
volatile unsigned char* dataOut4 = dataoFifo4;
volatile unsigned char* dataIn4 = dataiFifo4;
#endif

#if USE_FIFO_SCI5
volatile unsigned char dataoFifo5[100];
volatile unsigned char dataiFifo5[100];
volatile unsigned char* dataOut5 = dataoFifo5;
volatile unsigned char* dataIn5 = dataiFifo5;
#endif

/*******************************************************************************
 ***************** DATOS PREGRABDOS ********************************************
 *******************************************************************************/
unsigned char date[25] = "181120141503453";
unsigned char deviceID[25] = "0001";
unsigned char counter[25] = "0003";

unsigned char variable[25] = "hello";

unsigned char netName[25] = "GIBIC";
//unsigned char netName[25] = "Black$River$Lab$Network";
unsigned char netPass[25] = "gibic419BRL";
//unsigned char netPass[25] = "BRLgibic";

unsigned char netDns[25] = "whamupb.iforware.com";
unsigned char netPort[25] = "8080";
unsigned char netIp[25] = "165.225.129.253";

unsigned char sampleECG[] = "250";
unsigned char sampleSpo[] = "250";

//unsigned char venfs[] = "20";
//unsigned char spa[] = "0,4000,";
//unsigned char sfi[] = "3709,3890,";
//unsigned char svc[] = "3709,109,";
//unsigned char co2[] = "3709,109,";
//unsigned char ppa[] = "1";
//unsigned char pme[] = "2";
//unsigned char pfi[] = "3";
//unsigned char vme[] = "4";
//unsigned char rie[] = "5";
//unsigned char frt[] = "6";
//unsigned char pep[] = "7";
//unsigned char coz[] = "8";

unsigned char archivo[] = "prueba2.txt";
unsigned char texto[] = "42[\"hello\",{\"idD\":\"0001\",\"con\":\"0003\",\"fec\":"
        "\"181120141503453\",\"dat\":{\"ecg\":{\"dat\":{\"ed1\":[11391,11418,11444,11456,"
        "11475,11506,11539,11596,11660,11418,11430,11456,11466,11495,11524,11574,11640,11407,"
        "11421,11455,11459,11483,11514,11555,11619],\"ed2\":[11391,11418,11444,11456,11475,11506,"
        "11539,11596,11660,11418,11430,11456,11466,11495,11524,11574,11640,11407,11421,11455,11459,"
        "11483,11514,11555,11619],\"ed3\":[11391,11418,11444,11456,11475,11506,11539,11596,11660,"
        "11418,11430,11456,11466,11495,11524,11574,11640,11407,11421,11455,11459,11483,11514,-1555,"
        "11619],\"efe\":53,\"scl\":6},\"fs_\":250},\"spo\":{\"dat\":{\"sp_\":[2336,2334,2329,2325,2322,"
        "2323,2325,2326,2324,2319,2313,2308,2303,2297,2290,2284,2279,2277,2274,2270,2261,2251,2244,2242,"
        "2241],\"ps_\":10054,\"fp_\":10053},\"fs_\":250},\"nip\":{\"dat\":{\"nps\":1120,\"npd\":2070,\"npm\":3083"
        ",\"nfp\":4053}},\"ven\":{\"dat\":{\"spa\":[0,4000],\"sfi\":[3709,3890],\"svc\":[3709,109],\"co2\":[3709,"
        "109],\"ppa\":1,\"pme\":2,\"pfi\":3,\"vme\":4,\"rie\":5,\"frt\":6,\"pep\":7,\"coz\":8},\"fs_\":20}}}]";
unsigned char longitud[] = "987";

unsigned char* vecSamplOld; // contador para llenar los vectores sample
unsigned char* vecSamplNew; // contador para llenar los vectores sample





//
//char fifoOut[10];
//char fifoIn[10];
char * dataOut = 0;
//char * dIn = (char*)&fifoIn;

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned int da = 0;

    INTEnableSystemMultiVectoredInt();

    /***************************************************************************
     ********************** INICIALIZA PERIFERICOS *****************************
     ***************************************************************************/
    SCI1_Init();
    SCI2_Init();
    SCI3_Init();
    SCI4_Init();
    SCI5_Init();
    SCI6_Init();

    Fifo_Rx1_Init();
    Fifo_Tx1_Init();
    Fifo_Rx2_Init();
    Fifo_Tx2_Init();
    Fifo_Rx3_Init();
    Fifo_Tx3_Init();
    Fifo_Rx4_Init();
    Fifo_Tx4_Init();
    Fifo_Rx5_Init();
    Fifo_Tx5_Init();
    Fifo_Rx6_Init();
    Fifo_Tx6_Init();


    TPM1_Init(TIMER_1_LOW);
    TPM2_Init();

    //    SPI1_Init();
    //
    //    Fifo_Sdo1_Init();
    //

    I2C2_Init();
    MAX_32Alert(); // configura alerta de bateria en 32%


    // captura frecuencia de bus
    da = FCY;

    //    // llena vector de muestreo
    //    vecSamplOld = sampleECG;
    //    vecSamplNew = smpECGData;
    //
    //    while (*vecSamplOld != 0) {
    //        *vecSamplNew = *vecSamplOld;
    //        vecSamplNew++;
    //        vecSamplOld++;
    //    }
    //
    //    vecSamplOld = sampleSpo;
    //    vecSamplNew = smpSPOData;
    //
    //    while (*vecSamplOld != 0) {
    //        *vecSamplNew = *vecSamplOld;
    //        vecSamplNew++;
    //        vecSamplOld++;
    //    }


    // inicia concatenacion de prueba
    // key = 0xA5D2E045;
    // key = 0xAAB5EE02;
    //
    // ecgConcentData(ecgData, datosNum1, datosNum2, datosNum3, efe, scl, sampleECG);
    // spoConcentData(spoData, datosNumSpo, spops_, spofp_, sampleSpo);
    // nipConcentData(nipData, nps, npd, npm, nfp);
    // venConcentData(venData, spa, sfi, svc, co2, ppa, pme, pfi, vme, rie, frt, pep, coz, venfs);

    // concatWebSocketProtocol(jsonConvert, variable, deviceID, counter, date, ecgData, spoData, nipData, venData);
    // convertWebSocketProtocol(key, jsonEncript, jsonConvert, strlen(jsonConvert));

    fl_SendCmdWifi = FALSE;
    fl_MassStorage = FALSE;

    wifiOperationMode(MASTER); // configura Wifi en modo maestro


    fl_activateECG = TRUE; // activa muetreo de ECG
    fl_activateSPO = TRUE; // activa muestreo de SPO
    fl_activateNIP = TRUE; // activa muestreo de NIP


    ledsInit(); // funcion para inicializar puertos de salida de los LEDs RGB


    for (;;) {

        // interrupcion por TPM1.-
        if (fl_TPM1) {
            fl_TPM1 = FALSE;

            // espacio para programar
        }

        // interrupcion por TPM2.-
        if (fl_TPM2) {
            fl_TPM2 = FALSE;

            // espacio para programar

            // funcion que evalua el estado de los modulos para la medicion y solicitud de datos
            evaluateStateOfModules(); // evalua el estado de los modulos para realizar la adquisicion de datos
            //
            //            // funcion que evalua el estado de la transmision de datos al modulo wifi
            //            evaluateStateOfWifi(netName, netPass, netDns, netPort); // evalua el estado en el que se encuentra la transmision por wifi

            // evalua la condicion de la bateria, mostrada en leds
            if (fl_sensSOC) {

                evaluateVisualStateBat(batLevel);
            }

            // medicion de estado de carga de bateria
            evaluateStateOfCharge(batLevel); // evalua el estado de carga de la bateria

        }

        // recepcion con fifos desde modulo ECG
        // interrupcion por Rx serial, solo cuando llega la (,).-
        if (fl_proc_rx1) {
            fl_proc_rx1 = FALSE;

            // espacio para programar

            // procesa datos provenientes del modulo ECG
            processDataEcg(ecgData, ed1ECGData, ed2ECGData, ed3ECGData, efeECGData, sclECGData, sampleECG);

        }

        // recepcion con fifos desde modulo SPO
        // interrupcion por Rx serial, solo cuando llega la (,).-
        if (fl_proc_rx2) {
            fl_proc_rx2 = FALSE;

            // espacio para programar

            // procesa datos provenientes del modulo SPO
            processDataSPO(spoData, spoSPOData, satSPOData, efeSPOData, smpSPOData);

        }

        // recepcion con fifos desde modulo NIP
        // interrupcion por Rx serial, solo cuando llega la (,).-
        if (fl_proc_rx3) {
            fl_proc_rx3 = FALSE;

            // espacio para programar

            // procesa datos provenientes de NIP
            processDataNIP(nipData, npsNIPData, npdNIPData, npmNIPData, nfpNIPData);
        }

        // recepcion con fifos
        // interrupcion por Rx serial.-
        if (fl_proc_rx4) {
            fl_proc_rx4 = FALSE;

            dataIn4 = dataiFifo4;


            while (Fifo_Rx4_Get(dataIn4)) {
                dataIn4++;
            }

            dataIn4 = dataiFifo4;

            if (*dataIn4 == 0x4F) {//enviar
                fl_wifiSend = TRUE;
            }
            if (*dataIn4 == 0x43) {//cerrar
                fl_wifiSend = FALSE;
            }


            dataOut5 = dataoFifo5;
            while ((*dataOut5 != 0) && (Fifo_Tx5_Put(*dataOut5))) {
                *dataOut5 = 0;
                dataOut5++;
            }

            // espacio para programar

            //            // procesa la respuesta recibida desde el wifi;
            //            processWifiResponse(netName, netPass, netDns, netPort);
        }

        // recepcion con fifos
        // interrupcion por Rx serial.-
        if (fl_proc_rx5) {
            fl_proc_rx5 = FALSE;

            // espacio para programar

            //            // procesa las solicitudes enviadas desde el PC
            //            evaluateFt232Query(netName, netPass, netDns, netPort, archivo, longitud, texto);
        }

        // recepcion con fifos
        // interrupcion por Rx serial.-
        if (fl_proc_rx6) {
            fl_proc_rx6 = FALSE;

            // espacio para programar

        }

        // interrupcion por SPI Rx.-
        if (fl_SPI1) { //si hubo una interrupcion de spi
            fl_SPI1 = FALSE; //borra la bandera de interrupcion

            // espacio para programar

        }

        // interrupcion por IIC Rx.-
        if (fl_i2c2ProcRx) {
            fl_i2c2ProcRx = FALSE;

            // espacio para programar

            //            // imprime SOC en serial 5
            //            // batLevel[2] = 0x0D;
            //
            //            (void) itoa(batLevelPrint, (int) batLevel[0], 10);
            //            // (void) strcat(batLevelPrint, "\r");
            //
            //            // dataOut5 = batLevelPrint;
            //            // while ((*dataOut5 != 0) && (Fifo_Tx5_Put(*dataOut5))) {
            //            // *dataOut5 = 0;
            //            // dataOut5++;
            //            // }
        }

    }

    /* END */
    return (EXIT_SUCCESS);
}
