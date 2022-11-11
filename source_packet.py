from mib_processing import *
from GUI import EventWin

def extractValue(data, position, width):
    """Extract a value from a specified position"""
    value = 0
    number_of_bytes = int(width/8)

    for offs in range(0,number_of_bytes):
        value = value | data[position+offs]
        value = value << 8
    
    return value >> 8

class Packet(object):
    """CCSDS Source Packet object """

    def __init__(self,data, spid, frameID, event_win: EventWin):
        """ Initializes the Packet object """

        #Notes: event_win is the EventWin object created by main()

        ######## ATTRIBUTES ########
        self.SPID = spid
        self.eventWindow = event_win
        self.frameID = frameID
        self.TMSourcePacketPUSVersionNumber = None
        self.ALARM = False  # if just one parameter has the 'ALARM', 'TOLERANCE' or 'OOL' state is setted True

        #----- Primary Header -----#
        self.CCSDS_VERSION = 0
        self.CCSDS_TYPE = 0
        self.CCSDS_APID = -1
        self.CCSDS_PACKET_DATA_LENGTH = 0
        self.CCSDS_SEQUENCE_FLAG = 0
        self.CCSDS_SEQUENCE_COUNT = 0
        #--------------------------#

        #----- Secondary Header-----#
        self.TIME_REF_STATUS = 0
        self.TYPE = -1
        self.SUBTYPE = -1
        self.PACKET_SUBCOUNTER = 0
        self.DESTINATION_ID = 0
        self.TIME = None
        #----------------------------#

        self.data = []
        #############################

        ######## FLAGS ########
        self.SecHeaderFieldFLAGFLAG = False
        #######################

        ######### STRINGS #########
        self.string_PH = None
        self.string_SH = None
        ###########################

        #Building the packet infos
        self.firstHeaderInfoExtractor(data)
        if self.SecHeaderFieldFLAGFLAG == True:
            self.secondaryHeaderInfoExtractor(data)
        else:
            self.string_SH = ""


    ############# PROCESSING METHODS #############

    def firstHeaderInfoExtractor(self, packet):
        """ Set the First Header Parameters of the packet """

        self.CCSDS_VERSION = (packet[0] & 0xE0)>>5
        self.CCSDS_TYPE = (packet[0] & 0x10)>>4
        self.SecHeaderFieldFLAGFLAG = (packet[0] & 0x08)>>3
        self.CCSDS_APID = ((packet[0] & 7) << 8) | packet[1]
        self.CCSDS_SEQUENCE_FLAG = (packet[2] & 0xC0)>>6
        self.CCSDS_SEQUENCE_COUNT = ((packet[2] & 0x3F) << 8 ) | packet[3]
        self.CCSDS_PACKET_DATA_LENGTH = (packet[4] << 8) | packet[5]

        #version
        version = "PACKET VERSION : " + str(self.CCSDS_VERSION)+"\n"

        #type
        if self.CCSDS_TYPE == 0:
            typeP = "PACKET TYPE : TELEMETRY\n"
        elif self.CCSDS_TYPE == 1:
            typeP = "PACKET TYPE : TELECOMMAND\n"
        else: 
            print("Error in reading packet type")
            typeP = ""

        #secondary header presence
        if self.SecHeaderFieldFLAGFLAG == 0:
            sH = "PACKET SECONDARY HEADER: FALSE\n"
        elif self.SecHeaderFieldFLAGFLAG == 1:
            sH = "PACKET SECONDARY HEADER: TRUE\n"
            self.SecHeaderFieldFLAGFLAG = True
        else: 
            print("Error in reading packet sec header flag")
            sH = ""

        #packet apid
        pT = "PACKET APID: " + str(self.CCSDS_APID)+"\n"

        #sequence flag
        if self.CCSDS_SEQUENCE_FLAG == 3:
            sF = "PACKET SEQUENCE FLAG: 11\n"
        elif self.CCSDS_SEQUENCE_FLAG == 1:
            sF = "PACKET SEQUENCE FLAG: 01\n"
        elif self.CCSDS_SEQUENCE_FLAG == 0:
            sF = "PACKET SEQUENCE FLAG: 00\n"
        elif self.CCSDS_SEQUENCE_FLAG == 2:
            sF = "PACKET SEQUENCE FLAG: 10\n"
        else:
            print("Error in reading packet sequence flag")
            sF = ""

        # Sequence count
        seq = "PACKET SEQUENCE NUMBER: " + str(self.CCSDS_SEQUENCE_COUNT)+"\n"

        # Packet length
        length = "PACKET DATA LENGTH: " + str(self.CCSDS_PACKET_DATA_LENGTH)+"\n"

        # Final string builder
        self.string_PH = "\n<<PRIMARY HEADER>>\n" + version + typeP + sH + pT + sF + seq + length


    def secondaryHeaderInfoExtractor(self, packet):
        self.TMSourcePacketPUSVersionNumber = (packet[6] & 0xF0) >> 4

        if self.TMSourcePacketPUSVersionNumber == 1:
            """ Processing CCSDS Packet Version 1 """
            self.TYPE = packet[7]
            self.SUBTYPE = packet[8]
            self.PACKET_SUBCOUNTER = packet[9]
            self.DESTINATION_ID = None
            self.TIME = None

            # Creating string for __str__ method
            self.string_SH = "<< SECONDARY HEADER >>\n" + "SECONDARY HEADER VERSION: " + str(self.TMSourcePacketPUSVersionNumber) + "\nTYPE: " + str(self.TYPE) + "\nSUBTYPE: " + str(self.SUBTYPE) + "\nPACKET SUBCOUNTER: " + str(self.PACKET_SUBCOUNTER) + "\nDESTINATION ID: " + str(self.DESTINATION_ID) + "\nTIME: " + str(self.TIME)            
        
        elif self.TMSourcePacketPUSVersionNumber == 2:
            """Processing CCSDS Packet Version 2 """
            self.TIME_REF_STATUS = packet[6]  & 0x07
            self.TYPE = packet[7]
            self.SUBTYPE = packet[8]
            self.MSG_TYPE_COUNTER = (packet[9] << 8) | packet[10]
            self.DESTINATION_ID = (packet[11] << 8) | packet[12]
            self.TIME = None

            # Creating string for __str__ method
            self.string_SH = "<< SECONDARY HEADER >>\n" + "SECONDARY HEADER VERSION: " + str(self.TMSourcePacketPUSVersionNumber) + "\nTIME_REF_STATUS: " + str(self.TIME_REF_STATUS) + "\nTYPE: " + str(self.TYPE) + "\nSUBTYPE: " + str(self.SUBTYPE) + "\nMSG_TYPE_COUNTER: " + str(self.MSG_TYPE_COUNTER) + "\nDESTINATION ID: " + str(self.DESTINATION_ID) + "\nTIME: " + str(self.TIME)

    ##############################################

    def __str__(self):
        #Building a summary info string of packet
        self.packet2String = self.string_PH + self.string_SH
        return self.packet2String

    def getDescriptionFromMIB(self):
        pass

    #----------- DATA PROCESSING -----------#

    def getData(self):
        """ Returns data from the packet according to MIB informations"""
        
        #Checking type & subtype
        if self.TYPE == -1 | self.SUBTYPE == -1 :
            #LOG_ERROR "Error in reading type & subtype"
            pass
            
        #----------- PIC -----------#
        PI1_OFF, PI1_WIDTH, PI2_OFF, PI2_WIDTH, APID, found = PIC(self.TYPE, self.SUBTYPE)
        if found == False:
            # LOG_ERROR "Packet not in PIC Table"
            pass
        else:
            if PI1_OFF != -1:
                PI1 = extractValue(data, PI1_OFF-1, PI1_WIDTH)
                if PI2_OFF != -1:
                    PI2 = extractValue(data, PI2_OFF-1, PI2_WIDTH)
        #---------------------------#

        #----------- PID -----------#
        (PID_SPID, PID_DESCR, PID_UNIT, PID_TPSD, PID_DFHSIZE, PID_TIME, PID_INTER, PID_VALID, PID_CHECK, PID_EVENT, PID_EVID, found) = PID(self.TYPE,self.SUBTYPE,self.CCSDS_APID,PI1, PI2,-1)
        
        # Checking Match in table
        if found == False:
            # LOG_ERROR = "No match in PID Table"
            return

        # Checking EVENT
        if PID_EVENT != 'N':
                self.eventWindow.add_event(self.CCSDS_SEQUENCE_COUNT,PID_EVENT,PID_EVID)
        #---------------------------#

        if PID_TPSD == -1:
            # Fixed Packet

            params_to_check = [] #For these parameters the PCF VALID field is not empty

            #---------- PLF ----------#
            params = PLF(PID_SPID)
            #-------------------------#

            #---------- PCF ----------#
            
            for param in params:

                pcf,found = PCF(param['PLF_NAME'])
                if found:
                    
                    if pcf['PCF_VALID'] != "" & pcf['PCF_VALPAR'] != "":
                        p = [pcf['PCF_NAME', pcf['PCF_VALID'], pcf['PCF_VALPAR']]]
                        params_to_check.append(p)

                    if pcf['PCF_RELATED'] != "":

                        if pcf['PCF_PTC'] == 11:
                            #TO-DO
                            pass
                        elif pcf['PCF_NATUR'] == 'S':
                            #Saved synthetic parameters
                            #TO-DO
                            pass

                    if pcf['PCF_RELATED'] == "T" & pcf['PCF_PTC'] != 8:
                        #LOG_ERROR = Textual Parameter pcf['PCF_NAME'] with wrong calibration

                        if pcf['PCF_CURTX'] == "":
                            if pcf['PCF_CATEG'] == 'S':
                                #LOG_ERROR = Parameter pcf['PCF_NAME'] with PCF_CATEG = 'S' but PCF_CURTX = NULL
                                pass
                            else:
                                if pcf['PCF_CATEG'] == 'T' | pcf['PCF_PTC'] == 7 | pcf['PCF_PTC'] == 8 | pcf['PCF_PTC'] == 9 | pcf['PCF_PTC'] == 10:
                                #LOG_ERROR = Parameter pcf['PCF_NAME'] with no necessary calibration but PCF_CURTX not NULL
                                    pass

                            if pcf['PCF_USCON'] == 'Y':
                                #see OCP TO-DO
                                pass
                    if pcf['PCF_PARVAL'] != "" & pcf['PCF_NATUR'] == 'C':
                        #LOG_ERROR = Param pcf['PCF_NAME'] has the type 'CONSTANT' but no PCF_PARVAL found
                        pass
                        
                else:
                    #LOG_ERROR = Param pcf['PCF_NAME'] not found in pcf
                    pass

            #TO-CONTINUE
            #params elaboration
            

        else:
            # Variable Packet
            pass

        

                
                



    def checkValues(self):
        """Check the status of the parameters and eventually set the self.ALARM FLAG"""
        pass

    def toDictionary(self):
        """Returns a dictionary with packet details"""

        pkt = {'type' : self.TYPE, 'subtype': self.SUBTYPE,
                'pi1': None , 'pi2': None, 'apid': self.CCSDS_APID,
                'spid': self.SPID, 'genTime': None, 'acqTime': None,
                'frameID': self.frameID, 'alarm':self.ALARM, 'description': self.getDescriptionFromMIB}
        return pkt

data = [0x0A,0x00,0xA1]
print(extractValue(data,0,8))