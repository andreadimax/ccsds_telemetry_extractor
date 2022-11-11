import datetime
import tkinter
import platform
import sys
import os
import interface
import time
import struct
from tkinter import ttk
from copy import deepcopy

######### - DICTIONARIES FOR CHECKING VALUES - #########
eps = { 'battery_voltage': {'no':0,
                            'tol_min': 5,
                            'tol_max': 7.9,
                            'alarm': 8},
        'battery_charging': {'no':0,
                             'tol_min':1,
                             'tol_max':25},
        'battery_temperature':{'no':20,
                               'tol_min': 31,
                               'tol_max': 34.9,
                               'alarm': 35},
        'bus_5v_voltage':{'no':0,
                          'tol_min':5,
                          'tol_max':7.9,
                          'alarm':8},
        'bus_3v3_voltage':{'no':0,
                           'tol_min':3.3,
                           'tol_max':4.9,
                           'alarm':5}
        }

obc = { 'obc_load':{'alarm':90}}

########################################################



def bin_to_float(value):
    value = bin(value).replace("0b", "")
    if len(value) < 32:
        value =value.zfill(32)
    return struct.unpack('!f',struct.pack('!I', int(value, 2)))[0]

def getValue(offset, size, data):
    """ Return the value at the offset position in the binary file """
    initialOctet = int((offset)/8)
    finalOctet = int((offset + size -1)/8)
    finalOffset = (finalOctet+1)*8 - (offset + size)

    _filter = ((2**size) - 1) << finalOffset

    pack = data[initialOctet]

    for i in range(initialOctet + 1, finalOctet+1):
        pack = pack << 8
        pack = pack | data[i]
    
    finalData = (pack & _filter) >> finalOffset
    return finalData 

def specialCharactersTranslator(packet):
    """ Translate the DB+DC or DB+DD HEX sequencies of the KISS special characters
        Return the translated packet """
    ccn = 0
    for l in packet:
        if l == 0xDB:
            if packet[ccn+1] == 0xDC:
                packet[ccn] = 0xC0
                del packet[ccn+1]
            elif packet[ccn+1] == 0xDD:
                packet[ccn] = 0xDB
                del packet[ccn+1]
            else: print("Error in DATA: not T sequence after special character 0xDB")
        ccn += 1
    return (packet)

def firstHeaderInfoExtractor(packet):
    """ Return a string with the First Header Parameters of the packet """
    del packet[0] # Delete the first 00 HEX character of the KISS Protocol command field

    secHedFLAG = False

    CCSDS_VERSION = (packet[0] & 0xE0)>>5
    CCSDS_TYPE = (packet[0] & 0x10)>>4
    CCSDS_SECONDARY_HEADER_FLAG = (packet[0] & 0x08)>>3
    CCSDS_APID = ((packet[0] & 7) << 8) | packet[1]
    CCSDS_SEQUENCE_FLAG = (packet[2] & 0xC0)>>6
    CCSDS_SEQUENCE_COUNT = ((packet[2] & 0x3F) << 8 ) | packet[3]
    CCSDS_PACKET_DATA_LENGTH = (packet[4] << 8) | packet[5]

    #version
    version = "PACKET VERSION : " + str(CCSDS_VERSION)+"\n"

    #type
    if CCSDS_TYPE == 0:
        typeP = "PACKET TYPE : TELEMETRY\n"
    elif CCSDS_TYPE == 1:
        typeP = "PACKET TYPE : TELECOMMAND\n"
    else: 
        print("Error in reading packet type")
        typeP = ""

    #secondary header presence
    if CCSDS_SECONDARY_HEADER_FLAG == 0:
        sH = "PACKET SECONDARY HEADER: FALSE\n"
    elif CCSDS_SECONDARY_HEADER_FLAG == 1:
        sH = "PACKET SECONDARY HEADER: TRUE\n"
        secHedFLAG = True
    else: 
        print(CCSDS_SECONDARY_HEADER_FLAG)
        print("Error in reading packet sec header flag")
        sH = ""

    #packet apid
    if CCSDS_APID == 0:
        packetAPID = 0
        pT = "PACKET APID: OBC\n"
    elif CCSDS_APID == 1:
        packetAPID = 1
        pT = "PACKET APID: EPS\n"
    elif CCSDS_APID == 2:
        packetAPID = 2
        pT = "PACKET APID: ADCS\n"
    elif CCSDS_APID == 3:
        packetAPID = 3
        pT = "PACKET APID: WIFI\n"
    else: 
        print("Error in reading packet subtype")
        pT = ""

    #sequence flag
    if CCSDS_SEQUENCE_FLAG == 3:
        sF = "PACKET SEQUENCE FLAG: 11\n"
    elif CCSDS_SEQUENCE_FLAG == 1:
        sF = "PACKET SEQUENCE FLAG: 01\n"
    elif CCSDS_SEQUENCE_FLAG == 0:
        sF = "PACKET SEQUENCE FLAG: 00\n"
    elif CCSDS_SEQUENCE_FLAG == 2:
        sF = "PACKET SEQUENCE FLAG: 10\n"
    else:
        print("Error in reading packet sequence flag")
        sF = ""

    #sequence count
    seq = "PACKET SEQUENCE NUMBER: " + str(CCSDS_SEQUENCE_COUNT)+"\n"

    #packet length
    length = "PACKET DATA LENGTH: " + str(CCSDS_PACKET_DATA_LENGTH)+"\n"

    #final string builder
    string = "\n<<PRIMARY HEADER>>\n" + version + typeP + sH + pT + sF + seq + length
    return (string,secHedFLAG,packet,packetAPID)

