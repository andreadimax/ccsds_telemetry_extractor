import os
import sys

#CONSTANTS
CURRENT_PATH = os.path.dirname(os.path.realpath(sys.argv[0]))
MIB_PATH = os.path.dirname(os.path.realpath(sys.argv[0])) + "/mib/"


def PIC(_type: int, stype: int):

    found = False

    # Reading PIC file
    pic_file = open(MIB_PATH+"pic.dat", "r")

    # PIC Fields
    TYPE = -1
    SUBTYPE = -1
    PI1_OFF = -1
    PI1_WIDTH = -1
    PI2_OFF = -1
    PI2_WIDTH = -1
    PIC_APID = -1

    for line in pic_file.readlines():
        TYPE = line.split('\t')[0]
        SUBTYPE = line.split('\t')[1]

        try:
            PIC_APID = line.split('\t')[6]
        except:
            #nothing to do - PIC_APID remains -1
            pass
        
        # LINE MATCHED
        if (TYPE == _type) & (SUBTYPE == stype):
            PI1_OFF = line.split('\t')[2]
            PI1_WIDTH = line.split('\t')[3]
            PI2_OFF = line.split('\t')[4]
            PI2_WIDTH = line.split('\t')[5]
            found = True
            break

    pic_file.close()
    return (PI1_OFF, PI1_WIDTH, PI2_OFF, PI2_WIDTH, PIC_APID, found)

def PID(_type, stype, apid, pi1, pi2, spid):
    found = False

    # Reading PID file
    pid_file = open(MIB_PATH+"pid.dat", "r")

    # PID Fields
    PID_TYPE = -1
    PID_STYPE = -1
    PID_APID = -1
    PID_PI1_VAL = -1
    PID_PI2_VAL = -1
    PID_SPID = -1
    PID_DESCR = ""
    PID_UNIT = -1
    PID_TPSD = -1
    PID_DFHSIZE = -1
    PID_TIME = ""
    PID_INTER = -1
    PID_VALID = ""
    PID_CHECK = -1
    PID_EVENT = ""
    PID_EVID = ""

    for line in pid_file.readlines():

        # This is the case when the packet does not need extra info
        if pi1 == -1 & pi2 == -1:
            PID_TYPE = line.split('\t')[0]
            PID_STYPE = line.split('\t')[1]
            PID_APID = line.split('\t')[2]

            # LINE MATCHED
            if PID_TYPE == _type & PID_STYPE == stype:

                # In case the APID is specified...
                if apid != -1:
                    if PID_APID != apid:
                        continue
                
                found = True
                PID_VALID = line.split('\t')[12]
                PID_SPID =  line.split('\t')[5]

                # Taking SPID as key
                if PID_VALID == 'N':
                    if PID_SPID != spid:
                        continue

                PID_PI1_VAL = line.split('\t')[3]
                PID_PI2_VAL = line.split('\t')[4]
                PID_SPID =  line.split('\t')[5]
                PID_DESCR = line.split('\t')[6]
                PID_UNIT = line.split('\t')[7]
                PID_TPSD = line.split('\t')[8]
                PID_DFHSIZE = line.split('\t')[9]
                PID_TIME = line.split('\t')[10]
                PID_INTER = line.split('\t')[11]
                PID_CHECK = line.split('\t')[13]
                PID_EVENT = line.split('\t')[14]

                if PID_EVENT != 'N':
                    PID_EVID = line.split('\t')[15]

                break
        
        # This is the case when the packet needs extra info
        else:
            PID_TYPE = line.split('\t')[0]
            PID_STYPE = line.split('\t')[1]
            PID_APID = line.split('\t')[2]
            PID_PI1_VAL = line.split('\t')[3]
            PID_PI2_VAL = line.split('\t')[4]

            # LINE MATCHED
            if PID_TYPE == _type & PID_STYPE == stype & PID_PI1_VAL == pi1 & PID_PI2_VAL == pi2 :

                # In case the APID is specified...
                if apid != -1:
                    if PID_APID != apid:
                        continue
                    
                PID_SPID = line.split('\t')[5]
                PID_VALID = line.split('\t')[12]

                # Taking SPID as key
                if PID_VALID == 'N':
                    if PID_SPID != spid:
                        continue

                found = True
                PID_DESCR = line.split('\t')[6]
                PID_UNIT = line.split('\t')[7]
                PID_TPSD = line.split('\t')[8]
                PID_DFHSIZE = line.split('\t')[9]
                PID_TIME = line.split('\t')[10]
                PID_INTER = line.split('\t')[11]
                PID_VALID = line.split('\t')[12]
                PID_CHECK = line.split('\t')[13]
                PID_EVENT = line.split('\t')[14]

                if PID_EVENT != 'N':
                    PID_EVID = line.split('\t')[15]

                break
    pid_file.close()
    return (PID_SPID, PID_DESCR, PID_UNIT, PID_TPSD, PID_DFHSIZE, PID_TIME, PID_INTER, PID_VALID, PID_CHECK, PID_EVENT, PID_EVID, found)

