from tkinter import *
from tkinter import Menu
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox
from tkinter import filedialog
from tkcalendar import Calendar, DateEntry
from log import LOG_Frames
from log import LOG_Packets
from log import LOG_Events
import datetime
import time
import os
import sys
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# GLOBAL VARIABLES
image = None
image1 = None
updateFreq = 5
packets_to_visualize = 10

class EventWin():
    """ This Windows is used to visalize events generated from packets """

    def __init__(self):

        self.event = Tk()
        self.event.title('Options')
        self.event.resizable(0,0)
        self.event.geometry("700x350")
        self.counter = 0

        # Treeview
        self.tree = ttk.Treeview(self.event)
        self.tree["columns"]=("packet","severity","id")
        self.tree.column("#0",width=100,minwidth=50,stretch = NO)
        self.tree.column("severity",width=80,minwidth=50,stretch = NO)
        self.tree.column("id",width=80,minwidth=50,stretch = NO)
        self.tree.heading("#0", text="PACKET #")
        self.tree.heading("severity",text="SEVERITY")
        self.tree.heading("id", text="EVENT ID")

        # Configuring background colours
        self.tree.tag_configure('red', background='#FF0000')
        self.tree.tag_configure('yellow', background='yellow')

        self.event.mainloop()

    def add_event(self, packet_number, severity, id):
        """ Add an event to the treeview and update the log file"""
        # Adding log
        log = LOG_Events()
        log.write_event(str(packet_number)+" "+str(severity)+" "+str(id))
        log.close()

        if severity == 'W':
            self.tree.insert("", self.counter, text="PACKET #"+str(packet_number), values=( "WARNING", str(id)), tags=('yellow'))
        elif severity == 'A':
            self.tree.insert("", self.counter, text="PACKET #"+str(packet_number), values=( "ALARM", str(id)), tags=('red'))
        else:
            self.tree.insert("", self.counter, text="PACKET #"+str(packet_number), values=( "INFO", str(id)))




class OptionsWin():

    def __init__(self):

        # Attributes
        global updateFreq
        global packets_to_visualize

        self.opt = Tk()
        self.opt.title('Options')
        self.opt.resizable(0,0)
        self.opt.geometry("400x350")

        #------------- Interface -------------#

        frame0 = Frame(self.opt)
        frame0.pack(fill=BOTH, expand = 1)

        # Update frequency
        frame1 = Frame(frame0)
        frame1.pack(pady=10)

        freqLabel = Label(frame1, text="Update frequency", font=("Comic Sans MS", 12), justify= LEFT)
        freqLabel.grid(row=0, column=0, sticky=W, padx=7, pady=10)

        combo0 = ttk.Combobox(frame1, width=5)
        combo0['values']=(0.1,0.5,1,3,5,10,20,30,60)
        combo0.grid(row=0, column=1, padx=5)

        btn = Button(frame1, width = 5, text ="Set", command= lambda:self.assign(1, combo0.get()))
        btn.grid(row=0, column=2, sticky=E)

        # Number of packets

        freqLabel1 = Label(frame1, text="Previous packets to visualize", font=("Comic Sans MS", 12))
        freqLabel1.grid(row=1, column=0, sticky=W, padx=7, pady=10)

        combo1 = ttk.Combobox(frame1, width=5)
        combo1['values']=(5,10,20)
        combo1.grid(row=1, column=1, padx=5)

        btn1 = Button(frame1, width = 5, text ="Set", command= lambda:self.assign(0,combo1.get()))
        btn1.grid(row=1, column=2, sticky=E)

        self.opt.mainloop()

    def assign(self, code:int, value):
        """ Updates the global variables. Codes: 1 -> frequency | 2 -> packets """
        global packets_to_visualize
        global updateFreq
        if code:
            updateFreq=value
            messagebox.showinfo('Value Updated', 'New Update Frequency: ' + str(updateFreq))
        else:
            packets_to_visualize=value
            messagebox.showinfo('Value Updated', '# of prev. packets: ' + str(packets_to_visualize))

