#include "CEC_DATA_STRUCT.h"
#include <stdbool.h>

void clear_buffer(CEC_BUFFER *buffer){
    for(int i=0;i<MAX_FRAMES;i++){
        clear_bits(&(buffer->frames[i]));
    }
    buffer->length = 0;
}

//void clear_directions(CEC_DIRECTIONS *directions){
//    directions->LogicalAddress = 0;
//    directions->PhysicalAddress = 0;
//}
bool add_frame(CEC_FRAME frame, CEC_BUFFER *buffer){
    if(buffer->length<MAX_FRAMES){
        buffer->frames[buffer->length] = frame;
                buffer->length++;
        return true;
    }else{
        return false;
    }
}
void clear_bits(CEC_FRAME* frame){
    frame->ACK    = 0;
    frame->data   = 0;
    frame->length = 0;
}
//void set_direction(CEC_DIRECTIONS* directions,unsigned char physicalAddress,\
//        unsigned char logicalAddress){
//    directions->LogicalAddress = logicalAddress;
//    directions->PhysicalAddress = physicalAddress;
//}