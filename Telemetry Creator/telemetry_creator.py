from tkinter import *
import gi
import datetime
import os
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

statusbar = Gtk.Label()
statusbar.set_text('Stopped')
already_running = False
text_buffer = Gtk.TextBuffer()
main_file = "/home/andrea/Scrivania/Prove/prova.bin"
main_list = [] #list of dictionaries of structure {'field', 'value', 'size'}
elements_to_update = [] #list of dictionaries of structure {'field', 'value'} 
#Remeber to check that the value is in the range of the size

def write_on_file(_file, vals):

    list_to_write = [] #list of binary values

    for conf in vals:
        for val in conf:
            binary = bin(int(val['value'])).replace('0b', "")
            _len = len(binary)

            if _len < val['size']:
                binary = '0'*(_len-val['size']) + binary

            totalString = totalString + binary
        
    for counter in range(0,len(totalString)):
        list_to_write.append(totalString[counter:counter+8], base = 2)
        counter += 8

        if counter + 16 > len(totalString):
            list_to_write.append(totalString[counter+8:], base = 2)
            break

    for binary in list_to_write:
        _file.write(binary)

def run(button):
    global main_list
    global main_file
    global elements_to_update

    if already_running:
        return

    #Checking if the value is in the range
    for conf in main_list:
        for _dict in conf:
            if _dict['value'] >= 2**(int(_dict['size'])):
                text = "Error: Field " + str(_dict['field']) + " with value" + str(_dict['value'] + " is out of range of his size\n")
                text_buffer.insert(text_buffer.get_end_iter(),text)
    
    #Choosing number of packets
    win = RunWindow()
    win.show_all()

def read_saved():
    """Read the configuration already saved. Returns a list of dictionaries organized as
    {'description': , 'length'} """

    lista = []

    # Reading files
    PATH = os.path.dirname(os.path.realpath(sys.argv[0])) + "/Saved/"
    for root, dirs, files in os.walk(PATH):
        for name in files:
           _file = os.path.join(root, name)
           file = open(_file, 'r')
           data = file.readline()
           data = data.split('\t')
           lista.append({'description': data[0] , 'length': data[1]})
           file.close()

    lista.reverse()
    print(lista)
    return lista

class RunWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self)
        self.set_default_size(200,50)
        self.set_title("How many packets?")
        self.set_position(Gtk.WindowPosition.MOUSE)
        self.set_border_width(10)
        self.connect("destroy", self.close)

        g = Gtk.Grid()
        self.entry = Gtk.Entry()
        btn = Gtk.Button(label = "Ok")
        btn.connect("clicked", self.ok)
        g.attach(self.entry, 0,0,1,1)
        g.attach_next_to(btn, self.entry, Gtk.PositionType.RIGHT, 1,1)

        self.add(g)

    def ok(self,button):
        self.packets = int(self.entry.get_text())
        counter = self.packets
        #Writing
        _file = open(main_file, "wb")
        while True:
            if counter > 0:
                write_on_file(_file, main_list)
                pass
            else:
                break
            counter -= 1
        _file.close()
        text_buffer.insert(text_buffer.get_end_iter(),str(self.packets)+" packets correctly written!\n")
        self.close()

class UpdateWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self)
        self.set_default_size(400,200)
        self.set_title("Elements to update")
        self.set_position(Gtk.WindowPosition.MOUSE)
        self.set_border_width(10)
        self.connect("destroy", self.close)

        self.columns = ['Name','Value']
        self.listsrc = Gtk.ListStore(str, int)

        for val in elements_to_update:
            self.listsrc.append([val['field'], int(val['value'])]) 

        self.g = Gtk.Grid()

        self.tree = Gtk.TreeView(model=self.listsrc)
        for i, column in enumerate(self.columns):
            cell = Gtk.CellRendererText()
            col = Gtk.TreeViewColumn(column, cell, text=i)
            self.tree.append_column(col)
        self.tree.columns_autosize()
        self.tree.set_size_request(380, 180)

        self.button_0 = Gtk.Button(label = "Delete")
        self.button_0.connect("clicked", self.delete)
        self.button_1 = Gtk.Button(label = "Ok")
        self.button_1.connect("clicked", self.ok)
        self.button_2 = Gtk.Button(label = "Add")
        self.button_2.connect("clicked", self.add_fun)
        self.g.set_column_spacing(30)
        self.g.set_row_spacing(10)
        self.g.attach(self.tree, 0,0,3,1)
        self.g.attach(self.button_0, 0,1,1,1)
        self.g.attach_next_to(self.button_2, self.button_0, Gtk.PositionType.RIGHT, 1,1)
        self.g.attach_next_to(self.button_1, self.button_2, Gtk.PositionType.RIGHT, 1,1)

        self.add(self.g)

    class AddWindow(Gtk.Window):
        def __init__(self, tree):
            Gtk.Window.__init__(self)
            self.tree = tree #Treeview of the main window
            self.list = list #List of values inserted in the ListBox used for TreeView
            self.set_default_size(100,100)
            self.set_title("Add")
            self.set_position(Gtk.WindowPosition.MOUSE)
            self.set_border_width(10)
            self.connect("destroy", self.close)

            self.box1 = Gtk.Box()
            
            g1 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
            g1.set_row_spacing(5)
            lb = Gtk.Label()
            lb.set_text('Field')
            self.entry1 = Gtk.Entry()
            g1.add(lb)
            g1.add(self.entry1)

            g2 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
            g2.set_row_spacing(5)
            lb1 = Gtk.Label()
            lb1.set_text('Value')
            self.entry2 = Gtk.Entry()
            btn0 = Gtk.Button(label="Ok")
            btn0.connect("clicked", self.add_or_edit_element)
            g2.add(lb1)
            g2.add(self.entry2)
            g2.add(btn0)

            self.box1.pack_start(g1,True, True, 2)
            self.box1.pack_start(g2,True, True, 2)

            self.add(self.box1)

        def add_or_edit_element(self,btn0):
            self.tree.get_model().append([str(self.entry1.get_text()), int(self.entry2.get_text())])
            self.close()

    def ok(self,button):
        i=0
        global elements_to_update
        elements_to_update.clear()
        while i>=0:
            try:
                elements_to_update.append({'field': self.tree.get_model()[i][0], 'value': self.tree.get_model()[i][1]})
                i += 1
            except IndexError:
                break
        self.close()

    def delete(self,button):
        (model,i) = self.tree.get_selection().get_selected()
        field = str(model[i][0])
        for l,val in enumerate(elements_to_update):
            if val['field'] == field:
                del elements_to_update[l]
                break
        model.remove(i)
    
    def add_fun(self,button):
        win = self.AddWindow(self.tree)
        win.show_all()

class SavedWindow(Gtk.Window):
    def __init__(self, tree_parent):
        self.tree_parent = tree_parent
        Gtk.Window.__init__(self)
        self.set_default_size(400,300)
        self.set_title("Import configuration")
        self.set_position(Gtk.WindowPosition.MOUSE)
        self.set_border_width(10)
        self.connect("destroy", self.close)

        self.columns = ['Name','Size']
        self.listsrc = Gtk.ListStore(str, int) 

        self.g = Gtk.Grid()

        self.tree = Gtk.TreeView(model=self.listsrc)
        for i, column in enumerate(self.columns):
            cell = Gtk.CellRendererText()
            col = Gtk.TreeViewColumn(column, cell, text=i)
            self.tree.append_column(col)
        self.tree.columns_autosize()
        self.tree.set_size_request(380, 180)

        self.button_0 = Gtk.Button(label = "Delete")
        self.button_1 = Gtk.Button(label = "Import")
        self.button_1.connect("clicked", self.agg)
        self.g.set_column_spacing(30)
        self.g.attach(self.tree, 0,0,2,1)
        self.g.attach(self.button_0, 0,1,1,1)
        self.g.attach_next_to(self.button_1, self.button_0, Gtk.PositionType.RIGHT, 1,1)

        self.add(self.g)

        #Reading saved files...
        saved_files = read_saved()

        for _file in saved_files:
            self.listsrc.append([_file['description'], int(_file['length'])])

    def agg(self, button):
        configuration = []
        PATH = os.path.dirname(os.path.realpath(sys.argv[0])) + "/Saved/"

        (model, i) = self.tree.get_selection().get_selected()
        self.tree_parent.get_model().append([str(model[i][0]),int(model[i][1]), main_file ])

        file_path = PATH + str(model[i][0])
        _file = open(file_path, "r")
        _file.readline()

        for line in _file.readlines():
            [field, value, size] = line.split('\t')
            configuration.append({'field': field, 'value': int(value), 'size': int(size)})
        
        main_list.append(configuration)

        _file.close()
        self.close()

    def delete(self,button):
        PATH = os.path.dirname(os.path.realpath(sys.argv[0])) + "/Saved/"
        (model,i) = self.tree.get_selection().get_selected()
        os.remove(PATH+str(model[i][0]))
        model.remove(i)