#OptionsWin()        

class UserWin():

    def __init__(self, username:str):

        self.usrwin = Tk()
        self.usrwin.title(username)
        self.usrwin.resizable(0,0)
        self.usrwin.geometry("350x180")

        fr0 = Frame(self.usrwin)
        fr0.pack()
        lb0 = Label(fr0, text='User:', font=("Comic Sans MS", 16))
        lb1 = Label(fr0, text=username, font=("Comic Sans MS", 15, "bold italic"))
        lb0.pack(side=LEFT, pady =10)
        lb1.pack(side=LEFT, pady =10)

        fr1 = Frame(self.usrwin)
        fr1.pack(pady=10)
        bt0 = Button(fr1, text='Add User', command = self.addUser)
        bt1 = Button(fr1, text='Change Password', command = lambda : self.changePassword(username))
        bt0.pack(side=LEFT, padx =10)
        bt1.pack(side=LEFT, padx = 10)


        fr2 = Frame(self.usrwin)
        fr2.pack()
        lb1 = Label(fr2, text='Old Pass/New User:', font=("Comic Sans MS", 11))
        self.entr0 = Entry(fr2)
        lb1.pack(side=LEFT)
        self.entr0.pack(side=LEFT)

        fr3 = Frame(self.usrwin)
        fr3.pack()
        lb2 = Label(fr3, text='Password:', font=("Comic Sans MS", 11))
        self.entr1 = Entry(fr3, show="*")
        lb2.pack(side=LEFT, padx = 5)
        self.entr1.pack(side=LEFT)


        self.usrwin.mainloop()

    def getUsersFromFile(self):
        """ Read the user txt file and create a list of dictionaries with KEYS->'username' and 'password' """

        users = list()

        _file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + '/Users/users.data', "r")
        for value in _file:
            print(value)
            try:
                users.append({'username':value.split('\t')[0], 'password': value.split('\t')[1]})
            except IndexError:
                pass

        _file.close()

        return users

    def addUser(self):
        """ Get inserted data from User Win fields and insert in the database. It checks if the user is already inserted"""
        _list = self.getUsersFromFile()
        name = self.entr0.get()
        password = self.entr1.get()

        # Check if the fiels are empty
        if (name == "") | (password == ""):
            messagebox.showwarning("Warning", "No data inserted")
            return

        # Check if the user is already inserted
        for user in _list:
            if name == user['username']:
                messagebox.showinfo('Warning', 'User already inserted!')
                return 
        
        # Adding the new user
        _file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + '/Users/users.data', "a")
        _file.write(name+"\t"+password+"\n")
        _file.close()
        messagebox.showinfo('Operation Completed', 'User inserted correctly')

    def changePassword(self, user_logged):
        """ Change the passord of the current user """
        old_pass = self.entr0.get()
        password = self.entr1.get()

        # Check if the pass field is empty
        if password == "":
            messagebox.showwarning("Warning", "No passord inserted!")
            return

        # Updating pass
        _list = self.getUsersFromFile()
        for user in _list:
            if user_logged == user['username']:
                if (user['password'] == old_pass) | (user['password'] == old_pass+"\n"):
                    user['password'] = password+"\n"

                    #Updating the file
                    _file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + '/Users/users.data', "w")
                    for user in _list:
                        _file.write(user['username']+"\t"+user['password'])
                    _file.close()
                    messagebox.showinfo('Operation Completed', 'Password changed correctly')
                    break
                else:
                    messagebox.showwarning('Error', 'Password not correct!')
                    break

#UserWin('Antonio Esposito')


########################### REAL TIME WINDOW ###########################
########################################################################