def secondaryHeaderInfoExtractor(packet):
    """ Return a string with the Secondary Header Parameters of the packet (if present) """

    CCSDS_TIMESTAMP_PREAMBLE = packet[6]
    CCSDS_YEAR = str((packet[7] & 0xF0)>>4) + str(packet[7] & 15) + str((packet[8] & 0xF0)>>4) + str(packet[8] & 15)
    CCSDS_MONTH = str((packet[9] & 0xF0)>>4) + str(packet[9] & 15)
    CCSDS_DAY_OF_MONTH = str((packet[10] & 0xF0)>>4) + str(packet[10] & 15)
    CCSDS_HOURS = str((packet[11] & 0xF0)>>4) + str(packet[11] & 15)
    CCSDS_MINUTES = str((packet[12] & 0xF0)>>4) + str(packet[12] & 15)
    CCSDS_SECONDS = str((packet[13] & 0xF0)>>4) + str(packet[13] & 15)
    CCSDS_VERSION_NUMBER_MAJOR = str(packet[14])
    CCSDS_VERSION_NUMBER_MINOR = str(packet[15])
    CCSDS_VERSION_NUMBER_PATCH = str(packet[16])
    CCSDS_PACKET_ID = str(packet[17])
    packetID = packet[17]

    if (CCSDS_TIMESTAMP_PREAMBLE - 80) == 0:
        timestamp = "PACKET TIMESTAMP FORMAT: YYYY/MM/DD\n"
    else:
        print("Error in reading timestamp")
    
    packYear = "YEAR: " + CCSDS_YEAR + "\n"
    packMont = "MONTH: "+ CCSDS_MONTH + "\n"
    packDay = "DAY: " + CCSDS_DAY_OF_MONTH + "\n"
    hh = "HOUR: " + CCSDS_HOURS + "\n"
    mm = "MINUTE: " + CCSDS_MINUTES + "\n"
    ss = "SECONDS: " + CCSDS_SECONDS + "\n"
    nMA = "SUBSYSTEM SOFTWARE MAJOR VERSION NUMBER: " + CCSDS_VERSION_NUMBER_MAJOR + "\n"
    nMI = "SUBSYSTEM SOFTWARE MINOR VERSION NUMBER: " + CCSDS_VERSION_NUMBER_MINOR + "\n"
    nPA = "SUBSYSTEM SOFTWARE PATCH: " + CCSDS_VERSION_NUMBER_PATCH + "\n"
    ID = "PACKET ID: " + CCSDS_PACKET_ID + "\n"


    string = "\n<<SECONDARY HEADER>>\n" + timestamp + packYear + packMont + packDay + hh + mm + ss + nMA + nMI + nPA + ID

    return string,packetID

def tableReader(tableNumber):
    """ Returns a list of all parameters of a certain subsystem table
        The list has this format: [ offset name type scale ]"""
    tables = []
    if tableNumber == 0:
        file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + "/Tables/OBC_1.dat","r")
        for line in file:
            string = line.split('\t')
            tables.append(string)
    elif tableNumber == 1:
        file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + "/Tables/OBC_2.dat","r")
        for line in file:
            string = line.split('\t')
            tables.append(string)
    elif tableNumber == 2:
        file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + "/Tables/EPS.dat","r")
        for line in file:
            string = line.split('\t')
            tables.append(string)
    elif tableNumber == 3:
        file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + "/Tables/ADCS.dat","r")
        for line in file:
            string = line.split('\t')
            tables.append(string)
    elif tableNumber == 4:
        file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + "/Tables/WIFI.dat","r")
        for line in file:
            string = line.split('\t')
            tables.append(string)
    return tables

