//<editor-fold defaultstate="collapsed" desc="_CONFIG_BITS_">
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
//</editor-fold>
#define _XTAL_FREQ  20000000
#include <pic16f628a.h>
#include <stdbool.h>
#include "InterruptControl.h"
#include "RegConfiguration.h"
#include "CEC_DATA_STRUCT.h"
#include "CEC_CONTROL.h"
#include "CEC_SENDER_CONTROLLER.h"

//<editor-fold defaultstate="collapsed" desc="ERROR _MSG_">
//[0] - Sin errores
//[1] - Error de transmisión por el puerto CEC
//[2] - Error de recepción por el puerto CEC
//[3] - Error de recepción por el puerto UART
//[4] - Esperando paquete
//[5] - No espacio para el paquete
//</editor-fold>

#ifndef CEC_TMR_BITS
    #define clock_data  CCPR1
    #define START_B_A   17500
    #define START_B_B   19500
    #define B_1_A       2000
    #define B_1_B       4000
    #define B_0_A       6500
    #define B_0_B       8500
    #define buffer_size 11
    #define wait_interrupt_falling() {CEC_IF=0;\
                                        configCaptureCP(CCP_falling);\
                                      while(!CEC_IF){}}
    #define wait_interrupt_rising() {CEC_IF=0;\
                                      configCaptureCP(CCP_rising);\
                                      while(!CEC_IF){}}
#endif

void main(void) {
    //
    //  SALIDAS Y ENTRADAS DIGITALES
    //
    configIO();
    //
    //  CONFIGURAR UART 9600 BAUD
    //
    configUART();
    //
    //  CONFIGURAR EL TMR1
    //
    configTMR1();
    //
    //  CONFIGURAR LAS INTERRUPCIONES
    //
    configINT();
    CEC_CAPTURE_EVENT();
    asm("goto $");
}
void UART_EVENT(){
    disableCCP();
    if(uart_buffer.length<4){
        return;
    }
    unsigned int data[3] = {0,0,0};
    for(unsigned char i=0;i<3;i++){
        if(uart_buffer.data[i]>'9'){
            data[i] = (uart_buffer.data[i]+9) & 0xF;
        }else{
            data[i] = uart_buffer.data[i]-'0';
        }
    }
    if(uart_buffer.data[3]-'0'){
        //Hay un dato más
        //Limpiar y preparar buffer
        //Esperar proximo paquete
        UART_puts("==> 4\n");
        for(unsigned char i=0;i<4;i++){
            uart_buffer.data[i]=0;
            uart_buffer.length=0;
        }
        if(!CEC_PUSH_BUFFER( ((data[0]<<8)&0x3FF) +(data[1]<<4)+data[2])){
            UART_puts("==> 5\n");
            clear_buffer(&CEC_OUTPUT_BUFFER);
            uart_buffer.length=0;
            for(unsigned char i=0;i<4;i++){
                uart_buffer.data[i]=0;
                uart_buffer.length=0;
            }
            return;
        }
        return;
    }
    //
    //Es el ultimo paquete, transmitir!
    //
//    UART_puts("\nPreparando transmision\n");
    data[0] = (data[0]<<8) & 0x3FF;
    data[0] += (data[1]<<4) & 0xF0;
    data[0] += (data[2]) & 0xF;
    if(!CEC_PUSH_BUFFER(data[0])){
        UART_puts("==> 5\n");
        clear_buffer(&CEC_OUTPUT_BUFFER);
        uart_buffer.length=0;
        for(unsigned char i=0;i<4;i++){
            uart_buffer.data[i]=0;
            uart_buffer.length=0;
        }
        return;
    }
//    turnOffUART();
    if(!CEC_SEND()){
        SPEN=1;
        UART_puts("==> 1\n");
        clear_buffer(&CEC_OUTPUT_BUFFER);
        uart_buffer.length=0;
        for(unsigned char i=0;i<4;i++){
            uart_buffer.data[i]=0;
            uart_buffer.length=0;
        }
        return;
    }
//    turnOnUART();
    clear_buffer(&CEC_OUTPUT_BUFFER);
    uart_buffer.length=0;
    for(unsigned char i=0;i<4;i++){
            uart_buffer.data[i]=0;
            uart_buffer.length=0;
    }
    UART_puts("==> 0\n");
}

//void printShort(unsigned short value){
//    writeByte( HexToASCII[(value>>12) & 0xF]);
//    writeByte( HexToASCII[(value>>8) & 0xF]);
//    writeByte( HexToASCII[(value>>4) & 0xF]);
//    writeByte( HexToASCII[value & 0xF]);
//    writeByte('\n');
//}

void CEC_CAPTURE_EVENT(){
    PORTBbits.RB3 = 1;
    TRISBbits.TRISB3 = 1;
    PORTA = 0;
    unsigned short timing_buffer[buffer_size]={0,0,0,0,0,0,0,0,0,0};
    unsigned char bit_counter=0;
    unsigned short frame_buffer=0;
LOOP:
    CEC_IF=0;
    configCaptureCP(CCP_falling);
    while(!CEC_IF){}
    CEC_IF = 0;
    configCaptureCP(CCP_rising);
    while(!CEC_IF){}
    timing_buffer[bit_counter] = CCPR1;
    
    bit_counter++;
    if(bit_counter==buffer_size){
        goto SEND_DATA;
    }
    goto LOOP;
SEND_DATA:
    turnOffTMR1();
    if((timing_buffer[0]> START_B_A) && (timing_buffer[0]<START_B_B)){ 
        for(bit_counter=1;bit_counter<buffer_size;bit_counter++){
            if((timing_buffer[bit_counter]>B_1_A)\
                    &&(timing_buffer[bit_counter]<B_1_B)){
                frame_buffer<<=1;
                frame_buffer+=1;
            }else if((timing_buffer[bit_counter]>B_0_A)\
                    &&(timing_buffer[bit_counter]<B_0_B)){
                frame_buffer<<=1;
            }else{
                UART_puts("==> 2\n");
                break;
            }
        }
        UART_puts("0x0");
//        printShort(frame_buffer);
        writeByte( HexToASCII[(frame_buffer>>8) & 0xF]);
        writeByte( HexToASCII[(frame_buffer>>4) & 0xF]);
        writeByte( HexToASCII[frame_buffer & 0xF]);
        writeByte('\n');
    }else{
        UART_puts("==> 2\n");
    }
//    for(bit_counter=0;bit_counter<buffer_size;bit_counter++){
//      printShort( timing_buffer[bit_counter] );
//    } 
    bit_counter=0;
    goto LOOP;
}