class RealTimeWindow():
    
    def __init__(self, parent,  list_of_packets, lista, user_logged: str, log_usr):

        #VARIABLES
        self.version = "0.0.2"
        self.frames = []                        # needed to filter 
        self.list_of_packets = list_of_packets  # needed to update the treeview when new packets incoming
        self.values = {}                        # values to plot
        self.freqUpdate = 1                     # frequency update the Treeview
        self.sessionActive = True               # flag to stop the process

        #-------- Setting values to plot --------#
        for _list in lista:
            for elem in _list:
                param = elem['name']
                if param in self.values:
                    self.values[param].append(float(elem['value']))
                else:
                    self.values[param] = [elem['value']]
        #----------------------------------------#


        #-------- MAIN WINDOW --------#
        self.w = Toplevel()
        self.w.title('Real Time Window - ' + "Version: " + self.version)
        self.w.resizable(0,0)
        self.w.geometry("1015x430")

        #SETTING THE WINDOW ICON
        self.w.tk.call('wm', 'iconphoto', self.w._w, PhotoImage(file= os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat.ico'))

        #-----------------------------#

        #----------- Quit Function -----------#
        def on_closing():
            if messagebox.askokcancel("Quit", "Do you want to quit?"):
                log_usr.unlog(user_logged)
                log_usr.close()
                self.sessionActive = False
                self.w.destroy()
                parent.destroy()
        #-------------------------------------#        

        #------ Menu ------#
        menu = Menu(self.w)
        _file = Menu(menu, tearoff=0)
        _file.add_command(label='TM File...')
        _file.add_command(label='Save capture...', command = self.print_on_file)
        _file.add_command(label='Options', command=OptionsWin)
        _file.add_separator()
        _file.add_command(label='Terminate session', command=on_closing)
        menu.add_cascade(label='File', menu=_file)
        
        log = Menu(menu, tearoff=0)
        log.add_command(label='User Log Window', command=log_usr.window)
        log.add_command(label='Packet Log Window')
        menu.add_cascade(label='Log', menu=log)

        user = Menu(menu, tearoff=0)
        user.add_command(label=user_logged, command = lambda: UserWin(user_logged))
        menu.add_cascade(label='User', menu=user)
        self.w.config(menu=menu)
        #------------------#

        ######### Interaction part #########

        frame0 = Frame(self.w)
        frame0.pack(fill=X, expand=1)

        frame1 = Frame(self.w)

        #-------- FILTER SELECT --------#
        label = Label(frame0, text="Filter: ")
        label.pack(side=LEFT, padx = 10)
        combo = ttk.Combobox(frame0)
        combo['values'] = self.getFrames(list_of_packets)
        #-------------------------------#

        src = Scrollbar(frame1, orient = VERTICAL)
        self.tree = ttk.Treeview(frame1, yscrollcommand = src.set)
        combo.bind("<<ComboboxSelected>>", lambda comm: self.updateElenco(str(combo.get())))
        combo.pack(side=LEFT)

        #---------- Info ----------#
        info_Frame = Frame(frame0)
        info_Frame.pack(side=LEFT, padx = 30)

        lbl = Label(info_Frame, text="Total number of packets: "+str(len(self.list_of_packets)))
        lbl1 = Label(info_Frame, text="Time: " + datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S"))
        lbl.pack()
        lbl1.pack()
        #--------------------------#

        image = PhotoImage(file = os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat_retina_1.png')
        imageLabel = Label(frame0, image = image)
        imageLabel.image = image
        imageLabel.pack(side=RIGHT, padx= 20)

        frame1.pack(fill = BOTH,expand=1)
        ##################################

        ############################## TREEVIEW ##############################

        #----------------- Treeview set -----------------#
        self.tree.pack(side = LEFT, fill=Y)
        self.tree["columns"]=("type","stype","p1","p2","apid","spid","pktGEN","pktACQ","frameID","descr")
        self.tree.column("#0",width=100,minwidth=50,stretch = NO)
        self.tree.column("type",width=80,minwidth=50,stretch = NO)
        self.tree.column("stype",width=80,minwidth=50,stretch = NO)
        self.tree.column("p1",width=80,minwidth=50,stretch = NO)
        self.tree.column("p2",width=80,minwidth=50,stretch = NO)
        self.tree.column("apid",width=80,minwidth=50,stretch = NO)
        self.tree.column("spid",width=80,minwidth=50,stretch = NO)
        self.tree.column("pktGEN",width=110,minwidth=50,stretch = NO)
        self.tree.column("pktACQ",width=110,minwidth=50,stretch = NO)
        self.tree.column("frameID",width=80,minwidth=50,stretch = NO)
        self.tree.column("descr",width=120,minwidth=50,stretch = NO)
        self.tree.heading("#0", text="PACKET #")
        self.tree.heading("type",text="Type")
        self.tree.heading("stype", text="Subtype")
        self.tree.heading("p1", text="PI1")
        self.tree.heading("p2", text="PI2")
        self.tree.heading("apid", text="APID")
        self.tree.heading("spid", text="SPID")
        self.tree.heading("pktGEN", text="PKT GEN TIME")
        self.tree.heading("pktACQ", text="PKT ACQ TIME")
        self.tree.heading("frameID", text="FRAME ID")
        self.tree.heading("descr", text="Description")

        # CONFIGURING RED BACKGROUND FOR PACKET WITH ERRORS
        self.tree.tag_configure('red', background='#FF0000')

        # CONFIGURING DOUBLE_CLICK ON PACKET
        style = ttk.Style()
        def fixed_map(option):
            return [elm for elm in style.map("Treeview", query_opt=option)
                if elm[:2] != ("!disabled", "!selected")]

        style.map("Treeview", foreground=fixed_map("foreground"), background=fixed_map("background"))
        self.tree.bind('<Double-1>', self.tree_select_event)

        # ADDING ELEMENTS TO THE TREEVIEW CONFIGURATION
        self.addElement(self.list_of_packets)

        # SCROLLBAR CONFIGURATION
        src.pack(side=RIGHT, fill = Y)
        src.config(command = self.tree.yview)

        # Setting close event
        self.w.protocol("WM_DELETE_WINDOW", on_closing)

        #self.w.mainloop()

    def plot_values(self, param_name):
        """Plot the values using matplotlib"""
        y_values = self.values[param_name]
        x_values = np.arange(0, len(self.values[param_name]), 1, dtype='int')
        fig = plt.figure()
        psd = fig.add_subplot()
        fig.suptitle(param_name)
        psd.set_xlabel('Packets')
        psd.set_ylabel('Values')
        psd.plot(x_values,y_values)
        plt.show()

    def print_on_file(self):
        """ Print the info of all packets actually showed in the Treeview on a txt file """
        path = filedialog.askopenfilename()
        file = open(path, "w+")

        counter = 0
        for packet in self.list_of_packets:
            file.write("PACKET #"+str(counter)+ " "+(str(packet)+"\n").replace("{", "").replace("}", "").replace(", ", " "))
            counter += 1

        file.close()

        messagebox.showinfo("Info", 'Operation completed!')

    #------- Info Windows -------#
    def show_info(self, data_list: list, number_of_packet):
        inf = Toplevel()
        inf.title("PACKET #" + str(number_of_packet))
        inf.resizable(0,0)
        inf.geometry("790x400")

        #SETTING THE WINDOW ICON
        inf.tk.call('wm', 'iconphoto', inf._w, PhotoImage(file= os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat.ico'))
        

        class Table(RealTimeWindow): 
            def __init__(self, window, rows=0, columns=0):
                self.rows = []
                for row in range(rows):
                    current_row = []
                    for column in range(columns):
                        label = Label(window, borderwidth=0, width = 15)
                        label.grid(row=row, column=column, sticky="nsew", padx=1, pady=1)
                        current_row.append(label)
                    self.rows.append(current_row)


            def set(self, row, name, value, state, parent_of_table):
                if row != 0: # First row is assigned to titles
                    parameter = self.rows[row]
                    Button(parameter[0], text=name, command = lambda: RealTimeWindow.plot_values(parent_of_table, name)).pack()
                    parameter[1].configure(text=value)
                    if state == "OOL":
                        parameter[2].configure(bg='yellow')
                    elif state == 'TOLERANCE':
                        parameter[3].configure(bg='grey')
                    elif state == "ALARM":
                        parameter[4].configure(bg='red')
                else:
                    print("Error: row 0 can't be written")

        # Building the table
        frame0 = Frame(inf)
        frame0.pack(fill=BOTH,expand=True)
        frame = Frame(frame0, height=300)
        frame.pack(fill=X, expand = True)
        frame.pack_propagate(False)
        number_of_rows = len(data_list)+1
        scr = Scrollbar(frame, orient = VERTICAL)
        scr.pack(side=RIGHT, fill = Y)
        canvas = Canvas(frame, yscrollcommand=scr.set, scrollregion=(0,0,500,500), bg='black')
        canvas.pack(side=LEFT, fill=BOTH, expand = True)
        frame2= Frame(canvas, bg='black')
        frame2.pack(fill=BOTH, expand = True)
        canvas.create_window(0,0, window=frame2, anchor=N+W)
        table = Table(frame2, number_of_rows, 5)
        scr.config(command=canvas.yview)

        # Setting first row
        table.rows[0][0].configure(text="Name of Parameter", font=("Helvetica", 11, "bold"), width = 20)
        table.rows[0][1].configure(text="Value", font=("HelveticaBold", 11 , "bold"))
        table.rows[0][2].configure(text="OOL", font=("HelveticaBold", 11, "bold"))
        table.rows[0][3].configure(text="Tolerance", font=("HelveticaBold", 11, "bold"))
        table.rows[0][4].configure(text="ALARM", font=("HelveticaBold", 11, "bold"))

        # Setting values
        for i in range(1, number_of_rows):
            table.set(i,data_list[i-1]['name'], data_list[i-1]['value'] , data_list[i-1]['state'], self)

        frame2 = Frame(frame0)
        frame2.pack(fill=X, expand=1)

        btn = Button(frame2, text="Close", command= lambda: inf.destroy())
        btn.pack(side=RIGHT)

        inf.mainloop()
    #----------------------------#


    def addElement(self, pkts: list, frameFilter="None"):
        """Takes a pkt in dictionary format and add to window elements to show"""
        cc = 0

        for pkt in pkts:

            if frameFilter == "None":
                # Setting the background colour
                if pkt['alarm'] == True:
                    self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])), tags=('red'))
                else:
                    self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])))
            elif (frameFilter == "Error"):
                if pkt['alarm'] == True:
                    self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])), tags=('red'))
                else:
                    continue
            elif str(pkt['frameID']) == frameFilter.split(" ")[1]:
                # Setting the background colour
                if pkt['alarm'] == True:
                    self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])), tags=('red'))
                else:
                    self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])))
            cc += 1
    def deleteAll(self):
        """Delete ALL elements inserted in the self.treeview"""
        elements_inserted = self.tree.get_children()
        for elem in elements_inserted:
            self.tree.delete(elem)

    def updateElenco(self, filter: str):
        """ Update the treeview when a FILTER is applied """
        self.deleteAll()
        self.addElement(self.list_of_packets, filter)

    def update(self, list_of_packets):
        """ Update self.list_of_packets variable and add the new elements to the view"""
        cc = len(self.list_of_packets)
        for pkt in list_of_packets:
            self.list_of_packets.append(pkt)
            if pkt['alarm'] == True:
                self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])), tags=('red'))
            else:
                self.tree.insert("", cc, text="PACKET #"+str(cc), values=( str(pkt['type']), str(pkt['subtype']),str(pkt['pi1']),str(pkt['pi2']),str(pkt['apid']),str(pkt['spid']),str(pkt['genTime']),str(pkt['acqTime']),str(pkt['frameID']),str(pkt['description'])))
            cc += 1


    # Configuring double-click event
    def tree_select_event(self, a):
        """ Defines the event when in the treeview an element is double clicked.
            The details of packet parameters are showed """
        position = int((self.tree.item(self.tree.selection()[0])['text']).split('#')[1])
        self.show_info(lista[position], position)

    def getFrames(self, list_of_packets):
        """ Returns the filtering options for filter combobox """
        frames = ["None"] # The first option avaiable is no filter
        for elem in list_of_packets:
            try:
                frame_name = "FRAME " + str(elem['frameID'])
                frames.index(frame_name)
            except ValueError:
                frames.append(frame_name)
        frames.append("Error")
        return frames

    def getUpdateFreq(self):
        return self.freqUpdate

    def setUpdateFreq(self, freq: int):
        """ Update the update frequency for reading packets from the database setted """
        self.freqUpdate = freq

    

    #####################################################################

    #------------------------------------------------#