class Packet(object):
    def __init__(self,data):
        self.packet = data
        self.packetAPID = None
        self.packetID = None
        self.data = "\n<<DATA>>\n"
        self.checkedParams = None

        #Building the packet infos
        (self.firstHeader,self.secondaryHeaderFlag,self.packet,self.packetAPID) = firstHeaderInfoExtractor(self.packet)
        if self.secondaryHeaderFlag == True:
            (self.sndHeader,self.packetID) = secondaryHeaderInfoExtractor(self.packet)
        else:
            self.sndHeader = ""

        #getting data and checked params
        self.checkedParams = self.getData()
    
    def __str__(self):
        #Building a summary info string of packet
        self.packetString = self.firstHeader + self.sndHeader + self.data
        return self.packetString

    def getData(self):
        """ It assign the variable self.data of the object and returns a list of checked params"""

        ##### - FUNCTION VALUES - #####

        #A list of dictionaries with parameters and their check status
        checkedParams = []

        #Dictionary to print error status on screen
        #By default packet is all correct,
        #if any error is detected 'ok' is set to 0
        #and one of other values is set to 1
        states={'alarm':0,
               'tolerance':0,
               'ool':0,
               'zero':0,
               'ok':1}

        ################################

        #OBC APID=0 ID=0 subsystem
        if self.packetAPID == 0 and self.packetID == 0:
            parameters = tableReader(0)
            for i in parameters:
                offset = int(i[0])
                name = i[1]
                _type = str(i[2])
                scale = float(i[3])
                size = int(i[4])
                state=deepcopy(states)

                # scale = 0 means that on the table is not indicated a scale value
                if scale != 0:
                    if _type == "FLOAT":
                        value = bin_to_float(getValue(offset,size,self.packet)) * scale
                    else:
                        value = getValue(offset,size,self.packet) * scale
                else:
                    value = getValue(offset,size,self.packet)

                #CHECK
                if name == "OBC_PROCESSOR_LOAD" and value > obc['obc_load']['alarm']:
                    state['ok']=0
                    state['alarm']=1
                
                checkedParam = {'name':name, 'value':value, 'states': state}
                checkedParams.append(checkedParam)

                self.data= self.data + (name + " = " + str(value)+ "\n")
        #OBC APID=0 ID=1 subsystem 
        elif self.packetAPID == 0 and self.packetID == 1:
            parameters = tableReader(1)
            for i in parameters:
                offset = int(i[0])
                name = i[1]
                _type = str(i[2])
                scale = float(i[3])
                size = int(i[4])
                state = deepcopy(states)

                if scale != 0:
                    if _type == "FLOAT":
                        value = bin_to_float(getValue(offset,size,self.packet)) * scale
                    else:
                        value = getValue(offset,size,self.packet) * scale
                else:
                    value = getValue(offset,size,self.packet)

                checkedParam = {'name':name, 'value':value, 'states': state}
                checkedParams.append(checkedParam)  

                self.data= self.data + (name + " = " + str(value)+ "\n")
        #EPS subsystem
        elif self.packetAPID == 1 and self.packetID == 0:
            parameters = tableReader(2)
            for i in parameters:
                offset = int(i[0])
                name = i[1]
                _type = str(i[2])
                scale = float(i[3])
                size = int(i[4])
                state = deepcopy(states)

                if scale != 0:
                    if _type == "FLOAT":
                        value = bin_to_float(getValue(offset,size,self.packet)) * scale
                    else:
                        value = getValue(offset,size,self.packet) * scale
                else:
                    value = getValue(offset,size,self.packet)

                #CHECK
                if name == "EPS_3V3_LINE_VOLTAGE":
                    if value == eps['bus_3v3_voltage']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['bus_3v3_voltage']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                    elif value >= eps['bus_3v3_voltage']['alarm']:
                        state['ok']=0
                        state['alarm']=1
                elif name == "EPS_5V_LINE_VOLTAGE":
                    if value == eps['bus_5v_voltage']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['bus_5v_voltage']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                    elif value >= eps['bus_5v_voltage']['alarm']:
                        state['ok']=0
                        state['alarm']=1
                elif name == "EPS_BATTERY_1_VOLTAGE":
                    if value == eps['battery_voltage']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['battery_voltage']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                    elif value >= eps['battery_voltage']['alarm']:
                        state['ok']=0
                        state['alarm']=1
                elif name == "EPS_BATTERY_2_VOLTAGE":
                    if value == eps['battery_voltage']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['battery_voltage']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                    elif value >= eps['battery_voltage']['alarm']:
                        state['ok']=0
                        state['alarm']=1
                elif name == "EPS_BATTERY_TEMPERATURE":
                    if value == eps['battery_temperature']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['battery_temperature']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                    elif value >= eps['battery_temperature']['alarm']:
                        state['ok']=0
                        state['alarm']=1
                elif name == "EPS_BATTERY_STATE_OF_CHARGE":
                    if value == eps['battery_charging']['no']:
                        state['ok']=0
                        state['zero']=1
                    elif value >= eps['battery_charging']['tol_min'] and value <=eps['bus_3v3_voltage']['tol_max']:
                        state['ok']=0
                        state['tolerance']=1
                else:
                    pass

                checkedParam = {'name':name, 'value':value, 'states': state}
                checkedParams.append(checkedParam)        

                self.data= self.data + (name + " = " + str(value)+ "\n")
        #ADCS subsystem
        elif self.packetAPID == 2 and self.packetID == 0:
            parameters = tableReader(3)
            for i in parameters:
                offset = int(i[0])
                name = i[1]
                _type = str(i[2])
                scale = float(i[3])
                size = int(i[4])
                state = deepcopy(states)

                if scale != 0:
                    if _type == "FLOAT":
                        if offset == 536:
                            value = bin_to_float(getValue(offset,size,self.packet)) * scale
                    else:
                        value = getValue(offset,size,self.packet) * scale
                else:
                    value = getValue(offset,size,self.packet)

                checkedParam = {'name':name, 'value':value, 'states': state}
                checkedParams.append(checkedParam)  

                self.data= self.data + (name + " = " + str(value)+ "\n")
        #WIFI subsystem
        elif self.packetAPID == 3 and self.packetID == 0:
            parameters = tableReader(4)
            for i in parameters:
                offset = int(i[0])
                name = i[1]
                _type = str(i[2])
                scale = float(i[3])
                size = int(i[4])
                state = deepcopy(states)

                if scale != 0:
                    if _type == "FLOAT":
                        value = bin_to_float(getValue(offset,size,self.packet)) * scale
                    else:
                        value = getValue(offset,size,self.packet) * scale
                else:
                    value = getValue(offset,size,self.packet)
                self.data= self.data + (name + " = " + str(value)+ "\n")

                checkedParam = {'name':name, 'value':value, 'states': state}
                checkedParams.append(checkedParam)  

        return checkedParams
        
