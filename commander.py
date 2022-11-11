import os
import sys
import struct
import datetime
from copy import deepcopy

def float32(num):
    return ''.join(bin(ord(chr(c))).replace('0b', '').rjust(8, '0') for c in struct.pack('!f', num))

def readTelecommandData(fileInput):
    """ Read a file in input with data.
        Returns the following lists:
            - _list : is a list of dictionaries, where every dictionary is TC packet type
                      with all its parameters
            - _listAPIDS : is a list of APID SUBSYSTEMS
            - _listIDS : is a list of lists with the following structure -> at posiztion n there's 
                         the list of all parameters of the subsystem with APID n """
    
    ####### - DATA STRUCTURES - #######

    # - DICTIONARY FOR PACKET TYPE - #
    packet_type={'APID': 0,
                 'ID':0,
                 'NAME':"",
                 'DESCRIPTION':"",
                 'ARGUMENT':"",
                 'FORMAT':"",
                 'SIZE':""}
    #--------------------------------#

    # ------- LISTS TO RETURN -------#
    _list = []
    _listAPIDS = []
    _listIDS = []
    #--------------------------------#

    _listNamesforType = []

    ###################################

    file = open(fileInput)
    for line in file:
        string = line.split('\t')
        _type = deepcopy(packet_type)

        #SETTING PACKET TYPE VALUES
        _type['APID'] = int(string[0])
        _type['NAME'] = string[2]

        #Adding APID and ID types on lists
        if len(_listAPIDS) != 0: 
            if _type['APID'] != _listAPIDS[len(_listAPIDS)-1]:
                _listAPIDS.append(_type['APID'])
                _listIDS.append(deepcopy(_listNamesforType))
                _listNamesforType.clear()
                _listNamesforType.append(_type['NAME'])
            else:
                _listNamesforType.append(_type['NAME'])
        else:
            _listAPIDS.append(_type['APID'])
            _listNamesforType.append(_type['NAME'])
        #------------------------
        
        _type['ID'] = string[1]
        _type['DESCRIPTION'] = string[3]
        _type['ARGUMENT'] = string[4]
        _type['FORMAT'] = string[5]
        _type['SIZE'] = string[6]

        _list.append(_type)

    _listIDS.append(deepcopy(_listNamesforType))
    
    return _list,_listAPIDS,_listIDS

def firstHeaderCreator(dataLength, subsystem):
    """Creates the first header of a TC Packet. it returns the packet 
       in a list of octets"""

    #------ DATA STRUCTURES ------#

    packet =[]

    #-----------------------------#

    #VERSION TYPE SH FLAG
    val =0x1800

    #--- INSERTING APID CODE ---#
    if subsystem == "OBC":
        value = val | 0x00
        packet.append((value & 0xFF00) >> 8)
        packet.append((value & 0xFF))
    elif subsystem == "EPS":
        value = val | 0x01
        packet.append((value & 0xFF00) >> 8)
        packet.append((value & 0xFF))
    elif subsystem == "ADCS":
        value = val | 0x02
        packet.append((value & 0xFF00) >> 8)
        packet.append((value & 0xFF))
    elif subsystem == "WIFI":
        value = val | 0x03
        packet.append((value & 0xFF00) >> 8)
        packet.append((value & 0xFF))
    #---------------------------#

    #SQ_FLAG 
    sqq_flag = 0xC0

    #SQ_COUNT
    seqCount = 0x00

    value = (sqq_flag << 8) | seqCount
    packet.append((value & 0xFF00) >> 8)
    packet.append((value & 0xFF))

    #DATA LENGTH
    if dataLength < 256:
        print(dataLength)
        dataLength = dataLength | 0x0000
        packet.append((dataLength & 0xFF00) >> 8)
        packet.append((dataLength & 0xFF))
    else:
        print("Data Length Oversize!\n")

    return packet

