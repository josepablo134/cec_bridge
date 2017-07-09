#include "RegConfiguration.h"
#ifndef REGCONFIGURATION_C
#define REGCONFIGURATION_C

//void _StartMessage_(void){
//    UART_puts("Hi\n");
//}
void UART_puts(const char *c){
        while(*c){
            writeByte(*c++);
        }
    }

//void writeByte(unsigned char c){
//        while(!TXIF){}
//        TXREG=c;
//        while(!TXIF){}
//    }
#endif