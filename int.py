import struct
from tkinter import *
from tkinter import ttk

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
        print(data[i])
        pack = pack << 8
        pack = pack | data[i]
    
    finalData = (pack & _filter) >> finalOffset
    return finalData 

#print(bin_to_float(16))

pr = [{'name': "lollo", 'value':3, 'state':{'alarm':0,'tolerance':0, 'ok' : 1}},{'name': "lollo", 'value':3, 'state':{'alarm':0,'tolerance':1, 'ok' : 0}}, {'name': "lollo1", 'value':4, 'state':{'alarm':1,'tolerance':0, 'ok' : 0}}, {'name': "lollo2", 'value':4, 'state':{'alarm':0,'tolerance':0, 'zero':1,'ok' : 0}}]

def showInfo():

    packetName = Lb1.get(Lb1.curselection()[0])
    packetNumber = int(packetName.split('#')[1]) -1

    counter = 1
    checkStatus = ""
    lista = Packets[packetNumber].checkedParams

    inf = Tk()
    inf.title(packetName)
    inf.geometry("615x300")
    inf.resizable(0,0)

    def destroy():
        inf.destroy()

    ##################### - FRAME FOR PARAMETERS VISUALIZATION AND SCROLL - #####################

    fr = Frame(inf)
    fr.pack(fill = X)
    src = Scrollbar(fr, orient = VERTICAL)

    ### - CODE TO ADD TO FIX PYTHON 3.7 COLOUR BUG - ###

    def fixed_map(option):
    # Returns the style map for 'option' with any styles starting with
    # ("!disabled", "!selected", ...) filtered out

    # style.map() returns an empty list for missing options, so this should
    # be future-safe
        return [elm for elm in style.map("Treeview", query_opt=option)
            if elm[:2] != ("!disabled", "!selected")]

    style = ttk.Style()

    style.map("Treeview",
          foreground=fixed_map("foreground"),
          background=fixed_map("background"))
    
    #####################################################

    #TREEVIEW OBJECT CONFIGURATION
    tree = ttk.Treeview(fr, yscrollcommand = src.set)
    tree.pack(side = LEFT)
    tree["columns"]=("value","state")
    tree.column("#0",width=200,minwidth=200,stretch = NO)
    tree.column("value",width=200,minwidth=200,stretch = NO)
    tree.column("state",width=200,minwidth=200,stretch = NO)
    tree.heading("#0",text="Name")
    tree.heading("value", text="Value")
    tree.heading("state", text="Check")

    #TAGS TO CONFIGURE CHECK STATUS COLOUR (ok status is not colored)
    tree.tag_configure('red', background='#FF0000')   #ALARM
    tree.tag_configure('yellow', background='yellow') #TOLERANCE
    tree.tag_configure('lb', background='#ADD8E6')    #ZERO
    

    for element in lista:
        if element['states']['ok'] == 1:
            checkStatus = "OK"
            tree.insert("", counter, text=element['name'], values=(str(element['value']),checkStatus))
        elif element['states']['alarm'] == 1:
            checkStatus = "ALARM"
            tree.insert("", counter, text=element['name'], values=(str(element['value']),checkStatus), tags=('red'))
        elif element['states']['tolerance'] == 1:
            checkStatus = "TOLERANCE"
            tree.insert("", counter, text=element['name'], values=(str(element['value']),checkStatus), tags=('yellow'))
        elif element['states']['zero'] == 1:
            checkStatus = "ZERO"
            tree.insert("", counter+1, text=element['name'], values=(str(element['value']),checkStatus), tags=('lb'))
        
        counter +=1
    
    #SCROLLBAR CONFIGURATION
    src.pack(side=RIGHT, fill = Y)
    src.config(command = tree.yview)

    btn_1 = Button(inf, text="Show as Text", width = 2, command = showTextPacket)
    btn_1.pack(side = RIGHT, padx=5)

    btn_2 = Button(inf, text="Close", width = 2, command = destroy)
    btn_2.pack(side = LEFT, padx=5)

    inf.mainloop()
showInfo(pr)

