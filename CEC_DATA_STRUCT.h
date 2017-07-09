#ifndef CEC_DATA_STRUCT_H
#define CEC_DATA_STRUCT_H
    #include <stdbool.h>
    #define MAX_FRAMES  11
    /* *
     * ESTRUCTURA QUE ALMACENA UN UNICO FRAME DE DATOS 10 BITS
     * */
    struct FRAME{
        unsigned char data;
        bool          EOM;
        bool          ACK;
        unsigned char length;
    };
    /* *
     * ESTRUCTURA QUE ALMACENA EL BUFFER DE TRANSMICIÓN O RECEPCIÓN
     * */
    struct BUFFER{
        unsigned char length;
        struct FRAME  frames[MAX_FRAMES];
    };
    /* *
     * ESTRUCTURA QUE ALMACENA LA DIRECCIÓN DE ESTE DISPOSITIVO
     * */
    struct DIRECTIONS{
        unsigned char PhysicalAddress;
        unsigned char LogicalAddress;
    };
    typedef struct FRAME CEC_FRAME;
    typedef struct BUFFER CEC_BUFFER;
    typedef struct DIRECTIONS CEC_DIRECTIONS;
    
    /* *
     * clear_buffer
     * Limpia el buffer para preparar una transmisión o recepción
     * @param   CEC_BUFFER* Buffer de tipo CEC que se desea limpiar
     * */
    void clear_buffer(CEC_BUFFER*);
    /* *
     * clear_directions
     * Limpia las direcciones locales para comenzar una nueva conexión
     * @param   CEC_DIRECTIONS* Buffer de direcciones del disp. Local
     * */
    void clear_directions(CEC_DIRECTIONS*);
    /* *
     * add_frame
     * Permite agregar un frame al final del buffer
     * @param   CEC_FRAME   buffer frame de destino
     * @param   CEC_BUFFER* buffer cec de origen
     * @return  true si ha sido agregado, false si no hay espacio 
     * */
    bool add_frame(CEC_FRAME,CEC_BUFFER*);
    /**
     * add_bit_to_frame
     *  Agrega un bit al frame y verifica que se cumpla el formato.
     *  Permite construir un frame de 10 bits
     * @param CEC_FRAME*    Apuntador al frame que se pretende construir
     * @return true: todo en orden, false: hubo un error
     */
    bool add_bit_to_frame(CEC_FRAME*,bool);
    /**
     * clear_bits 
     *  Permite limpiar un frame para reconstruirlo o borrarlo
     * @param CEC_FRAME*    apuntador al frame
     */
    void clear_bits(CEC_FRAME*);
    /* *
     * set_direction
     * Permite registrar la dirección lógica y física del disp. local
     * @param CEC_DIRECTIONS* Apuntador al buffer de direcciones
     * @param unsigned char Dirección fisica del disp local
     * @param unsigned char Dirección lógica del disp local
     * */
    void set_direction(CEC_DIRECTIONS*,unsigned char,unsigned char);
    /* *
     * PERMITE LEER EL DATO ENPAQUETADO
     * */
#define CEC_FRAME_DATA(_CEC_FRAME_) _CEC_FRAME_.data
    /* *
     * PERMITE LEER EL BIT ACK
     * */
#define CEC_FRAME_IS_ACK(_CEC_FRAME_) _CEC_FRAME_.ACK
    /* *
     * PERMITE LEER EL BIT EOM
     * */
#define CEC_FRAME_IS_EOM(_CEC_FRAME_) _CEC_FRAME_.EOM
#endif