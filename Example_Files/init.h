/* 
 * File:   init.h
 * Author: FING150628
 *
 * Created on May 29, 2015, 4:29 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif


#ifndef PIC32MX795F512L
#define PIC32MX795F512L
#endif


    // con este define se elije limpiar los vectores de datos
#ifndef ERASEDATA
#define ERASEDATA
#endif

#ifndef COMILLAS
#define COMILLAS
#endif

    /** ****************************************************************************
     ** **************** INIT CONFIG ***********************************************
     ** ****************************************************************************/
    //#include <plib.h>


#ifdef PIC32MX795F512L
#include <p32xxxx.h>
    // #include "pic32mx.h"
    // #include "p32mx795f512l.h"
    // #include <sys/attribs.h>
#endif



    /** ****************************************************************************
     ** **************** STATES DEFINES ********************************************
     ** ****************************************************************************/
#define TRUE                            1
#define FALSE                           0
#define INPUT                           1
#define OUTPUT                          0
#define HIGH                            1
#define LOW                             0

#define NULL_DATA                       0


    /** ****************************************************************************
     ** **************** MODOS DE OPERACION WIFI ***********************************
     ** ****************************************************************************/
#define SLAVE                           0
#define MASTER                          1


    /** ****************************************************************************
     ** **************** DEFINITIONS ***********************************************
     ** ****************************************************************************/
#ifdef PIC32MX795F512L
#define FOSC                        8000000                 // Crystal de 8 MHz
#define PLL                              20                 // PLL Escogido
#define DIV                               2                 // PLL Divisor
#define FCY                    FOSC*PLL/DIV                 // FCY, Frecuencia de BUS   80MHz
#endif


    /** ****************************************************************************
     ** **************** FUNCTIONS *************************************************
     ** ****************************************************************************/

    //        void PLL_Init(void);

    /** ****************************************************************************
     ** **************** FLAGS *****************************************************
     ** ****************************************************************************/
    // Bits con el fin de manejar diversas banderas de programa

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

    // Bits con el fin de manejar diversos estados de programa

    typedef union {
        unsigned int state;

        struct {
            unsigned char state00 : 4;
            unsigned char state01 : 4;
            unsigned char state02 : 4;
            unsigned char state03 : 4;
            unsigned char state04 : 4;
            unsigned char state05 : 5;
            unsigned char state06 : 4;
            unsigned char state07 : 3;
        } Nibbles;

    } STR_STATES;



    extern volatile STR_FLAGS _Events;
#define fl_proc_rx1               _Events.Bits.flag00 //ok
#define fl_proc_rx2               _Events.Bits.flag01 //ok
#define fl_proc_rx3               _Events.Bits.flag02 //ok
#define fl_proc_rx4               _Events.Bits.flag03 //ok
#define fl_proc_rx5               _Events.Bits.flag04 //ok
#define fl_proc_rx6               _Events.Bits.flag05 //ok
    //#define fl_06               _Events.Bits.flag06 //ok
    //#define fl_07               _Events.Bits.flag07 //ok
    //#define fl_08               _Events.Bits.flag08 //ok
    //#define fl_09               _Events.Bits.flag09 //ok
#define fl_i2c2ProcRx             _Events.Bits.flag10 //ok
    //#define fl_11               _Events.Bits.flag11 //ok
    //#define fl_12               _Events.Bits.flag12 //ok
#define fl_TPM1                   _Events.Bits.flag13 //ok
#define fl_TPM2                   _Events.Bits.flag14 //ok
#define fl_SPI1                   _Events.Bits.flag15 //ok
#define fl_ECGData                _Events.Bits.flag16 //ok // Bandera para permitir la concatenacion de ECG si hay datos
#define fl_SPOData                _Events.Bits.flag17 //ok // Bandera para permitir la concatenacion de SPO si hay datos
#define fl_NIPData                _Events.Bits.flag18 //ok // Bandera para permitir la concatenacion de NIP si hay datos
#define fl_VENData                _Events.Bits.flag19 //ok // Bandera para permitir la concatenacion de VEN si hay datos
    //#define fl_20               _Events.Bits.flag20 //ok
#define fl_timerHigh              _Events.Bits.flag21 //ok // Bandera para verificar si es alta o baja frecuencia en el timer
    //#define fl_22               _Events.Bits.flag22 //ok
    //#define fl_23               _Events.Bits.flag23 //ok
