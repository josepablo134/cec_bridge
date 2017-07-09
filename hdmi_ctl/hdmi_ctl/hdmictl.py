# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

import serial
import time     #Controlador de retardos


__version__ = '0.0'

class hdmictl(object):
    #------------------------------------------------
    #Controlador de transmision y recepcion de datos
    #desde y para el HDMI_CEC BRIDGE
    #------------------------------------------------
    HexToChar = [b'0',b'1',b'2',b'3',\
                    b'4',b'5',b'6',b'7',\
                    b'8',b'9',b'A',b'B',\
                    b'C',b'D',b'E',b'F']
    __conexion_state = False
    __version_msg = "Using v."+__version__
    serial_port=""
    port = None
    baudrate=""
    def __init__(self,port='/dev/cu.usb1',baud=9600):
        #------------------------
        #Inicializador
        #------------------------
        self.baudrate        = baud
        self.serial_port     = port
        try:
            self.port            = serial.Serial(port,baud)
            self.__conexion_state = True
        except:
            self.__conexion_state = False
    def __del__(self):
        #------------------------
        #Destructor
        #------------------------
        del self.baudrate
        del self.serial_port
        del self
    def __str__(self):
        #------------------------
        #
        #------------------------
        obj_str = "using port  : %s\n"%self.serial_port
        obj_str +="baudrate    : %d\n"%self.baudrate
        if(self.__conexion_state):
            obj_str +='Established connection\n'
        else:
            obj_str +='No connection established\n'
        obj_str += self.__version_msg+'\n'
        return obj_str
    def __repr__(self):
        return self.__str__()
    def close(self):
        self.port.close()
        self.__conexion_state = False
    def open_connection(self):
        try:
            self.port = serial.Serial(self.serial_port,self.baudrate)
            self.__conexion_state = True
        except:
            self.__conexion_state = False
        return self.__conexion_state
    def write(self,data,eom=True,ack=True):
        time.sleep(0.2)#wait 200 miliseconds
        data = data<<2
        ctl_flag=b'1'
        if(ack):
            data+=1
        if(eom):
            data+=2
            ctl_flag=b'0'
        frame =  self.HexToChar[ (data>>8)&0xF ]    #MSB
        frame += self.HexToChar[ (data>>4)&0xF ]    
        frame += self.HexToChar[ data & 0xF]        #LSB
        frame += ctl_flag
        self.port.write(frame)        
    def read(self):
        #Leer 1 byte
        return self.port.read()
    def read_bytes(self,num_bytes_to_read):
        #leer n bytes
        return self.port.read(num_bytes_to_read)
    def is_connected(self):
        #Verificar conexion con la bandera de estado
        return self.__conexion_state
    def write_array(self,data_array):
        #Enviar un arreglo de bytes de datos en forma de frames
        counter = len(data_array)
        for i in data_array:
            counter -= 1
            ##
            ##Verificamos que el ultimo dato tenga el bit eom
            ##
            if(counter==0):
                self.write(i,True,False)
            else:
                self.write(i,False,False)
            print(self.read_bytes(6))#6 caracteres son recibidos desde el dispositivo
    def reset(self):
        self.port.write(b'R')
        time.sleep(0.2)#wait 200 miliseconds
    def interrupt_reading(self):
        self.port.write(b'I')
        time.sleep(0.2)#wait 200 miliseconds