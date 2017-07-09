#ifndef CEC_CONTROL_H
#define CEC_CONTROL_H
    #include "CEC_DATA_STRUCT.h"
    #include "CEC_SENDER_CONTROLLER.h"
    #include <stdbool.h>
    //
    //  BUFFER DE ENTRADA Y SALIDA
    //
    CEC_BUFFER CEC_OUTPUT_BUFFER;

    /* *
     * PERMITE ENVIAR EL BUFFER DE SALIDA POR EL PUERTO CEC
     * @return  true si la transmisión ha sido exitosa, false falta EOM
     * */
    bool CEC_SEND();
    /* *
     * PERMITE COLOCAR UN BYTE Y CONFIGURAR UN FRAME
     * DENTRO DEL BUFFER DE SALIDA
     * @param   unsigned int 10bits frame que se desea agregar
     * @return  true si ha sido agregado, false si no hay espacio 
     * */
    bool CEC_PUSH_BUFFER(unsigned int);
    
#endif