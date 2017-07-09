#include "CEC_CONTROL.h"


bool CEC_SEND(){
    return CEC_SC_SENDBUFFER(&CEC_OUTPUT_BUFFER);
}
bool CEC_PUSH_BUFFER(unsigned volatile int frame){
    //
    //  Se prepara un frame y se agrega al buffer
    //
    volatile CEC_FRAME Data;
    Data.data = 0xFF&(frame>>2);
    Data.EOM  = 0x01&(frame>>1);
    Data.ACK  = 0x01&frame;
    return add_frame(Data,&CEC_OUTPUT_BUFFER);
}