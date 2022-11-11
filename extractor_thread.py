import datetime
import tkinter
import platform
import sys
import os
import interface
import time
import struct
import multiprocessing
from tkinter import ttk
from copy import deepcopy
import threading

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

def dataOrganization(numPackets, packets_not_translated):
    """Takes as input the list of packets not translated in objects yet
       and divides the list in 4 part that are returned. If there are
       residual data they're returned too in dataRes and dataResFlag is
       setted"""
    dataRes = []
    dataResFlag = False
    
    if numPackets % 2 == 0:
        if numPackets % 4 == 0:
            dataDim = int(numPackets/4)
            data0 = packets_not_translated[0:(dataDim)]
            data1 = packets_not_translated[dataDim:(dataDim)+dataDim]
            data2 = packets_not_translated[(dataDim+dataDim):(dataDim)+2*dataDim]
            data3 = packets_not_translated[(dataDim+2*dataDim):(dataDim)+3*dataDim]
        else:
            dataDim = int(numPackets/4)
            data0 = packets_not_translated[0:(dataDim)]
            data1 = packets_not_translated[dataDim:(dataDim)+dataDim]
            data2 = packets_not_translated[(dataDim+dataDim):(dataDim)+2*dataDim]
            data3 = packets_not_translated[(dataDim+2*dataDim):(dataDim)+3*dataDim]
            dataRes = packets_not_translated[(dataDim)+3*dataDim:numPackets]
            dataResFlag = True
    else:
        numPackets1 = numPackets - (numPackets % 2)
        dataDim = int(numPackets1/4)
        data0 = packets_not_translated[0:(dataDim)]
        data1 = packets_not_translated[dataDim:(dataDim)+dataDim]
        data2 = packets_not_translated[(dataDim+dataDim):(dataDim)+2*dataDim]
        data3 = packets_not_translated[(dataDim+2*dataDim):(dataDim)+3*dataDim]
        dataRes = packets_not_translated[(dataDim)+3*dataDim:numPackets]
        dataResFlag = True
    return data0,data1,data2,data3,dataRes,dataResFlag

def bin_to_float(value):
    """Translate values in FLOAT IEEE format 32bit"""
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
    return (string,secHedFLAG,packet,packetAPID,CCSDS_PACKET_DATA_LENGTH)

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
    def __init__(self,data,number):
        self.packet = data
        self.packetAPID = None
        self.packetID = None
        self.dataLength = 0
        self.data = "\n<<DATA>>\n"
        self.checkedParams = None
        self.packetNumber = number

        #Building the packet infos
        (self.firstHeader,self.secondaryHeaderFlag,self.packet,self.packetAPID,self.dataLength) = firstHeaderInfoExtractor(self.packet)
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

    def getNumber(self):
        "Return the order number in file of the packet"
        return self.packetNumber

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
  
    def getDataLength(self):
        """Return the lenght of data in octets"""
        return self.dataLength+1
        
def extraction(data,offset,out):
    """This is the task assigned to each thread. It's the translation of packets in objects
       and their translation in useful data"""
    cc= 0
    for element in data:
        #CONVERSION IN PACKET OBJECT 
        packet = Packet(element,cc+offset)

        #PRINT PACKET DETAILS ON OUTPUT FILE
        out.write("---------" + " PACKET "+str(packet.getNumber())+" ---------")
        out.write("\n")
        out.write(str(packet))
        out.write("----------------------------\n\n")

        #ADD TO PACKETS GLOBAL LIST
        Packets.append(packet)
        cc+=1
    return True

#GLOBAL VARIABLES
Packets = []
packets_not_translated = []


def main(fileIN, fileOUT):
    """Returns the number of packets found"""

    insidePacket = False  
    doThread = True 
    cc = 0

    #----------------- FILE MANAGING -----------------#
    _in = open(fileIN, 'rb')
    bin = _in.read()
    out = open(fileOUT, 'w')
    out.write("EXTRACTION DATE: " + datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') +"\n")
    out.write("PLATFORM EXTRACTION: "+ str(platform.node())+"\n\n")
    #-------------------------------------------------#

    #------------- CHECKING BINARY FILE -------------#
    if len(bin) == 0:
        out.write("\nERROR IN EXTRACTION\n")
        out.close()
        tkinter.messagebox.showerror('Error', 'No data in file')
    #------------------------------------------------#

    #-------------- EXTRACTION OF PACKETS FROM THE KISS FILE --------------#
    for i in bin:
        if i == 0xC0:
            if insidePacket == False:
                binaryData = []
                insidePacket = True
            else:
                insidePacket = False
                binaryData = specialCharactersTranslator(binaryData)
                packets_not_translated.append(binaryData)
        else:
            binaryData.append(i)
    #-----------------------------------------------------------------------#

    #------------------------------------------ MULTITHREADING SECTION ------------------------------------------#
    numPackets = len(packets_not_translated)

    if numPackets < 16:
        doThread = False
    
    if doThread == True:
        #DIVIDE LIST OF UNTRASLATED PACKETS IN FOUR PART
        (data0,data1,data2,data3,dataRes,dataResFlag) = dataOrganization(len(packets_not_translated), packets_not_translated)

        #THREADS INIZIALIZATION
        t1 = threading.Thread(target=extraction, args=(data0,0,out,))
        t2 = threading.Thread(target=extraction, args=(data1,len(data0),out,))
        t3 = threading.Thread(target=extraction, args=(data2,2*len(data0),out,)) 
        t4 = threading.Thread(target=extraction, args=(data3,3*len(data0),out,))

        if dataResFlag == True:
            #IF RES DATA ARE PRESENT AN EXTRA THREAD IS INIZIALIZED
            t5 = threading.Thread(target=extraction, args=(dataRes,4*len(data0),out,))
            
            #THREADS STARTING
            t1.start()
            t2.start()
            t3.start()
            t4.start()
            t5.start()

            #WAITING FOR THREADS' ENDING AND UPDATING PROGRESS BAR
            t1.join()
            interface.bar['value'] = 20
            t2.join()
            interface.bar['value'] = 40
            t3.join()
            interface.bar['value'] = 60
            t4.join()
            interface.bar['value'] = 80
            t5.join()
            interface.bar['value'] = 100
        else:
            t1.start()
            t2.start()
            t3.start()
            t4.start()

            t1.join()
            interface.bar['value'] = 25
            t2.join()
            interface.bar['value'] = 50
            t3.join()
            interface.bar['value'] = 75
            t4.join()
            interface.bar['value'] = 100
    else:
        #ONLY ONE THREAD IF LEN(DATA) < 16
        t1 = threading.Thread(target=extraction, args=(packets_not_translated,0,out,)) 
        t1.start()
        t1.join()
        interface.bar['value'] = 100

    #-----------------------------------------------------------------------------------------------------------#

    tkinter.messagebox.showinfo('Extraction', 'Extraction completed!')
    interface.printOnTerminal("Extraction completed")
    out.close()

    #FILLING LISTBOX IN GUI
    for l in Packets:
        interface.Lb1.insert(l.getNumber(),"PACKET #" + str(l.getNumber()))
        cc += 1

    return len(Packets)

