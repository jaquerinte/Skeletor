import gi
gi.require_version('Gtk', '3.0')
gi.require_version('PangoCairo', '1.0')
from gi.repository import Gtk, Gdk, GdkPixbuf, cairo, Pango, PangoCairo

(TARGET_ENTRY_TEXT, TARGET_ENTRY_PIXBUF) = range(2)
(COLUMN_TEXT, COLUMN_PIXBUF) = range(2)

DRAG_ACTION = Gdk.DragAction.COPY

module = 0
wire = 0
drawings = []

class DragDropWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Drag and Drop Demo")
        
        #hbox = Gtk.Box(spacing=12) 
        #self.add(hbox)
        
        #vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        grid = Gtk.Grid()
        self.add(grid)
        self.buttonArea = ButtonArea()
        self.drawing_area = DrawingArea()

        self.drawing_area.connect('draw', self.drawing_area.do_draw_cb)
        #vbox.pack_start(self.buttonArea,True,False,0)
        #vbox.pack_start(self.drawing_area, True, True, 0)
        grid.attach(self.buttonArea,1,1,1,1)
        self.buttonArea.set_hexpand(True)
        grid.insert_row(2)
        grid.attach(self.drawing_area,1,2,5,5)
        self.drawing_area.set_hexpand(True)
        self.drawing_area.set_vexpand(True)



class DrawingArea(Gtk.DrawingArea):

    def __init__(self):
        Gtk.DrawingArea.__init__(self)
        self.add_events(Gdk.EventMask.BUTTON_PRESS_MASK)
        self.connect("button-press-event", self.button_press_event)

    def button_press_event(self, widget, event):
        if event.button == 1:
            optwin.show_all()

    def do_draw_cb(self, widget, cr):
        
        #cr.set_source_rgba(0,0,0,0.5)
        #cr.rectangle(50,50,100,100)
        #cr.rectangle(200,50,100,100)
        #cr.fill()
        #cr.set_source_rgba(0,0,0,1)
        #cr.rectangle(150,100,50,1)
        #cr.fill()
        return False

class ButtonArea(Gtk.ButtonBox):

    def __init__(self):
        Gtk.ButtonBox.__init__(self)
        self.set_layout(Gtk.ButtonBoxStyle(5))
        self.wireButton = Gtk.ToggleButton("wire")
        self.moduleButton = Gtk.ToggleButton("module")

        self.wireButton.connect("toggled",self.on_toggled_wire)
        self.moduleButton.connect("toggled",self.on_toggled_module)

        self.add(self.wireButton)
        self.add(self.moduleButton)


    def on_toggled_module(self, widget, data = None):
        if(self.moduleButton.get_active()):
            module = 1
            if self.wireButton.get_active():
                self.wireButton.set_active(False)
                wire = 0
        else: module = 0
    def on_toggled_wire(self, widget, data = None):
        if(self.wireButton.get_active()):
            wire = 1
            if self.moduleButton.get_active():
                self.moduleButton.set_active(False)
                module = 0
        else: wire = 0
            
class OptionWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Drag and Drop Demo")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        self.inputs = Gtk.Entry()
        self.outputs = Gtk.Entry()
        inputsLabel = Gtk.Label("Number of Inputs")
        outputsLabel = Gtk.Label("Number of Outputs")
        ibox = Gtk.Box(spacing=12) 
        obox = Gtk.Box(spacing=12)
        ibox.pack_start(inputsLabel,True,True,0)
        ibox.pack_start(self.inputs,True,True,0)

        obox.pack_start(outputsLabel,True,True,0)
        obox.pack_start(self.outputs,True,True,0)
        
        vbox.pack_start(ibox, True, True, 0)
        vbox.pack_start(obox, True, True, 0)

        bBox = Gtk.ButtonBox()

        self.acceptButton = Gtk.Button("Accept")
        self.cancelButton = Gtk.Button("Cancel")
        bBox.pack_start(self.cancelButton,True,True,0)
        bBox.pack_start(self.acceptButton,True,True,0)
        vbox.pack_start(bBox,True,True,0)

        self.acceptButton.connect("button-press-event", self.acceptbutton_press_event)
        self.cancelButton.connect("button-press-event", self.cancelbutton_press_event)

    def acceptbutton_press_event(self, widget, event):
        if event.button == 1:
            optwin.hide()
        #drawings.append([])

    def cancelbutton_press_event(self, widget, event):
        if event.button == 1:
            optwin.hide()

optwin = OptionWindow()
win = DragDropWindow()
win.connect("destroy", Gtk.main_quit)
win.maximize()
win.show_all()
Gtk.main()
