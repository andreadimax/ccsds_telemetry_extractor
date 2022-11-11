import datetime
import sys
import serial
from serial.tools.list_ports import comports
import subprocess
from tkinter import *
from tkinter import ttk
from tkinter import messagebox


#14 octets
#--------  Primary headers --------#
#2 last bytes need to be added to insert (packet length -1) in 16 bits
ph_OBC = [0xC0, 0x00, 0x18, 0x00, 0xC0, 0x00]
ph_EPS = [0xC0, 0x00, 0x18, 0x01, 0xC0, 0x00]
ph_ADCS = [0xC0, 0x00, 0x18, 0x02, 0xC0, 0x00, 0x00, 0x0D]
ph_WIFI = [0xC0, 0x00, 0x18, 0x03, 0xC0, 0x00]

class ESATGUI():
    def __init__(self):
        self.ports = []
        self.win = Tk()
        self.win.title("ESAT Command Module")
        self.win.resizable(0,0)
        self.win.geometry("350x180")

        fr0 = Frame(self.win)
        fr0.pack()
        lb0 = Label(fr0, text='Enter value in rpm:')
        lb0.pack(pady =10)

        self.entry = Entry(fr0)
        self.entry.pack(pady=5)

        bt0 = Button(fr0, text='Send', command = self.send)
        bt0.pack()

        #Tree View
        self.tree = ttk.Treeview(fr0, selectmode="browse")
        self.tree.pack()
        self.tree['columns'] = ['name']
        self.tree.column("#0")
        self.tree.column("name")
        self.tree.heading("#0",text="Available Ports")
        self.tree.heading("name",text="Description")
        self.insert_ports()

        self.win.mainloop()

    def create_sec_header(self, subsystem, command_code):
        sec_header = [0x50]

        #Adding timestamp in BCD
        date = datetime.datetime.now().strftime('%Y%m%d%H%M%S')

        for i in [0,2,4,6,8,10,12]:
            sec_header.append(((int(date[i])<<4)|(int(date[i+1]))))
        
        #Adding software infos
        OBC = []
        EPS = []
        ADCS = [3,3,0]
        WIFI = []

        if subsystem == 0:
            for val in OBC:
                sec_header.append((val))
        elif subsystem == 1:
            for val in EPS:
                sec_header.append((val))
        elif subsystem == 2:
            for val in ADCS:
                sec_header.append((val))
        elif subsystem == 3:
            for val in WIFI:
                sec_header.append((val))

        #Adding command code
        sec_header.append((command_code))

        return sec_header

    def send(self):
        #Taking position of selected item in self.ports
        element = int(str(self.tree.selection()[0][3]))-1

        #Packet creation
        packet = []
        packet.extend(ph_ADCS)
        packet.extend(self.create_sec_header(2,33))

        value = int(self.entry.get())
        packet.append((value & 0xFF00)>>8)
        packet.append(value & 0x00FF)

        packet.append(0xC0)

        #Sending packet on serial
        # _file = open("/home/andrea/Scrivania/Prove/packet.bin", "wb")
        # _file.write(bytearray(packet))
        # _file.close()

        ser = serial.Serial(self.ports[element], baudrate=9600)
        if ser.is_open == True:
            print("Port opened!\n")
            for val in packet:
                ser.write(val)
            #ser.write(bytearray(packet))
            ser.close()
            messagebox.showinfo('Info', 'Packet sent!')
        else:
            print("Port is not opened")

    def insert_ports(self):
        counter = 0 #Counter for inserting elements in treeview

        if sys.platform.startswith('win'):
            coms = ['COM%s' % (i + 1) for i in range(256)]
            for val in coms:
                try:
                    s = serial.Serial(val, baudrate=9600)
                    s.close()
                    self.ports.append(str(val))
                    self.tree.insert("", counter, text=str(val), values=("No description available",))
                    counter += 1
                except serial.SerialException:
                    pass

        elif sys.platform.startswith('lin'):
            ports = subprocess.check_output(['python3.7', '-m', 'serial.tools.list_ports','-v'])
            _list = str(ports).split('\\n')
            for i,val in enumerate(_list):
                if _list[i].find("/dev/") != -1:
                    self.tree.insert("", counter, text=_list[i].replace("b'", "").replace(" ", ""), values=(_list[i+1].replace("   desc: ", "")))
                    counter += 1
                    self.ports.append(_list[i].replace("b'", "").replace(" ", ""))

w = ESATGUI()