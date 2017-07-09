#include <pic16f628a.h>      //Registros de funciones especiales
#include "RegConfiguration.h"//Funciones de control de modulos hardware
#include "CEC_DATA_STRUCT.h" //Funciones de estructura buffer
#include "CEC_CONTROL.h"     //Funciones de control de buffer
#ifndef INTERRUPT_CONTROL_H
#define INTERRUPT_CONTROL_H  
    volatile unsigned char CEC_IF=0;
//
//  Estructura buffer para la recepción por puerto UART
//    
    struct C_BUFFER{
        unsigned char data[4];
        unsigned char length;
    };
    typedef struct C_BUFFER C_BUFFER;
    
//
//  Variable buffer para la recepción por el puerto UART
//
    volatile C_BUFFER uart_buffer;
    /**
     * ISR
     * Servicio de atención a la interrupción
     */
    void interrupt ISR(void);
#endif