def secondaryHeaderCreator(SMAVN, SMIVN, SPVN, PACKET_ID):
    "Creates the secondary header of the packet that is returned in a list"

    #------ DATA STRUCTURES ------#

    packet =[]

    #-----------------------------#

    #ADDING TIMESTAMP
    packet.append(0x50)

    #ADDING DATE AND TIME IN BCD FORMAT
    date = datetime.datetime.now().strftime('%Y_%m_%d_%H_%M_%S')
    date = date.split('_')
    for i in date:
        values = BCD(i)
        for va in values:
            packet.append(va)

    #ADDING SOFTWARE INFO
    packet.append(int(SMAVN))
    packet.append(int(SMIVN))
    packet.append(int(SPVN))

    #ADDING PACKET_ID
    packet.append(int(PACKET_ID.split('/')[1]))
    return packet

def BCD(data):
    """ This function represent a string in BCD format. As output returns a list
        where every element is a byte"""
    cc = 1
    res = []
    first4 = 0
    for value in data:
        first4 = first4 << 4
        first4 = ((int(value) & 15) | first4 )

        if cc == 2:
            res.append(first4)
            first4 = 0
            cc = 0
        
        cc += 1
    return res

def dataCreator(_list,_format,size):
    """ Create the data field of the TC packet and return it as a list"""
    
    cc=0
    data=[]
    totalsize=0
    size = size.replace("\n", '')

    if size == "---":
        return data, totalsize

    if ',' in size:
        vals=size.split(",")
    else:
         vals = []
         vals.append(size)

    for elem in vals:
        totalsize =totalsize+int(elem)
        if _format == "UINT":
            val= int(_list[cc])

            if int(elem) == 8:
                data.append(val)
            elif int(elem) == 16:
                data.append((val & 0xFF00) >> 8)
                data.append((val & 0xFF))
            elif int(elem) == 32:
                data.append((val & 0xFF0000) >> 16)
                data.append((val & 0xFF00) >> 8)
                data.append((val & 0xFF))

        elif _format == "FLOAT":
            val = int(float32(float(_list[cc])),base=2)

            #DIVIDING THE VALUE IN 4 BYTES
            byte_1 = (val & 0xFF000000) >> 24
            byte_2 = (val & 0xFF0000) >> 16
            byte_3 = (val & 0xFF00) >> 8
            byte_4 = val & 0xFF

            data.append(byte_1)
            data.append(byte_2)
            data.append(byte_3)
            data.append(byte_4)

        elif _format == "UTF-8":
            string = bytearray(_list[cc], 'utf-8')

            for byte in string:
                data.append(byte)

            #IF THE STRING HAS A LEN MINOR THAN THE EXPECTED LENGTH
            #EMPTY BYTES ARE FILLED
            if len(string) < (int(elem)/8):
                empty_bytes = int(int(elem)/8)- len(string)
                for b in range(empty_bytes):
                    data.append(0)

        elif _format == "BCD":
            vals = BCD(str(_list[cc]))
            for inter in vals:
                data.append(inter)

        cc +=1

    return data, totalsize

def createPacket(data_list, PACKET_ID, APID_string , format_string, size_string):
    """ Create a packet and return it as a list. The list is composed of 3 sublists:
        [firstheader] [secHeader] [data] """

    SEC_HEADER_LENGTH = 96
    
    data, totalsize = dataCreator(data_list, format_string, size_string)
    secHeader = secondaryHeaderCreator(0,0,0, PACKET_ID)
    firstheader = firstHeaderCreator(int((totalsize+SEC_HEADER_LENGTH)/8)-1, APID_string)

    Packet = [firstheader, secHeader, data]

    return Packet

def writePacket(file_path_string, Packet):
    
    #OPENING FILE
    out = open(file_path_string, "wb")
    
    #WRITING PACKET DATA
    for elem in Packet:
        for data in elem:
            out.write(bytes([data]))

    out.close()

    
res = BCD('18')

print(res)