#define fl_openCom                _Events.Bits.flag24 //ok
#define fl_factoryMode            _Events.Bits.flag25 //ok // Bandera para iniciar configuracion de fabrica en WIFI
#define fl_WlanConfig             _Events.Bits.flag26 //ok // Bandera para iniciar configuracion de WLAN en WIFI
#define fl_DNSConfig              _Events.Bits.flag27 //ok // Bandera para iniciar configuracion de DNS en WIFI
    //#define fl_28               _Events.Bits.flag28 //ok
#define fl_wr_vnc1l               _Events.Bits.flag29 //ok // Bandera para iniciar escritura en modulo VDIP
#define fl_wrDataSPI              _Events.Bits.flag30 //ok // Bandera para iniciar escritura en modulo SPI
#define fl_openPort               _Events.Bits.flag31 //ok // Bandera que indica que el puerto esta abierto



    extern volatile STR_FLAGS _ModulesEvents;
#define fl_activateECG               _ModulesEvents.Bits.flag00 //ok // status de ECG
#define fl_activateSPO               _ModulesEvents.Bits.flag01 //ok // status de SPO
#define fl_activateNIP               _ModulesEvents.Bits.flag02 //ok // status de NIP
    //#define fl_03               _ModulesEvents.Bits.flag03 //ok
    //#define fl_04               _ModulesEvents.Bits.flag04 //ok
    //#define fl_05               _ModulesEvents.Bits.flag05 //ok
    //#define fl_06               _ModulesEvents.Bits.flag06 //ok
#define fl_MassStorage            _ModulesEvents.Bits.flag07 //ok
    //#define fl_08               _ModulesEvents.Bits.flag08 //ok
    //#define fl_09               _ModulesEvents.Bits.flag09 //ok
#define fl_ECGReady               _ModulesEvents.Bits.flag10 //ok // bandera que indica que se muestrearon los datos de ECG y se concatenaron
#define fl_SPOReady               _ModulesEvents.Bits.flag11 //ok // bandera que indica que se muestrearon los datos de SPO y se concatenaron
#define fl_NIPReady               _ModulesEvents.Bits.flag12 //ok // bandera que indica que se muestrearon los datos de SPO y se concatenaron
    //#define fl_13               _ModulesEvents.Bits.flag13 //ok
#define fl_SerialSend             _ModulesEvents.Bits.flag14 //ok // bandera para enviar datos por serial
#define fl_MassStrSend            _ModulesEvents.Bits.flag15 //ok // bandera para enviar datos a Mass Storage
    //#define fl_16               _ModulesEvents.Bits.flag16 //ok
    //#define fl_17               _ModulesEvents.Bits.flag17 //ok
#define fl_wifiSend               _ModulesEvents.Bits.flag18 //ok // bandera para iniciar el envio por wifi
    //#define fl_19               _ModulesEvents.Bits.flag19 //ok
    //#define fl_20               _ModulesEvents.Bits.flag20 //ok
    //#define fl_21               _ModulesEvents.Bits.flag21 //ok
    //#define fl_22               _ModulesEvents.Bits.flag22 //ok
    //#define fl_23               _ModulesEvents.Bits.flag23 //ok
    //#define fl_24               _ModulesEvents.Bits.flag24 //ok
    //#define fl_25               _ModulesEvents.Bits.flag25 //ok
#define fl_nfirsted1              _ModulesEvents.Bits.flag26 //ok // bandera para indicar que la cadena ed1 ya tiene datos
#define fl_nfirsted2              _ModulesEvents.Bits.flag27 //ok // bandera para indicar que la cadena ed2 ya tiene datos
#define fl_nfirsted3              _ModulesEvents.Bits.flag28 //ok // bandera para indicar que la cadena ed3 ya tiene datos
#define fl_nfirstspo              _ModulesEvents.Bits.flag29 //ok // bandera para indicar que la cadena spo ya tiene datos
    //#define fl_30               _ModulesEvents.Bits.flag30 //ok
    //#define fl_31               _ModulesEvents.Bits.flag31 //ok



    extern volatile STR_STATES _StateEvents;
#define st_ECG                    _StateEvents.Nibbles.state00 //ok
#define st_SPO                    _StateEvents.Nibbles.state01 //ok
#define st_NIP                    _StateEvents.Nibbles.state02 //ok
#define st_vdip                   _StateEvents.Nibbles.state03 //ok
    //#define st_04               _StateEvents.Nibbles.state04 //ok
#define st_WIFI                   _StateEvents.Nibbles.state05 //ok
    //#define st_06               _StateEvents.Nibbles.state06 //ok
#define fl_SendCmdWifi            _StateEvents.Nibbles.state07 //ok



#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */

