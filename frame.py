from source_packet import Packet
#import GUI

frames = []
lista = []
cc = 1

_in = open("/home/andrea/Scrivania/TMframes3.bin", 'rb')
bin = _in.read()
#print(len(bin))

for i in bin:
    if ((cc-1) % 1135 == 0):
        frames.append(lista)
        lista = []
        lista.append(i)
        cc += 1
    else:
        if cc == len(bin):
            lista.append(i)
            frames.append(lista)
        else:
            lista.append(i)
            cc += 1
#print(cc)
#print(len(frames))

def crc16(data : bytearray, offset , length):
        """ Calculate the CRC of the frame. Returbs a 16-bit value"""
        if data is None or offset < 0 or offset > len(data)- 1 and offset+length > len(data):
            return 0
        crc = 0xFFFF
        for i in range(0, length):
            crc ^= data[offset + i] << 8
            for j in range(0,8):
                if (crc & 0x8000) > 0:
                    crc =(crc << 1) ^ 0x1021
                else:
                    crc = crc << 1
        return crc & 0xFFFF



class Frame(object):

    def __init__(self,data, number_of_frame: int):
        """Initializes the Packet object"""

        self.info = ""
        self.number_of_frame = number_of_frame

        ##### COSTANTS #####
        self.FRAME_LENGTH = len(data)
        self.PRIMARY_HEADER_LENGTH = 6  #(octets)
        self.OPERATIONAL_CONTROL_FIELD_DATA_LENGTH = 4 #(octets)
        self.FRAME_ERROR_CONTROL_FIELD_DATA_LENGTH = 2 #(octets)

        self.PACKETS_TO_MULTIPLEX = []
        self.IDLE_DATA = []
        self.VCA_SDU_DATA =[]
        ####################

        ##### FLAGS #####
        self.IDLE_DATA = False
        self.PACKETS_DATA = False
        self.NO_PACKETS = False # in this case the frame transport remaing parts of packets from previous frames
        self.CRC_ERROR = False
        #################


        #----- Primary Header Variables -----#
        self.versionNumber = 0

        self.spID = 0
        self.virtualChannel = 0
        self.opCntrlFieldFLAG = 0

        self.masterChannelcount = 0
        self.virtualChannelCount = 0

        self.scndHeaderFLAG = 0
        self.synchFLAG = 0
        self.pktOrderFLAG = 0
        self.segmentLenghtID = 0
        self.firstHeaderPointer = 0
        #------------------------------------#


        #----- Secondary Header Variables -----#
        self.scndHeaderVersionNumber = 0
        self.scndHeaderLength = 0
        self.scndHeaderData = 0
        self.scndHeaderDataNumbOctets = 0
        #--------------------------------------#

        #------------ Frame Data Field Variables ------------#
        self.frameDataFieldLength = 0
        self.startOffset= 0
        self.packets = []
        #----------------------------------------------------#

        #------- CRC -------#
        self.crc_calcuated = 0
        self.crc = (data[len(data)-2] << 8) & (data[len(data)-1])

        # Comparing CRC
        if self.crc != self.crc_calcuated:
            self.CRC_ERROR = True

        #-------------------#


        #------- Initialization of the Frame -------#
        self.extractPrimaryHeader(data)
        if self.scndHeaderFLAG == True:
            self.extractSecondaryHeader(data)
        else:
            self.startOffset = 6
        #-------------------------------------------#

        # Checking the type of data transported (Packets, IDLE or VCA_SDU)
        if self.firstHeaderPointer == 0x7FF:
            self.NO_PACKETS = True
        elif self.firstHeaderPointer == 0x7FE:
            self.IDLE_DATA = True
        else:
            self.PACKETS_DATA = True

        # Calculating the frame data field length
        if self.scndHeaderFLAG == True:
            self.frameDataFieldLength = self.FRAME_LENGTH - (self.PRIMARY_HEADER_LENGTH + self.OPERATIONAL_CONTROL_FIELD_DATA_LENGTH + self.FRAME_ERROR_CONTROL_FIELD_DATA_LENGTH + self.scndHeaderDataNumbOctets)
        else:
            self.frameDataFieldLength = self.FRAME_LENGTH - (self.PRIMARY_HEADER_LENGTH + self.OPERATIONAL_CONTROL_FIELD_DATA_LENGTH + self.FRAME_ERROR_CONTROL_FIELD_DATA_LENGTH)

        # Extracting packets
        self.extractPackets(self.extractDataField(data))
        #-------------------------------------------#

    ################### GET METHODS ###################

    def getVersionNumber(self):
        return self.versionNumber
    
    def getSpid(self):
        return self.spID

    def getVirtualChannel(self):
        return self.virtualChannel
    
    def getMC_Count(self):
        return self.masterChannelcount
    
    def getVC_Count(self):
        return self.virtualChannelCount

    def printPackets(self, packets: list):
        string = ""
        cc = 0
        for packet in packets:
            string = string + "----- PACKET #" + str(cc) + " -----\n" +  str(packet) + "\n---------------------\n"
            cc += 1
        return string

    ###################################################



    ################### PROCESSING METHODS ###################
    def extractPrimaryHeader(self,packet):
        """This function extracts infos from frame primary header and
           assigns them to object attributes"""

        self.versionNumber = (packet[0] & 0xC0)>> 6

        #TF Identification
        self.spID = ((packet[0] & 0x3F) << 4) | ((packet[1] & 0xF0) >> 4)
        self.virtualChannel = (packet[1] & 0x0E) >> 1
        self.opCntrlFieldFLAG = (packet[1] & 0x01)

        self.masterChannelcount = packet[2]
        self.virtualChannelCount = packet[3]

        #TF Data Field Status
        self.scndHeaderFLAG = (packet[4] & 0x80) >> 7
        self.synchFLAG = (packet[4] & 0x40) >> 6
        self.pktOrderFLAG = (packet[4] & 0x20) >> 5
        self.segmentLenghtID = (packet[4] & 0x18) >> 3
        self.firstHeaderPointer = ((packet[4] & 0x07) << 8) | packet[5]

    def extractSecondaryHeader(self, packet):
        """This function extracts infos from frame secondary header and
           assigns them to object attributes"""

        self.scndHeaderVersionNumber = (packet[6] & 0xC0) >> 6
        self.scndHeaderLength = (packet[6] & 0x3F)

        self.scndHeaderDataNumbOctets = self.scndHeaderLength + 1 
        self.startOffset = 7+self.scndHeaderDataNumbOctets
        self.scndHeaderData = packet[7:self.startOffset]

    def extractDataField(self,packet):
        """This function extract the data field from the frame. Create a list and return it"""
        dataField = packet[self.startOffset:self.startOffset+self.frameDataFieldLength]
        return dataField

    def extractPackets(self, dataField):
        """Takes as input the data field and extract the packets. The packets are memorized in the 
        self.packets vaiable as list of Packet objects"""

        continueFlag = True
        firstByteofNextPacket = 0

        if self.PACKETS_DATA == True:
            while continueFlag:
                # Reading length of the packet from its first header
                lenght = (((dataField[firstByteofNextPacket+4]) << 8) |  dataField[firstByteofNextPacket+5])+1
                totalPacketLength = 6 + lenght

                # Calculating the position of the first byte of next packet
                firstByteofNextPacket_old = firstByteofNextPacket
                firstByteofNextPacket= firstByteofNextPacket+totalPacketLength

                if firstByteofNextPacket <= self.frameDataFieldLength:
                    # This control is necessary because if the first byte of next packet is > than the
                    # frame data field length means that the packet spills over the next frame
                    packet = Packet(dataField[firstByteofNextPacket_old:firstByteofNextPacket], self.spID, self.number_of_frame )
                    self.packets.append(packet)
                    
                    # Termination condition
                    if firstByteofNextPacket == self.frameDataFieldLength:
                        continueFlag = False
                else:
                    self.PACKETS_TO_MULTIPLEX = dataField[firstByteofNextPacket_old:self.frameDataFieldLength]
                    continueFlag = False

        elif self.NO_PACKETS:
            # In this case a very big packet is occupying previous frame and perhaps next...
            self.PACKETS_TO_MULTIPLEX.append(dataField)

        else:
            self.IDLE_DATA = dataField
    
    def calculateCRC(self,data):
        self.crc = crc16(data,0,len(data)-2)

    def toDictionary(self):
        """Returns a dictionary with Frame details"""

        frame = {'vc' : str(self.virtualChannelCount), 'spID': str(self.spID),
                'mcCount': str(self.masterChannelcount) , 'vcCount': str(self.virtualChannelCount), 'crc': str(self.CRC_ERROR),
                'info': self.info}
        return frame
    

    
    def __str__(self):
        string = """FRAME PRIMARY HEADER:
VERSION NUMBER: """ + str(self.versionNumber) +"""
SPACECRAFT ID: """ + str(self.spID) + """
VIRTUAL CHANNEL: """ + str(self.virtualChannel) + """
OP. CONTROL FLAG: """ + str(self.opCntrlFieldFLAG)+ """
MASTER CHANNEL COUNT: """ + str(self.masterChannelcount)+"""
VIRTUAL CHANNEL COUNT: """+str(self.virtualChannelCount)+"""
SECONDARY HEADER FLAG: """+str(self.scndHeaderFLAG)+"""
SYNC FLAG: """+str(self.synchFLAG)+"""
PACKET ORDER FLAG: """ +str(self.pktOrderFLAG)+"""
SEGMENT LENGHT ID: """ +str(self.segmentLenghtID)+"""
FIRST HEADER POINTER: """+str(self.firstHeaderPointer) +"""
CRC: """+str(self.crc)+"""
CRC ERROR:"""+str(self.CRC_ERROR)+"""\n-------- PACKETS --------\n"""+self.printPackets(self.packets)

        return string        
    ##########################################################


del frames[0]
cc= 0
l = []

for element in frames:
    frame_1 = Frame(element, cc)
    l.append(frame_1.toDictionary())
    #print("\n" + "-------- FRAME #" + str(cc) + " --------\n" + str(frame_1) + "\n------------------------------------\n")
    cc += 1

y = GUI.NONRealTimeWin(l)
         