#########################################################################
#########################################################################

######################### NON REAL TIME WINDOW ##########################
#########################################################################


class NONRealTimeWin():
    def __init__(self, parent, lista, user_logged:str, log_usr):

        #VARIABLES
        self.version = "0.0.2"
        self.lista = lista                   # list of dictionaries [every dictionary describes a frame] (IF NEW FRAMES ARE RECORDED THEY ARE ADDED TO THIS LIST)
        self.freqUpdate = 1                  # frequency update the Treeview
        self.sessionActive = True 

        #-------- MAIN WINDOW --------#
        self.win = Toplevel()
        self.win.title('NON-Real-Time Window - ' + "Version: " + self.version)
        self.win.resizable(0,0)
        self.win.geometry("1080x430")

        #SETTING THE WINDOW ICON
        self.win.tk.call('wm', 'iconphoto', self.win._w, PhotoImage(file= os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat.ico'))

        #-----------------------------#

        #----------- Quit Function -----------#
        def on_closing():
            if messagebox.askokcancel("Quit", "Do you want to quit?"):
                log_usr.unlog(user_logged)
                log_usr.close()
                self.sessionActive = False
                self.win.destroy()
                parent.destroy()
        #-------------------------------------# 

        #------ Menu ------#
        menu = Menu(self.win)
        _file = Menu(menu, tearoff=0)
        _file.add_command(label='TM File...')
        _file.add_command(label='Save capture...', command = self.print_on_file)
        _file.add_command(label='Options')
        _file.add_separator()
        _file.add_command(label='Terminate session',command=on_closing)
        menu.add_cascade(label='File', menu=_file)
        
        log = Menu(menu, tearoff=0)
        log.add_command(label='User Log Window')
        log.add_command(label='Packet Log Window')
        menu.add_cascade(label='Log', menu=log)

        user = Menu(menu, tearoff=0)
        user.add_command(label=user_logged)
        menu.add_cascade(label='User', menu=user)
        self.win.config(menu=menu)
        #------------------#

        #------------------- Frame for time selection -------------------#
        self.fr0 = Frame(self.win)
        self.fr0.pack(fill=X,expand=1)

        # Check Button
        self.chk_state = BooleanVar()
        self.chk_state.set(False) #set check state
        chk = Checkbutton(self.fr0, text='Filter', var=self.chk_state, command = self.checkFiltering)
        chk.pack(side=LEFT, padx= 8)

        # Frame for filtering fields
        self.fr1 = Frame(self.fr0)
        self.fr1.pack(side=LEFT)

        #------------ Frame for infos ------------#
        info_Frame = Frame(self.fr0)
        info_Frame.pack(side=LEFT)
        lbl = Label(info_Frame, text="Total number of packets: "+str(len(self.lista)))
        lbl1 = Label(info_Frame, text="Time: " + datetime.datetime.now().strftime("%d/%m/%y - %H:%M:%S"))
        lbl.pack()
        lbl1.pack()
        #-----------------------------------------#

        # Cubesat Logo
        image = PhotoImage(file = os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat_logo.png')
        imageLabel = Label(self.fr0, image = image)
        imageLabel.image = image
        imageLabel.pack(side=RIGHT, padx= 10)

        #----------------------------------------------------------------#

        #----------------- Frame for FRAME visualization -----------------#
        fr2 = Frame(self.win)
        fr2.pack(fill = BOTH, expand = 1)
        src = Scrollbar(fr2, orient = VERTICAL)

        # Treeview set
        self.tree = ttk.Treeview(fr2, yscrollcommand = src.set)
        self.tree.pack(side = LEFT, fill=BOTH)
        self.tree["columns"]=("vc", "scid", "mccount", "vccount", "crc", "info")
        self.tree.column("#0",width=100,minwidth=50,stretch = NO)
        self.tree.column("vc",width=200,minwidth=50,stretch = NO)
        self.tree.column("scid",width=200,minwidth=50,stretch = NO)
        self.tree.column("mccount",width=100,minwidth=50,stretch = NO)
        self.tree.column("vccount",width=100,minwidth=50,stretch = NO)
        self.tree.column("crc",width=90,minwidth=50,stretch = NO)
        self.tree.column("info",width=275,minwidth=50,stretch = NO)
        self.tree.heading("#0",text="# Frame")
        self.tree.heading("vc", text="Virtual Channel")
        self.tree.heading("scid", text="Spacecraft ID")
        self.tree.heading("mccount", text="MC Count")
        self.tree.heading("vccount", text="VC Count")
        self.tree.heading("crc", text="CRC")
        self.tree.heading("info", text="Info")
        #------------------------------------------------#

        style = ttk.Style()
        def fixed_map(option):
            return [elm for elm in style.map("Treeview", query_opt=option)
                if elm[:2] != ("!disabled", "!selected")]

        style.map("Treeview", foreground=fixed_map("foreground"), background=fixed_map("background"))

        self.tree.tag_configure('red', background='#FF0000')

        #SCROLLBAR CONFIGURATION
        src.pack(side=RIGHT, fill = Y)
        src.config(command = self.tree.yview)

        self.addElement(self.lista)

        # Setting close event
        self.win.protocol("WM_DELETE_WINDOW", on_closing)

        #self.win.mainloop()
    
    def print_on_file(self):
        """ Print the info aof all frames actually showed in the Treeview on a txt file """
        path = filedialog.askopenfilename()
        file = open(path, "w+")

        counter = 0
        for packet in self.lista:
            file.write("FRAME #"+str(counter)+ " "+(str(packet)+"\n").replace("{", "").replace("}", "").replace(", ", " "))
            counter += 1

        file.close()

        messagebox.showinfo("Info", 'Operation completed!')


    def addElement(self, lista: list):
        """ Add the frame to show in treeview """
        cc= 0
        for elem in lista:
            if elem['crc'] == True:
                self.tree.insert("", cc, text="FRAME #"+str(cc), values=( str(elem['vc']), str(elem['spID']),str(elem['mcCount']),str(elem['vcCount']),str(elem['crc']),str(elem['info'])), tags='red')
            else:
                self.tree.insert("", cc, text="FRAME #"+str(cc), values=( str(elem['vc']), str(elem['spID']),str(elem['mcCount']),str(elem['vcCount']),str(elem['crc']),str(elem['info'])))
            cc += 1

    def checkFiltering(self):
        """ Command assigned to the checkbutton. Il this on is seleceted this function shows the 
            filtering fileds """
        
        if self.chk_state.get() == True:
            # If the filter checkbutton is True -> show filtering fields

            # Start Time
            startTime = Label(self.fr1,text = "Start Time:", font = ("ComicSans", 10))
            startTime.pack(side=LEFT,padx = 5)

            cal = DateEntry(self.fr1, width=12, background='darkblue',foreground='white', borderwidth=2, year=2020)
            cal.pack(side=LEFT, padx = 5)

            hours = list(range(0, 25))
            minutes = list(range(0,59))

            combo1 = ttk.Combobox(self.fr1, width = 5)
            combo1['values']= hours
            combo1.current(1)
            combo1.pack(side=LEFT)

            combo2 = ttk.Combobox(self.fr1, width = 5)
            combo2['values']= minutes
            combo2.current(1)
            combo2.pack(side=LEFT, padx = 5)

            # End Time
            endTime = Label(self.fr1,text = "End Time:", font = ("ComicSans", 10))
            endTime.pack(side=LEFT)

            cal2 = DateEntry(self.fr1, width=12, background='darkblue',foreground='white', borderwidth=2, year=2020)
            cal2.pack(side=LEFT, padx = 5)

            combo3 = ttk.Combobox(self.fr1, width = 5)
            combo3['values']= hours
            combo3.current(1)
            combo3.pack(side=LEFT)

            combo3 = ttk.Combobox(self.fr1, width = 5)
            combo3['values']= minutes
            combo3.current(1)
            combo3.pack(side=LEFT, padx = 5)

            # Button
            bbtn = Button(self.fr1, text = "Ok")
            bbtn.pack(padx = 10, side = LEFT)
        else:
            # If the filter checkbutton is False -> destroy filtering fields
            list_ = self.fr1.pack_slaves()
            for l in list_:
                l.destroy()
    
    def update(self, list_of_frames):
        """ Update self.lista variable and add the new elements to the view"""
        cc = len(self.lista)
        for elem in self.lista:
            self.lista.append(elem)
            if elem['crc'] == True:
                self.tree.insert("", cc, text="FRAME #"+str(cc), values=( str(elem['vc']), str(elem['spID']),str(elem['mcCount']),str(elem['vcCount']),str(elem['crc']),str(elem['info'])), tags='red')
            else:
                self.tree.insert("", cc, text="FRAME #"+str(cc), values=( str(elem['vc']), str(elem['spID']),str(elem['mcCount']),str(elem['vcCount']),str(elem['crc']),str(elem['info'])))
            cc += 1
        

        


#########################################################################
#########################################################################

params = [{'name': 'param1', 'value': 3.51, 'state': 'OOL'}, {'name':'param2', 'value': 10.43, 'state': 'TOLERANCE'}, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': .23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.43, 'state': 'ALARM' }, {'name': "param3", 'value': 12.23, 'state': 'ALARM' }, {'name': "param3", 'value': 2.3, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 0.23, 'state': 'ALARM' }, {'name': "param3", 'value': 6.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 4.23, 'state': 'ALARM' }, {'name': "param3", 'value': 5.43, 'state': 'ALARM' }, {'name': "param3", 'value': 0.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }]
lista = [params,params]

a = {'type': 1, 'subtype': 2, 'pi1': 3, 'pi2': 3, 'apid': 2233, 'spid': 34, 'acqTime': 'Bo', 'genTime': 'Bo', 'frameID': 2, 'alarm': False, 'description': 'lalalalala', 'parameters': lista[0]}
b = {'type': 2, 'subtype': 4, 'pi1': 6, 'pi2': 7, 'apid': 133, 'spid': 35, 'acqTime': 'Bo', 'genTime': 'Bo', 'frameID': 1, 'alarm': True, 'description': 'lalasdgwgalala', 'parameters': lista[0]}
list_of_packets = [a, b]
f=[{'vc':2, "spID":3, "mcCount":33, "vcCount": 22, "crc":True, "info":"Bo"}, {'vc':2, "spID":3, "mcCount":34, "vcCount": 23, "crc":False, "info":"Bo1"}]
# a=Tk()
# a.withdraw()
# x= RealTimeWindow(a, list_of_packets,lista,"Andrea Di Mauro")
# a.mainloop()
#y = NONRealTimeWin(f, "Andrea Di Mauro")