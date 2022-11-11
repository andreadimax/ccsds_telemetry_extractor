import sys
import serial
import asyncio
import struct

#out = open("/home/andrea/Scrivania/data", "wb")


#ser = serial.Serial('/dev/ttyUSB0', baudrate=38400)  # open serial port Linux
ser = serial.Serial('COM5', baudrate=38400)           # open serial port Windows
#print(ser.name) # check which port was really used
#print(ser.BAUDRATES)

#tnc_init_part="0x1B,0x40,0x4B,0xFF,0xC0,0x0D" #setting for TNC for KISS AX.25 protocol
#tnc_init_part1="0x1B,0x54,0x32,0x30,0x30,0x0D"
#tnc_init_part2="0x1B,0x40,0x4B,0x0D"

tnc_init_part=[0x1B,0x40,0x4B,0xFF,0xC0,0x0D]
tnc_init_part1=[0x1B,0x54,0x32,0x30,0x30,0x0D]
tnc_init_part2=[0x1B,0x40,0x4B,0x0D]

command = [0xC0,0x00,0x43,0x54,0x50,0x43,0x54,0x50,0xE0,0x43,0x53,0x53,0x47,0x53,0x53,0x26,0x03,0xF0]

# s = [0x1B,0x40,0x4B,0xFF,0xC0,0x0D,0x1B,0x54,0x32,0x30,0x30,0x0D,0x1B,0x40,0x4B,0x0D]

#s = 0x1B404BFFC00D1B543230300D1B404B0D

# tnc_init_part=" 192, 255" #setting for TNC for KISS AX.25 protocol
# tnc_init_part1="192"
# tnc_init_part2="13"
# tnc_init_part=bin(0x1B).lstrip('0b'), bin(0x40).lstrip('0b'), bin(0x4B).lstrip('0b'), bin(0xFF).lstrip('0b'), bin(0xC0).lstrip('0b'), bin(0x0D).lstrip('0b') #setting for TNC for KISS AX.25 protocol
# tnc_init_part1=bin(0x1B).lstrip('0b'), bin(0x54).lstrip('0b'), bin(0x32).lstrip('0b'), bin(0x30).lstrip('0b'), bin(0x30).lstrip('0b'), bin(0x0D).lstrip('0b')
# tnc_init_part2=bin(0x1B).lstrip('0b'), bin(0x40).lstrip('0b'), bin(0x4B).lstrip('0b'), bin(0x0D).lstrip('0b')

# tnc_init_part=str({0x1B,0x40,0x4B,0xFF,0xC0,0x0D}) #setting for TNC for KISS AX.25 protocol
# tnc_init_part1=str({0x1B,0x54,0x32,0x30,0x30,0x0D})
# tnc_init_part2=str({0x1B,0x40,0x4B,0x0D})

if ser.is_open == True:
    print("COM5 is Open")
    try:
        # Ensure that the end of the message has both \r and \n, not just one or the other
        # command = str(tnc_init_part)
        # print(command)
        # ser.write(command.encode('utf-8'))
        # print(ser.write(command.encode('utf-8')))
        # command1 = str(tnc_init_part1)
        # print(command1)
        # ser.write(command1.encode('utf-8'))
        # print(ser.write(command1.encode('utf-8')))
        # command2 = str(tnc_init_part2)
        # print(command2)
        # ser.write(command2.encode('utf-8'))
        # print(ser.write(command2.encode('utf-8')))
        for l in tnc_init_part:
            l=chr(l)
            print(l)
            print(ser.write(l.encode('charmap')))
        for l in tnc_init_part1:
            l=chr(l)
            print(l)
            print(ser.write(l.encode('charmap')))
        for l in tnc_init_part2:
            l=chr(l)
            print(l)
            print(ser.write(l.encode('charmap')))

        for l in command:
            l=chr(l)
            print(l)
            print(ser.write(l.encode('charmap')))
        # l= str(tnc_init_part[0])
        # ser.write(l.encode('ascii'))
        #     # ser.write(bin(l))7
        # l = str(tnc_init_part).replace(", ", "").replace("[","").replace("]","")
        # ser.write(l.encode('ascii'))
        # l1 = str(tnc_init_part1).replace(", ", "").replace("[","").replace("]","")
        # ser.write(l1.encode('ascii'))
        # l2 = str(tnc_init_part2).replace(", ", "").replace("[","").replace("]","")
        # ser.write(l2.encode('ascii'))

    except:
        print("Error sending message: ", sys.exc_info()[0] )
#     # ser.write(tnc_init_part)         # write a string
#     # ser.close()                 # close port
# else:
#     print('COM5 not Open')


# s = serial.Serial('COM2')
# res = s.read()
# print(res)


# import serial.tools.list_ports as port_list
# ports = list(port_list.comports())
# print(ports)
# for p in ports:
#     print (p)

# SERIAL_PORT = 'COM3'  #Porta Seriale per radiomodem
# SERIAL_PORT1 = 'COM2' #Porta Seriale per radiomodem


# import sys
# import glob
# import serial


# def serial_ports():
#     """ Lists serial port names

#         :raises EnvironmentError:
#             On unsupported or unknown platforms
#         :returns:
#             A list of the serial ports available on the system
#     """
#     if sys.platform.startswith('win'):
#         ports = ['COM%s' % (i + 1) for i in range(256)]
#     elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
#         # this excludes your current terminal "/dev/tty"
#         ports = glob.glob('/dev/tty[A-Za-z]*')
#     elif sys.platform.startswith('darwin'):
#         ports = glob.glob('/dev/tty.*')
#     else:
#         raise EnvironmentError('Unsupported platform')

#     result = []
#     for port in ports:
#         try:
#             s = serial.Serial(port)
#             s.close()
#             result.append(port)
#         except (OSError, serial.SerialException):
#             pass
#     return result


# if __name__ == '__main__':
#     print(serial_ports())

# import string  
# from ctypes import windll  
# import time  
# import os  
# def get_drives():  
#     drives = []  
#     bitmask = windll.kernel32.GetLogicalDrives()  
#     for letter in string.ascii_uppercase:  
#         if bitmask & 1:  
#             drives.append(letter)  
#         bitmask >>= 1  
#     return drives  
# if __name__ == '__main__':  
#     before = set(get_drives())  
#     pause = input("Please insert the USB device, then press ENTER")  
#     print ('Please wait...')  
#     time.sleep(5)  
#     after = set(get_drives())  
#     drives = after - before  
#     delta = len(drives)  
#     if (delta):  
#         for drive in drives:  
#             if os.system("cd " + drive + ":") == 0:  
#                 newly_mounted = drive  
#                 print ("There were %d drives added: %s. Newly mounted drive letter is   %s" %   (delta, drives, newly_mounted))
#     else:  
#         print ("Sorry, I couldn't find any newly mounted drives.")
ser.close()