class NewWindow(Gtk.Window):
    def __init__(self, listStore_parent = None, tree_parent = None, position = None):
        self.lisStore_parent = listStore_parent
        self.tree_parent = tree_parent
        self.position = position

        Gtk.Window.__init__(self)
        self.set_default_size(400,300)
        if self.position == None:
            self.set_title("New Configuration")
        else:
            self.set_title("Edit Configuration")
        self.set_position(Gtk.WindowPosition.MOUSE)
        self.set_border_width(10)
        self.connect("destroy", self.close)

        self.columns = ['Field', 'Value', 'Size']
        self.listsrc = Gtk.ListStore(str, int, int)
        self.total_size = 0

        self.g = Gtk.Grid()

        self.tree = Gtk.TreeView(model=self.listsrc)
        for i, column in enumerate(self.columns):
            cell = Gtk.CellRendererText()
            col = Gtk.TreeViewColumn(column, cell, text=i)
            self.tree.append_column(col)
        self.tree.columns_autosize()
        self.tree.set_size_request(380, 180)

        if self.position is not None:
            model = self.tree.get_model()

            for _dict in main_list[position]:
                model.append([_dict['field'], _dict['value'], _dict['size']])

        self.box1 = Gtk.Grid()
        self.box1.set_column_spacing(30)
        self.entry = Gtk.Entry()
        self.entry.set_size_request(5,2)
        self.entry.set_text('Configuration Name')
        self.btn0 = Gtk.Button(label = 'Done')
        self.btn0.connect("clicked", self.done)
        self.box1.attach(self.entry, 0,0,1,1)
        self.box1.attach_next_to(self.btn0, self.entry, Gtk.PositionType.RIGHT, 1,1)
        self.btn0.set_size_request(2,2)

        self.g1 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
        self.g1.set_row_spacing(2)
        btn1 = Gtk.Button(label='Add')
        btn1.connect("clicked", self.add_element)
        btn2 = Gtk.Button(label='Edit')
        btn2.connect("clicked", self.edit_element)
        btn3 = Gtk.Button(label='Delete')
        btn3.connect("clicked", self.delete_element)
        self.g1.add(btn1)
        self.g1.add(btn2)
        self.g1.add(btn3)

        self.g.attach(self.tree, 0,0,2,1)
        self.g.attach(self.box1,0,1,1,1)
        self.g.attach_next_to(self.g1, self.box1,Gtk.PositionType.RIGHT, 1,1)
        self.g.set_row_spacing(10)
        self.g.set_column_spacing(30)
        self.add(self.g)

    class AddWindow(Gtk.Window):
        def __init__(self, tree, model, i):
            Gtk.Window.__init__(self)
            self.model = model
            self.i = i
            self.tree = tree #Treeview of the main window
            self.list = list #List of values inserted in the ListBox used for TreeView
            self.set_default_size(100,100)
            self.set_title("Add")
            self.set_position(Gtk.WindowPosition.MOUSE)
            self.set_border_width(10)
            self.connect("destroy", self.close)

            self.box1 = Gtk.Box()
            
            g1 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
            g1.set_row_spacing(5)
            lb = Gtk.Label()
            lb.set_text('Field')
            self.entry1 = Gtk.Entry()
            g1.add(lb)
            g1.add(self.entry1)

            g2 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
            g2.set_row_spacing(5)
            lb1 = Gtk.Label()
            lb1.set_text('Value')
            self.entry2 = Gtk.Entry()
            btn0 = Gtk.Button(label="Ok")
            btn0.connect("clicked", self.add_or_edit_element)
            g2.add(lb1)
            g2.add(self.entry2)
            g2.add(btn0)

            g3 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
            g3.set_row_spacing(5)
            lb2 = Gtk.Label()
            lb2.set_text('Size')
            self.entry3 = Gtk.Entry()
            g3.add(lb2)
            g3.add(self.entry3)

            self.box1.pack_start(g1,True, True, 2)
            self.box1.pack_start(g2,True, True, 2)
            self.box1.pack_start(g3,True, True, 2)

            self.add(self.box1)

        def add_or_edit_element(self,btn0):
            if self.model is not None:
                self.model.set_value(self.i,0,str(self.entry1.get_text()))
                self.model.set_value(self.i,1,int(self.entry2.get_text()))
                self.model.set_value(self.i,2,int(self.entry3.get_text()))
                self.close()
                return
            self.tree.get_model().append([str(self.entry1.get_text()), int(self.entry2.get_text()), int(self.entry3.get_text())])
            self.close()


    def add_element(self, btn1):
        win = self.AddWindow(self.tree, None, None)
        win.show_all()

    def edit_element(self, button):
        (model, i) = self.tree.get_selection().get_selected()
        win = self.AddWindow(self.tree, model, i)
        win.show_all()

    def delete_element(self, button):
        (model, i) = self.tree.get_selection().get_selected()
        model.remove(i)

    def done(self, button):
        i=0
        configuration = []
        global main_file

        if self.position is not None:
            #Calculating total size
            while i>=0:
                try:
                    self.total_size = self.tree.get_model()[i][2] + self.total_size
                    configuration.append({'field': self.tree.get_model()[i][0], 'value': self.tree.get_model()[i][1], 'size': self.tree.get_model()[i][2]})
                    i += 1
                except IndexError:
                    break

            #Updating value in main list
            main_list[self.position] = configuration
            self.close()
            return

        #Getting configuration name
        name = self.entry.get_text()

        #Calculating total size
        while i>=0:
            try:
                self.total_size = self.tree.get_model()[i][2] + self.total_size
                configuration.append({'field': self.tree.get_model()[i][0], 'value': self.tree.get_model()[i][1], 'size': self.tree.get_model()[i][2]})
                i += 1
            except IndexError:
                break
        
        #Saving data
        main_list.append(configuration)

        #Adding value to main treeview
        self.tree_parent.get_model().append([name, self.total_size, main_file])

        self.close()

class MyWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self)
        self.set_default_size(600,500)
        self.set_title('Telemetry Emulator')
        self.set_position(Gtk.WindowPosition.CENTER_ALWAYS)
        self.set_border_width(10)
        self.set_icon_from_file('/home/andrea/SynologyDrive/04-Control_Centre/05-Extractor_2.0/Images/cubesat.ico')
        self.connect("destroy", Gtk.main_quit)

        columns = ['Description', 'Length', 'File']

        #listbox = [['CCSDS SOURCE PACKET', '6035', '/home/andrea/...'], ['CCSDS FRAME', '1024', '/home/andrea/']]
        self.listsrc = Gtk.ListStore(str, int, str)
        # for i in listbox:
        #     self.listsrc.append(i)

        # Main listbox
        # self.listmain = Gtk.ListBox()
        # self.listmain.set_selection_mode(Gtk.SelectionMode.NONE)
        
    

        #----------- Treeview -----------#
        self.tree = Gtk.TreeView(model=self.listsrc)
        for i, column in enumerate(columns):
            cell = Gtk.CellRendererText()
            col = Gtk.TreeViewColumn(column, cell, text=i)
            self.tree.append_column(col)
        self.tree.columns_autosize()
        self.tree.set_size_request(580, 280)

        #self.selection.connect("changed", self.select)
        #-------------------------------------#

        # row2 = Gtk.ListBoxRow()
        # box2 = Gtk.Box()

        #----Buttons on the left----#
        grid = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
        grid.set_row_spacing(5)
        btn1 = Gtk.Button(label='Folder')
        btn1.connect("clicked", self.on_folder_clicked)
        btn2 = Gtk.Button(label='Edit')
        btn2.connect("clicked", self.edit_element)
        btn3 = Gtk.Button(label='Run')
        btn3.connect("clicked", run)
        grid.add(btn1)
        grid.add(btn2)
        grid.add(btn3)
        #box2.pack_start(grid, True, True,0)
        #----------------------------#

        #------ Event, State, PID ------#
        box3 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
        box3.set_row_spacing(12)
        text = Gtk.TextView(buffer = text_buffer)
        text.set_size_request(400,100)
        box3.add(text)
        box4 = Gtk.Box()
        bfr = Gtk.TextBuffer()
        # tag = bfr.create_tag("red", background="red")
        # bfr.apply_tag(tag, bfr.get_start_iter(), bfr.get_end_iter())
        image = Gtk.Image()
        image.set_from_file("/home/andrea/SynologyDrive/04-Control_Centre/05-Extractor_2.0/Telemetry Creator/cubesat_logo.png")
        image.set_pixel_size(10)
        box4.pack_start(statusbar, True, True, 1)
        box4.pack_start(image,True,True,1)
        label = Gtk.Label()
        label.set_text("PID\n" + str(os.getpid()))
        label.set_margin_top(5)
        box4.pack_start(label, True, True, 1)
        box3.add(box4)
        #box2.pack_start(box3, True, True, 1)
        #-------------------------------#

        #----Buttons on the right---#
        grid1 = Gtk.Grid(orientation = Gtk.Orientation.VERTICAL)
        grid1.set_row_spacing(5)
        btn6 = Gtk.Button(label='New')
        btn6.connect("clicked", self.new_conf)
        btn7 = Gtk.Button(label='Import')
        btn7.connect("clicked", self.to_import)
        btn8 = Gtk.Button(label='Delete')
        btn8.connect("clicked", self.delete_conf)
        btn9 = Gtk.Button(label='Save')
        btn9.connect("clicked", self.save_conf)
        grid1.add(btn6)
        grid1.add(btn7)
        grid1.add(btn8)
        grid1.add(btn9)
        #box2.pack_start(grid1, True, True,0)
        #----------------------------#

        self.grid_main = Gtk.Grid()
        self.grid_main.set_row_spacing(20)
        self.grid_main.attach(self.tree, 0,0,3,3)
        self.grid_main.attach(grid, 0,3,1,1)
        self.grid_main.attach_next_to(box3, grid, Gtk.PositionType.RIGHT,1,1)
        self.grid_main.attach_next_to(grid1, box3, Gtk.PositionType.RIGHT,1,1)

        # row2.add(box2)
        # self.listmain.add(row2)
        self.add(self.grid_main)

    def new_conf(self,button):
        win = NewWindow(self.tree.get_model(), self.tree)
        win.show_all()

    def save_conf(self,button):
        l=0
        PATH = os.path.dirname(os.path.realpath(sys.argv[0])) + "/Saved/"

        (model, i) = self.tree.get_selection().get_selected()
        selection = self.tree.get_model()[i]
        name = selection[0]
        size = selection[1]

        _file = open(PATH+name, "w")
        _file.write(name+'\t'+str(size)+"\n")

        while l>=0:
            try:
                if model[l][0] == name:
                    break
                l += 1
            except IndexError:
                break

        _list = main_list[l]
        for _dict in _list:
            _file.write(_dict['field']+'\t'+str(_dict['value'])+'\t'+str(_dict['size'])+"\n")

        _file.close()

    def delete_conf(self, button):
        l=0
        (model, i) = self.tree.get_selection().get_selected()
        selection = self.tree.get_model()[i]
        name = selection[0]
        self.tree.get_model().remove(i)

        while l>=0:
            try:
                if model[l][0] == name:
                    break
                l += 1
            except IndexError:
                break
        del main_list[l]

    def edit_element(self,button):
        l=0
        (model, i) = self.tree.get_selection().get_selected()
        selection = self.tree.get_model()[i]
        name = selection[0]

        while l>=0:
            try:
                if model[l][0] == name:
                    break
                l += 1
            except IndexError:
                break
        win = NewWindow(None,None,l)
        win.show_all()

    def to_import(self,button):
        win = SavedWindow(self.tree)
        win.show_all()

    def on_folder_clicked(self, button):
        global main_file
        dialog = Gtk.FileChooserDialog(
            "Please choose a folder",
            self,
            Gtk.FileChooserAction.SELECT_FOLDER,
            (Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL, "Select", Gtk.ResponseType.OK),
        )
        dialog.set_default_size(800, 400)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            main_file = dialog.get_filename()
        dialog.destroy()

    def update(self,button):
        win = UpdateWindow()
        win.show_all()


        

# win1 = NewWindow()
# win1.connect('destroy', win1.close)
# win1.show_all()
    

win = MyWindow()
win.show_all()
Gtk.main()