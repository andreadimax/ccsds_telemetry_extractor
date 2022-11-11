import tkinter
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import os
import threading
import sys
import time
import log
from GUI import *
import GUI


def main():

    threads = list()

    # Logging Check
    check = False
    credentials = {'username': userEntry.get(), 'password': passEntry.get()}
    string = credentials['username']+"\t"+credentials['password']
    file = open(os.path.dirname(os.path.realpath(sys.argv[0])) + '/Users/users.data', "r")

    for value in file:
        if (value == string) | (value == string +"\n"):
            check = True

    if check == False:
        messagebox.showwarning('Error', 'Incorrect username or password')
        return
    else:
        messagebox.showinfo('Log Info', 'Correctly Logged')
        login.destroy()

        # Creation of a new log object
        log_usr = log.LOG_User()
        log_usr.log(credentials['username'])

        #------------ Function that takes data from the database ------------#

        #a = [{'name': 'param1', 'value': 3.51, 'state': 'OOL'}, {'name':'param2', 'value': 10.43, 'state': 'TOLERANCE'}, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }]
        #show_info(a,1)

        params = [{'name': 'param1', 'value': 3.51, 'state': 'OOL'}, {'name':'param2', 'value': 10.43, 'state': 'TOLERANCE'}, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': .23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.43, 'state': 'ALARM' }, {'name': "param3", 'value': 12.23, 'state': 'ALARM' }, {'name': "param3", 'value': 2.3, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 0.23, 'state': 'ALARM' }, {'name': "param3", 'value': 6.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 4.23, 'state': 'ALARM' }, {'name': "param3", 'value': 5.43, 'state': 'ALARM' }, {'name': "param3", 'value': 0.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }, {'name': "param3", 'value': 1.23, 'state': 'ALARM' }]
        lista = [params,params]

        a = {'type': 1, 'subtype': 2, 'pi1': 3, 'pi2': 3, 'apid': 2233, 'spid': 34, 'acqTime': 'Bo', 'genTime': 'Bo', 'frameID': 2, 'alarm': False, 'description': 'lalalalala'} #'parameters': lista[0]
        b = {'type': 2, 'subtype': 4, 'pi1': 6, 'pi2': 7, 'apid': 133, 'spid': 35, 'acqTime': 'Bo', 'genTime': 'Bo', 'frameID': 1, 'alarm': True, 'description': 'lalasdgwgalala'} # 'parameters': lista[0]
        list_of_packets = [a, b]
        f=[{'vc':2, "spID":3, "mcCount":33, "vcCount": 22, "crc":True, "info":"Bo"}, {'vc':2, "spID":3, "mcCount":34, "vcCount": 23, "crc":False, "info":"Bo1"}]
        #--------------------------------------------------------------------#

        a=Tk()
        a.withdraw()
        w = GUI.RealTimeWindow(a, list_of_packets, lista, credentials['username'], log_usr)
        win = GUI.NONRealTimeWin(a, f, credentials['username'], log_usr)

        t1 = threading.Thread(target=RealTimeWinProcess, args=(w,))
        t2 = threading.Thread(target=NonRealTimeWinProcess, args=(win,))
        t3 = threading.Thread(target=EventWin)

        threads.append(t1)
        threads.append(t2)
        threads.append(t3)

        t1.start()
        t2.start()
        t3.start()

        for t in threads:
            t.join()

        a.mainloop()
        return

#---------------- Thread Functions ----------------#
def RealTimeWinProcess(w):
    """ Function for real time window thread """

    while False:  #w.sessionActive
            #updateFreq = w.getUpdateFreq()
            #update...
            time.sleep(GUI.updateFreq)
    return

def NonRealTimeWinProcess(win):
    """ Function for non-real time window thread """

    while False: #win.sessionActive:
            #updateFreq = win.freqUpdate
            #update...
            time.sleep(GUI.updateFreq)
    return
#--------------------------------------------------#

#------------------ LOGGING WINDOW ------------------#

# Window initializing
login = Tk()
login.title('C3 MCC - login')
login.resizable(0,0)
login.geometry("380x250")

login.tk.call('wm', 'iconphoto', login._w, PhotoImage(file= os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat.ico'))

frame0 = Frame(login)
frame0.pack(fill = BOTH, expand = 1)

frameImages = Frame(frame0)
frameImages.pack()

image = PhotoImage(file = os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/c3_transparent.png')
imageLabel = Label(frameImages, image = image)
image1 = PhotoImage(file = os.path.dirname(os.path.realpath(sys.argv[0])) + '/Images/cubesat_retina_1.png')
imageLabel1 = Label(frameImages, image = image1)
imageLabel1.pack(side=LEFT, pady = 20,padx=5)
imageLabel.pack(side=LEFT, pady = 20, padx= 10)

userFrame = Frame(frame0)
userFrame.pack()
passFrame = Frame(frame0)
passFrame.pack(pady=5)

userLabel = Label(userFrame, text="Username")
userLabel.pack(side=LEFT, padx= 5)
userEntry = Entry(userFrame)
userEntry.pack(side= LEFT)

passLabel = Label(passFrame, text="Password")
passLabel.pack(side=LEFT, padx= 5)
passEntry = Entry(passFrame, show='*')
passEntry.pack(side= LEFT)

btn = Button(frame0, text= "Login", command = main)
btn.pack(pady= 5)

login.mainloop()
#-----------------------------------------------------#