#GLOBAL VARIABLES
Packets = []


def main(fileIN, fileOUT):
    #FILE MANAGING
    _in = open(fileIN, 'rb')
    bin = _in.read()
    out = open(fileOUT, 'w')
    out.write("EXTRACTION DATE: " + datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') +"\n")
    out.write("PLATFORM EXTRACTION: "+ str(platform.node())+"\n\n")


    binaryFileDim = os.path.getsize(fileIN)
    cc = 0                    #octets in binary file counter
    counter = 0               #packets counter
    cc2 = 1                   #counter for representing PACKET# in listbox
    insidePacket = False      

    for i in bin:
        cc += 1
        
        #Progressbar in GUI managing
        percentage = int((cc * 100)/binaryFileDim)
        interface.bar['value'] = percentage

        if i == 0xC0:
            if insidePacket == False:
                binaryData = []
                insidePacket = True
            else:
                insidePacket = False
                counter += 1
                binaryData = specialCharactersTranslator(binaryData)
                packet = Packet(binaryData)

                #Extraction file writer
                out.write("---------" + " PACKET "+str(counter)+" ---------")
                out.write("\n")
                out.write(str(packet))
                out.write("----------------------------\n\n")

                Packets.append(packet)
        else:
            binaryData.append(i)


    #tkinter.messagebox.showinfo('Extraction', 'Extraction completed!')
    interface.printOnTerminal("Extraction completed")
    out.close()

    
    for l in Packets:
        interface.Lb1.insert(cc2,"PACKET #" + str(cc2))
        cc2 += 1

