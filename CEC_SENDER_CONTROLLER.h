#ifndef CEC_SENDER_CONTROLLER_H
#define CEC_SENDER_CONTROLLER_H
    #include <stdbool.h>
    #include <pic16f628a.h>
    #include "CEC_DATA_STRUCT.h"
    #include "RegConfiguration.h"
    #include "InterruptControl.h"
    #include "CEC_CONTROL.h"
    /**
     * CEC_SC_SENDBUDDER
     *  Esta función depende del hardware y el metodo de transmisión
     *  En este caso se utilizó el CCP,
     *  y unicamente funciona cuando se activa la transmisión.
     * @param CEC_BUFFER* Referencia al buffer que enviar
     * @return true si la transmisión ha sido exitosa, false sino.
     */
    bool CEC_SC_SENDBUFFER(CEC_BUFFER*);
    /**
     * INC_STEP
     * Incrementar paso
     */
    void INC_STEP();
    void SET_ERROR();
    void idle();
    bool isERROR();
    volatile unsigned char step;
#endif