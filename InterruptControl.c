#include "InterruptControl.h"
//
//  INTERRUPT SERVICE ROUTINE
//
void interrupt ISR(void){
    //
    //  UART INT
    //
    if(RCIF){
        volatile unsigned char rx = RCREG;
        //Restart
            if(rx == 'R'){asm("goto 0x00");}
        //Atencion - Interrupción
            if(rx == 'I'){
                clear_buffer(&CEC_OUTPUT_BUFFER);
                uart_buffer.length=0;
                UART_puts("OK\n");
                return;
            }
        if(uart_buffer.length<4){
            uart_buffer.data[uart_buffer.length] = rx;
            uart_buffer.length++;
            UART_EVENT();
        }else{
            UART_puts("==> 3\n");
            uart_buffer.length=0;
        }
        return;
    }
    //
    //  TMR1 INT
    //
    if(TMR1IF){
        TMR1IF = 0;
        asm("goto 0x00");
    }
    //
    //  CCP1 INT
    //
    if(CCP1IF){
        CCP1IF = 0;
        CEC_IF = 1;
        PORTA = 1;
        PORTA = 0;
    }
    return;
}