#include "CEC_SENDER_CONTROLLER.h"
    //
    // TOTAL DEL CICLO INICIO 
    //      4.3 - 4.5 - 4.7 ms
    //     TIEMPO DEL PULSO DE INICIO
    //          3.5 - 3.7 - 3.9 ms AS LOW
    
    // TOTAL DEL CICLO DE BIT
    //      2.05 - 2.4 - 2.75 ms
    //     TIEMPO DEL PULSO BAJO PARA 0 LOGICO
    //         1.3 - 1.5 - 1.7 ms
    //     TIEMPO DEL PULSO BAJO PARA 1 LOGICO
    //          0.4 - 0.6 - 0.8 ms
    //     TIEMPO PARA EL PROXIMO BIT     
    //          (TOTAL DEL CICLO) - (TIEMPO DE 1 o 0 LOGICO) ms
#define _XTAL_FREQ  20000000
#include <xc.h>
#include <pic16f628a.h>

bool CEC_SC_SENDBUFFER(CEC_BUFFER* buffer){
    if(!(buffer->frames[buffer->length-1].EOM)){
        //El ultimo bit no tiene EOM?
        return false;
    }
    TRISBbits.TRISB3 = 0;   //Configurar como salida
    PORTBbits.RB3 = 0;
    __delay_us(3700);
    PORTBbits.RB3 = 1;
    __delay_us(800);
    
    for(unsigned char frame=0 ; frame<buffer->length ; frame++){
        unsigned int data = (buffer->frames[frame].data<<2)+\
                            (buffer->frames[frame].EOM<<1)+\
                            (buffer->frames[frame].ACK);
        for(unsigned char bits=0 ; bits<10 ; bits++){
            // TRANSMITE UN 1
            if( (data<<bits)&0x200 ){
                PORTBbits.RB3 = 0;
                __delay_us(600);
                PORTBbits.RB3 = 1;
                __delay_us(1800);
            }else{
            // TRANSMITE UN 0
                PORTBbits.RB3 = 0;
                __delay_us(1500);
                PORTBbits.RB3 = 1;
                __delay_us(900);
            }
        }
    }
    //
    //  PASO 0 ENVIAR BIT DE INICIO
    //
    TRISBbits.TRISB3 = 1;//Configurar como entrada
    return true;
}