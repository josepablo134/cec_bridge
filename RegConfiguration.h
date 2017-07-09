#define _XTAL_FREQ  20000000
#include <pic16f628a.h>
#include <xc.h>
#include <stdbool.h>
#ifndef REGCONFIGURATION_H
#define REGCONFIGURATION_H
    unsigned volatile char HexToASCII[16] = \
    {'0','1','2','3',\
    '4','5','6','7',\
    '8','9','A','B',\
    'C','D','E','F'};
/**
 * configIO
 * Configura el puerto A, y los bits Rx y Tx como entrada y salida.
 *  */
    #define configIO()      {PORTA = 0x01;\
                            TRISA = 0;\
                            PORTAbits.RA0 = 1;\
                            PORTB   = 0x00;\
                            TRISBbits.TRISB0 = 1;\
                            TRISBbits.TRISB2 = 0;}
/**
* turnOnTMR1
*   Inicializa el conteo del TMR1
*/
    #define turnOnTMR1(){PIR1bits.TMR1IF=0;TMR1=0x00;TMR1ON=1;TMR1IE=1;}
/**
 * configCaptureCP
 *  @param    Capturemode true: capture every rising edge, false: other case
 * Configura el CCP1 en modo captura
 * */
    #define CCP_falling         false
    #define CCP_rising          true
    #define configCaptureCP(Capturemode){PORTBbits.RB3 = 1;\
                                        TRISBbits.TRISB3 = 1;\
                                        TMR1 = 0;\
                                        PIE1bits.CCP1IE=0;\
                                        PIR1bits.CCP1IF=0;\
                                        CCP1CON=0;\
                                            if(Capturemode)\
                                                {CCP1CON = 0b0101;}\
                                            else\
                                                {CCP1CON = 0b0100;}\
                                        PIE1bits.CCP1IE=1;\
                                        turnOnTMR1();\
                                        }
 /**
 * configInt
 *  Configura las interrupciones del Rx y CCP1
 * 
 */
    #define configINT()     {   PIR1 = 0x0;\
                                INTCON = 0b11000000;\
                                PIE1 = 0b00100101;\
                                PIE1bits.TMR1IE=1;\
                                PIE1bits.CCP1IE=1;}
 /**
 * configUART
 *  Configura el puerto UART a 9600 baudios, high speed, 8 bits sin bit
 *  de paridad como entrada y salida.
 */
    #define configUART()    {TXSTA = 0x24;\
                            RCSTA = 0x90;\
                            SPBRG = 129;}//  Interrupt
/**
 * configTMR1
 *  Configura el reloj del TMR1 como el FOSC/4/8 y realiza
 *  una precarga sin comenzar el conteo
 */
    #define configTMR1()    {PIE1bits.TMR1IE = 1;\
                            T1CON = 0b00000000;\
                            TMR1 = 0x0;}
/**
* turnOnTMR1
*   Inicializa el conteo del TMR1
*/
    #define turnOnTMR1(){PIR1bits.TMR1IF=0;TMR1=0x00;TMR1ON=1;TMR1IE=1;}
/**
* turnOffTMR1
*   Detiene el conteo del TMR1
*/
    #define turnOffTMR1()   {TMR1ON=0;}
/**
 * turnOnUART
 *  Activa el modulo uart
 * @param 
 */
    #define turnOnUART()    {RCSTA= 0x90;}
/**
 * turnOffUART
 *  Detiene el modulo uart
 * @param 
 */
    #define turnOffUART()   {RCSTA = 0x10;}
/**
 * disableCCP
 * Desactiva el modulo CCP1
 */
    #define disableCCP(){PIE1bits.CCP1IE=0;PIR1bits.CCP1IF=0;CCP1CON=0;turnOffTMR1();}
/**
* write
*   Escribe un byte en el registro de transmisión del puerto serial
* @param    char    un byte para transmitir 
*/    
    #define writeByte(C){ while(!TXIF){} TXREG=C; while(!TXIF){} }
/**
 * puts
 *  Flujo de bytes en el registro de transmisión del puerto serial
 * @param char*     el apuntador al primer byte de un arreglo de bytes 
 */
void UART_puts(unsigned const char*);
/**
 * _StartMessage_
 * Mensaje de inicio por el puerto serial.
 * Simplemente un mensaje de bienvenida.
 */
//void _StartMessage_(void);
/**
 * UART_EVENT
 * Evento uart que permite re enviar
 * los datos del uart por el puerto CEC.
 * Cambia el estado de la variable INT_STATE
 * INT_STATE @cambio_a  0x00
 */
void UART_EVENT();
/**
 * CEC_CAPTURE_EVENT
 * Evento de captura por el puerto CEC para
 * preparar reenvio por el puerto UART.
 * Cambia el estado de la variable INT_STATE.
 * INT_STATE @cambio_a  0x00
 * INT_STATE @cambio_a  0b011
 */
void CEC_CAPTURE_EVENT();
//void printShort(unsigned short);
#endif