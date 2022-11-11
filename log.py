import os
import sys
import datetime
from tkinter import *

class LOG_User():

    def __init__(self):

        self._file = None

        date = datetime.datetime.now().strftime("%d_%m_%y")
        path=os.path.dirname(os.path.realpath(sys.argv[0]))+"/Log/Users/"+date
        if(os.access(path, mode= os.F_OK)):
            self._file = open(path+"/users.data", "a+")
            #self._file.write("self.TYPE	self.SUBTYPE	None	None	self.CCSDS_APID	self.SPID	None	None	self.frameID	self.ALARM	self.getDescriptionFromMIB")
        else:
            os.mkdir(path)
            self._file = open(path+"/users.data", "w+")

    def log(self, username: str):
        """ Add the log data to the file of the day """
        date = datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S")
        self._file.write(">>> " + date+": "+ username + " logged\n")

    def unlog(self, username: str):
        """ Add the unlog data to the file of the day """
        date = datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S")
        self._file.write(">>> " + date+": "+ username + " unlogged\n")

    def close(self):
        self._file.close()

    def __str__(self):
        """ Print the content of file of the current day """
         # To read the file is necessary to restore the pointer to the beginning
         # and after the read the old position needs to be restored
        current_pos = self._file.tell()
        self._file.seek(0,0)
        text = self._file.read()
        self._file.seek(current_pos, 0)
        return text

    def window(self):
        """ Print the content of file of the current day on a tkinter interface """
        info = Tk()
        info.title('Users Log Window')
        info.resizable(0,0)
        info.geometry("560x400")

        frame0 = Frame(info)
        frame0.pack(fill=BOTH, expand = 1)

        src = Scrollbar(frame0, orient=VERTICAL)
        lb = Text(frame0, yscrollcommand= src.set)
        lb.insert(INSERT, str(self))
        lb.pack(side = LEFT)
        src.pack(side=RIGHT, fill=Y)

        src.config(command = lb.yview)
        
        info.mainloop()

class LOG_Packets():

    def __init__(self):

        self._file = None

        date = datetime.datetime.now().strftime("%d_%m_%y")
        path=os.path.dirname(os.path.realpath(sys.argv[0]))+"/Log/Packets/"+date
        if(os.access(path, mode= os.F_OK)):
            self._file = open(path+"/packets.data", "a+")
        else:
            os.mkdir(path)
            self._file = open(path+"/packets.data", "w+")

    def add(self, packet):
        """ Add the packet's received info to the data file of the current day """
        date = datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S")
        self._file.write(date+": "+ str(packet.toDictionary()).replace("{", "").replace("}", "").replace(",", " |")+"\n")

    def close(self):
        self._file.close()

    def __str__(self):
        """ Print the content of file of the current day """
         # To read the file is necessary to restore the pointer to the beginning
         # and after the read the old position needs to be restored
        current_pos = self._file.tell()
        self._file.seek(0,0)
        text = self._file.read()
        self._file.seek(current_pos, 0)
        return text

    def window(self):
        """ Print the content of file of the current day on a tkinter interface """
        info = Tk()
        info.title('Users Log Window')
        info.resizable(0,0)
        info.geometry("560x400")

        frame0 = Frame(info)
        frame0.pack(fill=BOTH, expand = 1)

        src = Scrollbar(frame0, orient=VERTICAL)
        lb = Text(frame0, yscrollcommand= src.set)
        lb.insert(INSERT, str(self))
        lb.pack(side = LEFT)
        src.pack(side=RIGHT, fill=Y)

        src.config(command = lb.yview)
        
        info.mainloop()

class LOG_Frames():

    def __init__(self):

        self._file = None

        date = datetime.datetime.now().strftime("%d_%m_%y")
        path=os.path.dirname(os.path.realpath(sys.argv[0]))+"/Log/Frames/"+date
        if(os.access(path, mode= os.F_OK)):
            self._file = open(path+"/frames.data", "a+")
        else:
            os.mkdir(path)
            self._file = open(path+"/frames.data", "w+")

    def add(self, frame):
        """ Add the frame's received info to the data file of the current day """
        date = datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S")
        self._file.write(date+": "+ str(frame.toDictionary()).replace("{", "").replace("}", "").replace(",", " |")+"\n")

    def close(self):
        self._file.close()

    def __str__(self):
         # To read the file is necessary to restore the pointer to the beginning
         # and after the read the old position needs to be restored
        current_pos = self._file.tell()
        self._file.seek(0,0)
        text = self._file.read()
        self._file.seek(current_pos, 0)
        return text

    def window(self):
        """ Print the content of file of the current day on a tkinter interface """
        info = Tk()
        info.title('Users Log Window')
        info.resizable(0,0)
        info.geometry("560x400")

        frame0 = Frame(info)
        frame0.pack(fill=BOTH, expand = 1)

        src = Scrollbar(frame0, orient=VERTICAL)
        lb = Text(frame0, yscrollcommand= src.set)
        lb.insert(INSERT, str(self))
        lb.pack(side = LEFT)
        src.pack(side=RIGHT, fill=Y)

        src.config(command = lb.yview)
        
        info.mainloop()

class LOG_Events():

    def __init__(self):

        self._file = None

        date = datetime.datetime.now().strftime("%d_%m_%y")
        path=os.path.dirname(os.path.realpath(sys.argv[0]))+"/Log/Events/"+date
        if(os.access(path, mode= os.F_OK)):
            self._file = open(path+"/users.data", "a+")
            #self._file.write("self.TYPE	self.SUBTYPE	None	None	self.CCSDS_APID	self.SPID	None	None	self.frameID	self.ALARM	self.getDescriptionFromMIB")
        else:
            os.mkdir(path)
            self._file = open(path+"/users.data", "w+")

    def write_event(self, event):
        """ Add the log data to the file of the day """
        date = datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S")
        self._file.write(">>> " + date + " " + event + "\n")

    def close(self):
        self._file.close()

    def __str__(self):
        """ Print the content of file of the current day """
         # To read the file is necessary to restore the pointer to the beginning
         # and after the read the old position needs to be restored
        current_pos = self._file.tell()
        self._file.seek(0,0)
        text = self._file.read()
        self._file.seek(current_pos, 0)
        return text

# log_usr = LOG_User()
# log_usr.window()
# log_usr.log("lol")
# log_usr.unlog("unlol")
# log_usr.window()
# log_usr.close()
# log_frms = LOG_Frames()
# log_pkts = LOG_Packets()