def TPCF(spid):

    tpcf_file = open(MIB_PATH+"tpcf.dat", "r")

    # TPCF Fields
    TPCF_SPID = -1
    TPCF_NAME = ""
    TPCF_SIZE = -1

    for line in tpcf_file.readlines():
        TPCF_SPID = line.split('\t')[0]
        if(TPCF_SPID == spid):
            TPCF_NAME = line.split('\t')[1]
            TPCF_SIZE = line.split('\t')[2]

        break

    tpcf_file.close()
    return (TPCF_NAME,TPCF_SIZE)

def PLF(spid):
    """Returns a list of dictionaries where every dictionary represent the PLF
       fields of a parameter """

    # Reading PLF file
    plf_file = open(MIB_PATH+"plf.dat", "r")

    #List of parameters
    parameters = []

    PLF_SPID = -1

    for line in plf_file.readlines():
        PLF_SPID = line.split('\t')[1]

        # LINE MATCHED
        if (PLF_SPID == spid):
            param = {}
            param['PLF_NAME'] = line.split('\t')[0]
            param['PLF_OFFBY'] = line.split('\t')[2]
            param['PLF_OFFBI'] = line.split('\t')[3]
            param['PLF_NBOCC'] = line.split('\t')[4]
            param['PLF_LGOCC'] = line.split('\t')[5]
            param['PLF_TIME'] = line.split('\t')[6]
            param['PLF_TDOCC'] = line.split('\t')[7]
            parameters.append(param)
            break

    plf_file.close()
    return parameters

def PCF(param_name):
    found = False
    parameter = {}

    # Reading PCF File
    pcf_file = open(MIB_PATH+"pcf.dat", "r")

    #PCF Fields
    # PCF_NAME = ""
    # PCF_DESCR = ""
    # PCF_PID = -1
    # PCF_UNIT = ""
    # PCF_PTC = -1
    # PCF_PFC = -1
    # PCF_WIDTH = -1
    # PCF_VALID = ""
    # PCF_RELATED = ""
    # PCF_CATEG = ""
    # PCF_NATUR = ""
    # PCF_CURTX = ""
    # PCF_INTER = ""
    # PCF_USCON = ""
    # PCF_DECIM = -1
    # PCF_PARVAL = ""
    # PCF_SUBSYS = ""
    # PCF_VALPAR = -1
    # PCF_SPTYPE = ""
    # PCF_CORR = ""
    # PCF_OBTID = -1
    # PCF_DARC = ""
    # PCF_ENDIAN = ""

    for line in pcf_file.readlines():
        PCF_NAME = line.split('\t')[0]

        if param_name == PCF_NAME:
            found = True

            parameter['PCF_DESCR'] = line.split('\t')[1]
            parameter['PCF_PID'] = line.split('\t')[2]
            parameter['PCF_UNIT'] = line.split('\t')[3]
            parameter['PCF_PTC'] = line.split('\t')[4]
            parameter['PCF_PFC'] = line.split('\t')[5]
            parameter['PCF_WIDTH'] = line.split('\t')[6]
            parameter['PCF_VALID'] = line.split('\t')[7]
            parameter['PCF_RELATED'] = line.split('\t')[8]
            parameter['PCF_CATEG'] = line.split('\t')[9]
            parameter['PCF_NATUR'] = line.split('\t')[10]
            parameter['PCF_CURTX'] = line.split('\t')[11]
            parameter['PCF_INTER'] = line.split('\t')[12]
            parameter['PCF_USCON'] = line.split('\t')[13]
            parameter['PCF_DECIM'] = line.split('\t')[14]
            parameter['PCF_PARVAL'] = line.split('\t')[15]
            parameter['PCF_SUBSYS'] = line.split('\t')[16]
            parameter['PCF_VALPAR'] = line.split('\t')[17]
            parameter['PCF_SPTYPE'] = line.split('\t')[18]

            try:
                parameter['PCF_CORR']= line.split('\t')[19]
                parameter['PCF_OBTID'] = line.split('\t')[20]
                parameter['PCF_DARC'] = line.split('\t')[21]
                parameter['PCF_ENDIAN'] = line.split('\t')[22]
            except IndexError:
                #nothing to do
                pass
    return parameter,found