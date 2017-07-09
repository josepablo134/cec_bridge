# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
from hdmictl import *

__version__ = '0.0'

class hdmicec(hdmictl):
    CMD_TURN_ON   =[0x10,0x04]
    CMD_TURN_OFF  =[0x10,0x36]
    CMD_DMC_UCP_SELECT = [0x10,0x44,0x00]
    CMD_DMC_UserControllPressed_SELECT  = [0x10,0x44,0x00]  #select
    CMD_DMC_UserControllPressed_UP      = [0x10,0x44,0x01]  #up
    CMD_DMC_UserControllPressed_DOWN    = [0x10,0x44,0x02]  #down
    CMD_DMC_UserControllPressed_LEFT    = [0x10,0x44,0x03]  #left
    CMD_DMC_UserControllPressed_RIGHT   = [0x10,0x44,0x04]  #right
    CMD_DMC_UserControllPressed_R_U     = [0x10,0x44,0x05]  #right up
    CMD_DMC_UserControllPressed_R_D     = [0x10,0x44,0x06]  #right down
    CMD_DMC_UserControllPressed_L_U     = [0x10,0x44,0x07]  #left up
    CMD_DMC_UserControllPressed_L_D     = [0x10,0x44,0x08]  #left down
    CMD_DMC_UserControllPressed_R_M     = [0x10,0x44,0x09]  #root menu
    CMD_DMC_UserControllPressed_S_M     = [0x10,0x44,0x0A]  #setup menu
    CMD_DMC_UserControllPressed_C_M     = [0x10,0x44,0x0B]  #contents menu
    CMD_DMC_UserControllPressed_F_M     = [0x10,0x44,0x0C]  #favorite menu
    CMD_DMC_UserControllPressed_EXIT    = [0x10,0x44,0x0D]  #exit
    CMD_DMC_UserControllPressed_0       = [0x10,0x44,0x20]  #0
    CMD_DMC_UserControllPressed_1       = [0x10,0x44,0x21]  #1
    CMD_DMC_UserControllPressed_2       = [0x10,0x44,0x22]  #2
    CMD_DMC_UserControllPressed_3       = [0x10,0x44,0x23]  #3
    CMD_DMC_UserControllPressed_4       = [0x10,0x44,0x24]  #4
    CMD_DMC_UserControllPressed_5       = [0x10,0x44,0x25]  #5
    CMD_DMC_UserControllPressed_6       = [0x10,0x44,0x26]  #6
    CMD_DMC_UserControllPressed_7       = [0x10,0x44,0x27]  #7
    CMD_DMC_UserControllPressed_8       = [0x10,0x44,0x28]  #8
    CMD_DMC_UserControllPressed_9       = [0x10,0x44,0x29]  #9
    CMD_DMC_UserControllPressed_DOT     = [0x10,0x44,0x2A]  #dot
    CMD_DMC_UserControllPressed_ENTER   = [0x10,0x44,0x2B]  #enter
    CMD_DMC_UserControllPressed_CLEAR   = [0x10,0x44,0x2C]  #clear
    CMD_DMC_UserControllPressed_NF      = [0x10,0x44,0x2F]  #next favorite
    CMD_DMC_UserControllPressed_CU      = [0x10,0x44,0x30]  #channel up
    CMD_DMC_UserControllPressed_CD      = [0x10,0x44,0x31]  #channel down
    CMD_DMC_UserControllPressed_PC      = [0x10,0x44,0x32]  #previous channel
    CMD_DMC_UserControllPressed_SS      = [0x10,0x44,0x33]  #sound select
    CMD_DMC_UserControllPressed_IS      = [0x10,0x44,0x34]  #input select
    CMD_DMC_UserControllPressed_DI      = [0x10,0x44,0x35]  #display information
    CMD_DMC_UserControllPressed_HELP    = [0x10,0x44,0x36]  #help
    CMD_DMC_UserControllPressed_PU      = [0x10,0x44,0x37]  #page up
    CMD_DMC_UserControllPressed_PD      = [0x10,0x44,0x38]  #page down
    CMD_DMC_UserControllPressed_POWER   = [0x10,0x44,0x40]  #power
    def __init__(self,port="",baud=9600):
        hdmictl.__init__(self,port,baud)
    def turnOn(self):
        self.write_array(self.CMD_TURN_ON)
    def turnOff(self):
        self.write_array(self.CMD_TURN_OFF)
    
if __name__ == "__main__":
    print("Hello world")
#'/dev/cu.usbserial-FTH0KEFT',9600
#    print(a.open_connection())
#    a.interrupt_reading()
#    print(a.read_bytes(3))#OK\n 3 caracteres son recibidos desde el dispositivo
#    a.write(0xFF,False,False)
#    print(a.read_bytes(6))#6 caracteres son recibidos desde el dispositivo
#    a.write(0xFF,False,False)
#    print(a.read_bytes(6))
#    a.write(0xFF,False,False)
#    print(a.read_bytes(6))
#    a.write(0xFF,True,False)
#    print(a.read_bytes(6))
#    print(a.is_connected())                     #a.read() 
#    a.write_array([0xFF,0xFF,0xFF,0xFF,0xFF])   #a.read_bytes(3)
#    print(a.read_bytes(6))#6 caracteres son recibidos desde el dispositivo
#    print(a.read_bytes(6))
#    print(a.read_bytes(6))
#    print(a.read_bytes(6))
#    print(a.read_bytes(6))