import gi
gi.require_version('Gtk', '3.0')
gi.require_version('PangoCairo', '1.0')
from gi.repository import Gtk, Gdk, cairo, Pango, PangoCairo
from gi.repository import GObject
import uuid
import glib

module = 0
wire = 0
move=0
topConnectionB=0
modules_selected=0
enable_movement=0
edit=0
multiple_selected=0
# modules --> objects of Class Module
modules = []
# wires --> objects of Class Wire
wires = []
# topConnections --> objects of Class TopConnection
topConnections = []
optX = 0
optY = 0
wiringA=0
wiringB=0
wiringW=0

class SchematicWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Schematic")
        
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
        self.add_events(Gdk.EventMask.BUTTON_PRESS_MASK | Gdk.EventMask.BUTTON_RELEASE_MASK | Gdk.EventMask.POINTER_MOTION_MASK)
        self.connect("button-press-event", self.button_press_event)
        self.connect("motion-notify-event", self.moving_cursor)
        self.connect("button-release-event", self.button_release_event)

    def button_release_event(self,widget,event):
        global modules
        global move
        global modules_selected
        global enable_movement
        global multiple_selected
        multiple_selected=0
        enable_movement=0
        if move == 1 and modules_selected==1:
            modules_selected=0
            for item in modules:
                if item.selected==1:
                    item.orgX=item.posXNow
                    item.orgY=item.posYNow
                item.selected=0
            self.queue_draw()
        elif move == 1 and modules_selected==0 and edit==0:
            for item in modules:
                #case0 --> abajo Iz, arriba De
                #case1 --> arriba Iz, abajo De
                #case2 --> abajo De, arriba Iz
                #case3 --> arriba De, abajo Iz
                if ((optX <= item.posXNow and event.x >= item.posXNow+item.width and optY >= item.posYNow+item.height and event.y <= item.posYNow) or
                   (optX <= item.posXNow and event.x >= item.posXNow+item.width and optY <= item.posYNow and event.y >= item.posYNow+item.height) or
                   (event.x <= item.posXNow and optX >= item.posXNow+item.width and optY >= item.posYNow+item.height and event.y <= item.posYNow) or
                   (event.x <= item.posXNow and optX >= item.posXNow+item.width and optY <= item.posYNow and event.y >= item.posYNow+item.height)):
                    multiple_selected = multiple_selected+1
                    item.selected=1
                    modules_selected=1

            self.queue_draw()


    def moving_cursor(self,widget,event):
        global modules
        global move
        global modules_selected
        global enable_movement
        if move == 1 and modules_selected==1 and enable_movement==1 and edit==0:
            for item in modules:
                if item.selected==1:
                    item.posXNow = item.orgX - (optX-event.x)
                    item.posYNow = item.orgY - (optY-event.y)
                    for w in wires:
                        if w.idA == item.id:
                            w.posXA=item.posXNow+item.width
                            w.posYA=item.posYNow+(item.height/2)
                        elif w.idB == item.id:
                            w.posXB=item.posXNow
                            w.posYB=item.posYNow+(item.height/2)
            self.queue_draw()

        if wire==1 and modules_selected == 1:
            for w in wires:
                if w.idB == 0:
                    w.posXB=event.x
                    w.posYB=event.y
                    break
            self.queue_draw()

    def button_press_event(self, widget, event):
        global optX
        global optY
        global module
        global move
        global modules
        global modules_selected
        global enable_movement
        global topConnectionB
        global edit
        global win
        global wiringA
        global wiringB
        global wiringW


        if event.button == 1 and move == 1 and edit==1:
            edit=0
            for item in modules:
                item.selected=0

        #New Module Window
        if event.button == 1 and module==1:
            optX = event.x
            optY = event.y
            
            idModule = uuid.uuid1().int
            modules.append(Module(idModule,optX,optY,100,100,0,optX,optY))
            self.queue_draw()
            # TO DO: optwin.show_all()

        #Selecting Single Module
        elif event.button == 1 and move==1 and modules_selected==0:
            optX = event.x
            optY = event.y
            for item in modules:
                if event.x >= item.posXNow and event.x <= item.posXNow+item.width and event.y >= item.posYNow and event.y <= item.posYNow+item.height:
                    if item.selected == 0:
                        item.selected=1
                        modules_selected=1
                        enable_movement=1
                    break
            self.queue_draw()

        #Grabbing Multiple Selected Modules
        elif event.button==1 and move==1 and modules_selected==1:
            optX = event.x
            optY = event.y
            enable_movement=1

        #Start wiring
        elif event.button==1 and wire==1 and modules_selected==0:
            optX = event.x
            optY = event.y
            for item in modules:
                if event.x >= item.posXNow and event.x <= item.posXNow+item.width and event.y >= item.posYNow and event.y <= item.posYNow+item.height:
                    modules_selected=1
                    wires.append( Wire(item.id,(item.posXNow+item.width),(item.posYNow+(item.height/2)),0,optX,optY) )
                    break
            self.queue_draw()

        #Finish Wiring
        elif event.button==1 and wire==1 and modules_selected==1:
            optX = event.x
            optY = event.y
            connected = 0
            for item in modules:
                #If button press has happened inside boundaries of item
                if event.x >= item.posXNow and event.x <= item.posXNow+item.width and event.y >= item.posYNow and event.y <= item.posYNow+item.height:
                    modules_selected=0
                    wire_index=0
                    for w in wires:
                        if w.idB==0:
                            connected=1
                            #Wiring Right to Left
                            if w.posXA > w.posXB :
                                w.idB=w.idA
                                w.posXB=w.posXA
                                w.posYB=w.posYA
                                w.idA=item.id
                                w.posXA=item.posXNow
                                w.posYA=item.posYNow+(item.height/2)
                                wiringA = w.idA
                                wiringB = w.idB
                                wiringW = wire_index
                            #Wiring Left to Right
                            else:
                                w.idB=item.id
                                w.posXB=item.posXNow
                                w.posYB=item.posYNow+(item.height/2)
                                wiringA = w.idA
                                wiringB = w.idB
                                wiringW = wire_index
                            break 
                        wire_index=wire_index+1  
                    break
            if connected==0:
                for ins in topConnections:
                    if event.x >= ins.posXNow and event.x<= ins.posXNow+ins.width:
                        modules_selected=0
                        wire_index=0
                        for w in wires:
                            if w.idB==0:
                                connected=1
                            #Wiring Right to Left
                                if w.posXA > w.posXB :
                                    w.idB=w.idA
                                    w.posXB=w.posXA
                                    w.posYB=w.posYA
                                    w.idA=ins.id
                                    w.posXA=ins.posXNow + (ins.width/2)
                                    w.posYA=w.posYB
                                    wiringA = w.idA
                                    wiringB = w.idB
                                    wiringW = wire_index
                            #Wiring Left to Right
                                else:
                                    w.idB=ins.id
                                    w.posXB=ins.posXNow+(ins.width/2)
                                    w.posYB=w.posYA
                                    wiringA = w.idA
                                    wiringB = w.idB
                                    wiringW = wire_index
                                break 
                            wire_index=wire_index+1  
                        break
            wireDefWin.update_port_list()
            wireDefWin.show_all()
            self.queue_draw()

        #New Input/Output
        elif event.button==1 and (topConnectionB):
            topConWin.show_all()

    def do_draw_cb(self, widget, cr):
        global modules
        global wires
        global topConnections
        global edit
        inputSpacing = 0
        outputSpacing= 0
        portStartX=0
        portStartY=0
        portFinalX=0
        portFinalY=0
        portLength=10
        strokeWidth = 1
        inputportSpacing=0
        outputportSpacing=0
        inoutportSpacing=0
        portSpace=10


        for item in modules:
            inputportSpacing=0
            outputportSpacing=0
            inoutportSpacing=0
            if item.deletion>=1:
                continue
            if item.selected == 1:
                cr.set_source_rgba(0,0,255,0.5)
            else: cr.set_source_rgba(0,0,0,1)
            if item.nPorts*portSpace > item.height:
                item.height = item.nPorts*portSpace
            rec = cr.rectangle(item.posXNow,item.posYNow,item.width,item.height)
            cr.fill()
            #Draw Ports...
            for port in item.portInfo:
                #Inputs
                if port[2] == 0:
                    portStartX = item.posXNow
                    portStartY = item.posYNow + strokeWidth + inputportSpacing
                    portFinalX = portStartX - portLength
                    portFinalY = portStartY
                    inputportSpacing = inputportSpacing  + portSpace
                elif port[2] == 1:
                    portStartX = item.posXNow + item.width
                    portStartY = item.posYNow + strokeWidth + outputportSpacing
                    portFinalX = portStartX + portLength
                    portFinalY = portStartY
                    outputportSpacing += portSpace
                elif port[2] == 2:
                    portStartX = item.posXNow + strokeWidth + inoutportSpacing
                    portStartY = item.posYNow + item.height
                    portFinalX = portStartX
                    portFinalY = portStartY + portLength
                    inoutportSpacing += portSpace
                cr.move_to(portStartX,portStartY)
                cr.line_to(portFinalX,portFinalY)
                cr.stroke()
                for w in wires:
                    if port[3]==w.idA:
                        w.posXA = portFinalX
                        w.posYA = portFinalY
                    elif port[3]==w.idB:
                        w.posXB = portFinalX
                        w.posYB = portFinalY
        spacing = 0
        for i in topConnections:
            if i.portInfo[0][2] == 0:
                spacing = outputSpacing
                outputSpacing=outputSpacing-i.width-5
            elif i.portInfo[0][2] == 1:
                spacing = inputSpacing
                inputSpacing=inputSpacing+i.width+5
            cr.set_source_rgba(0,0,0,1)
            cr.rectangle(i.posXNow+spacing,i.posYNow,i.width,i.height)
            cr.fill()
            cr.move_to(i.posXNow+spacing+(i.width/2),i.posYNow+(i.height/2))
            cr.line_to(i.posXNow+spacing+(i.width/2),900)
            cr.stroke()
            spacing = spacing + i.width + 5
            for w in wires:
                    if i.id==w.idA:
                        w.posXA = i.posXNow + (i.width/2)
                        w.posYA = w.posYB
                    elif i.id==w.idB:
                        w.posXB = i.posXNow + (i.width/2)
                        w.posYB = w.posYA
        for w in wires:
            cr.set_source_rgba(0,0,0,1)
            cr.move_to(w.posXB,w.posYB)
            cr.line_to(w.posXA,w.posYA)
            cr.stroke()
        return False

class ButtonArea(Gtk.ButtonBox):

    def __init__(self):
        Gtk.ButtonBox.__init__(self)
        self.set_layout(Gtk.ButtonBoxStyle(5))
        self.wireButton = Gtk.ToggleButton("Wire")
        self.moduleButton = Gtk.ToggleButton("Module")
        self.moveButton = Gtk.ToggleButton("Move")
        self.topConnectionButton = Gtk.ToggleButton("TopConnection")
        self.editButton = Gtk.Button("Edit")
        self.addButton = Gtk.Button("Add Ports")
        self.modifyButton = Gtk.Button("Modify Ports")
        self.deleteButton = Gtk.Button("Delete")
        self.recoverButton = Gtk.Button("Recover")


        self.wireButton.connect("toggled",self.on_toggled_wire)
        self.moduleButton.connect("toggled",self.on_toggled_module)
        self.moveButton.connect("toggled",self.on_toggled_move)
        self.topConnectionButton.connect("toggled",self.on_toggled_top_connection)
        self.editButton.connect("clicked",self.on_clicked_edit)
        self.addButton.connect("clicked",self.on_clicked_add)
        self.modifyButton.connect("clicked",self.on_clicked_modify)
        self.deleteButton.connect("clicked",self.on_clicked_delete)
        self.recoverButton.connect("clicked",self.on_clicked_recover)


        self.add(self.wireButton)
        self.add(self.moduleButton)
        self.add(self.moveButton)
        self.add(self.topConnectionButton)
        self.add(self.editButton)
        self.add(self.recoverButton)

        

        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        vbox.pack_start(self.addButton, False, True, 10)
        vbox.pack_start(self.modifyButton, False, True, 10)
        vbox.pack_start(self.deleteButton, False, True, 10)
        self.pop = Gtk.Popover()
        self.pop.add(vbox)



    def on_toggled_module(self, widget, data = None):
        global module
        global wire
        global move
        global topConnectionB
        if(self.moduleButton.get_active()):
            module = 1
            if self.wireButton.get_active():
                self.wireButton.set_active(False)
                wire = 0
            if self.moveButton.get_active():
                self.moveButton.set_active(False)
                move = 0        
                for item in modules:
                    item.selected=0
            if self.topConnectionButton.get_active():
                self.topConnectionButton.set_active(False)
                topConnectionB = 0
        else: module = 0

    def on_toggled_wire(self, widget, data = None):
        global module
        global wire
        global move
        global topConnectionB
        if(self.wireButton.get_active()):
            wire = 1
            if self.moduleButton.get_active():
                self.moduleButton.set_active(False)
                module = 0
            if self.moveButton.get_active():
                self.moveButton.set_active(False)
                move = 0        
                for item in modules:
                    item.selected=0
            if self.topConnectionButton.get_active():
                self.topConnectionButton.set_active(False)
                topConnectionB = 0
        else: wire = 0

    def on_toggled_move(self, widget, data = None):
        global module
        global wire
        global move
        global topConnectionB
        if(self.moveButton.get_active()):
            move = 1
            if self.moduleButton.get_active():
                self.moduleButton.set_active(False)
                module = 0
            if self.wireButton.get_active():
                self.wireButton.set_active(False)
                wire = 0
            if self.topConnectionButton.get_active():
                self.topConnectionButton.set_active(False)
                topConnectionB = 0
        else: move = 0

    def on_toggled_top_connection(self, widget, data = None):
        global module
        global wire
        global move
        global topConnectionB
        if(self.topConnectionButton.get_active()):
            topConnectionB = 1
            if self.moduleButton.get_active():
                self.moduleButton.set_active(False)
                module = 0
            if self.wireButton.get_active():
                self.wireButton.set_active(False)
                wire = 0
            if self.moveButton.get_active():
                self.moveButton.set_active(False)
                move = 0        
                for item in modules:
                    item.selected=0
        else: move = 0

    def on_clicked_edit(self, widget, data = None):
        global edit
        global modules_selected
        edit=1
        if modules_selected == 1:
            self.pop.set_relative_to(widget)
            self.pop.show_all()
            self.pop.popup()
        modules_selected=0

    def on_clicked_add(self,widget,data=None):
        global modules
        for item in modules:
            if item.selected:
                item.toAdd=1
            item.selected=0
        addPortWin.show_all()


    def on_clicked_modify(self,widget,data=None):
        global modules
        if multiple_selected >1:
            #multipleWarning.show_all()
            print("")
        else:
            for item in modules:
                if item.selected:
                    item.toMod=1
            modPortWin.update_port_list()       
            modPortWin.show_all()
        
        for item in modules:
            item.selected=0 
    def on_clicked_delete(self, widget, data=None):
        deleteW = []
        deleteM = []
        moduleIndex=-1
        wireIndex=-1
        pile=0
        for item in modules:
            if item.selected == 1:
                for w in wires:
                    if (w.idA == item.id or w.idB == item.id) and w.deletion==0:
                        w.deletion=1
                item.deletion = 1
                pile=1
        if pile:
            for item in modules:
                moduleIndex=moduleIndex+1
                if item.deletion >=1 and item.selected==0:
                    item.deletion=item.deletion+1
                    if item.deletion>=6:
                        deleteM.append(moduleIndex)
            for wire in wires:
                wireIndex=wireIndex+1
                if wire.deletion>=1:
                    wire.deletion=wire.deletion+1
                    if w.deletion>=6:
                        deleteW.append(wireIndex)
        for wI in deleteW:
            wires.pop(wI)
        for mI in deleteM:
            modules.pop(mI)
        for item in modules:
            item.selected=0
        #edit=0
        win.drawing_area.queue_draw()
    def on_clicked_recover(self,wdiget,data=None):
        for item in modules:
            if item.deletion>=1:
                item.deletion = item.deletion-1
        for wire in wires:
            if wire.deletion>=1:
                wire.deletion = wire.deletion-1
        win.drawing_area.queue_draw()

class OptionWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Insert New Module")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        self.inputs = Gtk.Entry()
        self.outputs = Gtk.Entry()
        inputsLabel = Gtk.Label("Name")
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
        global optwin
        idModule = uuid.uuid1().int
        modules.append(Module(idModule,optX,optY,100,100,0,optX,optY))
        if event.button == 1:
            optwin.inputs.set_text("")
            optwin.outputs.set_text("")
            optwin.hide()
        
        win.drawing_area.queue_draw()

    def cancelbutton_press_event(self, widget, event):
        global optwin
        if event.button == 1:
            optwin.hide()

class TopConnectionWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="New Top Connection")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        self.bitWidth = Gtk.Entry()
        self.name = Gtk.Entry()
        bitWidthLabel = Gtk.Label("Bit-Width")
        inputNameLabel = Gtk.Label("Name of Connection")

        self.connection_type=0

        self.port_types = Gtk.ListStore(int, str)
        self.port_types.append([0, "Input"])
        self.port_types.append([1, "Output"])
        self.port_types.append([2, "InOut"])

        self.port_types = Gtk.ComboBox.new_with_model_and_entry(self.port_types)
        self.port_types.connect("changed", self.on_port_combo_changed)
        self.port_types.set_entry_text_column(1)

        bWBox = Gtk.Box(spacing=12) 
        nBox = Gtk.Box(spacing=12)
        cTBox = Gtk.Box(spacing=12)

        bWBox.pack_start(bitWidthLabel,True,True,0)
        bWBox.pack_start(self.bitWidth,True,True,0)

        nBox.pack_start(inputNameLabel,True,True,0)
        nBox.pack_start(self.name,True,True,0)

        cTBox.pack_start(self.port_types,True,True,0)
        

        bBox = Gtk.ButtonBox()

        self.acceptButton = Gtk.Button("Accept")
        self.cancelButton = Gtk.Button("Cancel")
        bBox.pack_start(self.cancelButton,True,True,0)
        bBox.pack_start(self.acceptButton,True,True,0)

        vbox.pack_start(bWBox, True, True, 0)
        vbox.pack_start(nBox, True, True, 0)
        vbox.pack_start(cTBox, True, True, 0)
        vbox.pack_start(bBox,True,True,0)

        self.acceptButton.connect("button-press-event", self.acceptbutton_press_event)
        self.cancelButton.connect("button-press-event", self.cancelbutton_press_event)

    def on_port_combo_changed(self, combo):
        self.connection_type = combo.get_active()

    def acceptbutton_press_event(self, widget, event):
        global topConWin
        if self.connection_type==0:
            topConnections.append(TopConnection(int(topConWin.bitWidth.get_text()),topConWin.name.get_text(),0,0,15,15,uuid.uuid1().int,1))
        elif self.connection_type==1:
            topConnections.append(TopConnection(int(topConWin.bitWidth.get_text()),topConWin.name.get_text(),1700,0,15,15,uuid.uuid1().int,0))
        if event.button == 1:
            topConWin.name.set_text("")
            topConWin.bitWidth.set_text("")
            topConWin.hide()
        
        win.drawing_area.queue_draw()

    def cancelbutton_press_event(self, widget, event):
        global topConWin
        if event.button == 1:
            topConWin.hide()

class Module(object):

    def __init__(self,idModule,posXN,posYN,modWidth,modHeight,selected,orgX,orgY):
        self.id = idModule
        self.nPorts = 0
        self.posXNow = posXN
        self.posYNow = posYN
        self.width = modWidth
        self.height = modHeight
        self.selected = selected
        self.orgX = orgX
        self.orgY = orgY
        self.deletion = 0
        self.toAdd = 0
        self.toMod = 0
        self.portInfo = []

    def addPort(self,name,width,connectionType):
        self.portInfo.append([name,width,connectionType,uuid.uuid1().int])

class TopConnection(object):

    def __init__(self,bitwidth,name,posX,posY,inWidth,inHeight,idInput,connectionType):
        self.id = idInput
        self.name = name
        self.posXNow = posX
        self.posYNow = posY
        self.width = inWidth
        self.height = inHeight
        self.portInfo = [[self.name,bitwidth,connectionType,self.id]]

class Wire(object):

    def __init__(self,idModuleA,posX_A,posY_A,idModuleB,posXB,posYB):
        #AT CONNECTION, IDA AND IDB ARE PORT NAMES
        self.idA = idModuleA
        self.modIdA = idModuleA
        self.portA = ""
        self.posXA = posX_A
        self.posYA = posY_A
        self.idB = idModuleB
        self.modIdB = idModuleB
        self.portB = ""
        self.posXB = posXB
        self.posYB = posYB
        self.deletion = 0
        self.width = 0

class AddPortWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="New Module Port")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        self.bitWidth = Gtk.Entry()
        self.name = Gtk.Entry()
        self.connection_type = -1
        bitWidthLabel = Gtk.Label("Bit-Width")
        inputNameLabel = Gtk.Label("Name of Port")

        self.port_types = Gtk.ListStore(int, str)
        self.port_types.append([0, "Input"])
        self.port_types.append([1, "Output"])
        self.port_types.append([2, "InOut"])

        self.port_types = Gtk.ComboBox.new_with_model_and_entry(self.port_types)
        self.port_types.connect("changed", self.on_port_combo_changed)
        self.port_types.set_entry_text_column(1)

        ibox = Gtk.Box(spacing=12) 
        obox = Gtk.Box(spacing=12)
        ibox.pack_start(bitWidthLabel,True,True,0)
        ibox.pack_start(self.bitWidth,True,True,0)

        obox.pack_start(inputNameLabel,True,True,0)
        obox.pack_start(self.name,True,True,0)
        
        vbox.pack_start(ibox, True, True, 0)
        vbox.pack_start(obox, True, True, 0)
        vbox.pack_start(self.port_types, False, False, 0)

        bBox = Gtk.ButtonBox()

        self.acceptButton = Gtk.Button("Accept")
        self.cancelButton = Gtk.Button("Cancel")
        bBox.pack_start(self.cancelButton,True,True,0)
        bBox.pack_start(self.acceptButton,True,True,0)
        vbox.pack_start(bBox,True,True,0)

        self.acceptButton.connect("button-press-event", self.acceptbutton_press_event)
        self.cancelButton.connect("button-press-event", self.cancelbutton_press_event)

    def on_port_combo_changed(self, combo):
        self.connection_type = combo.get_active()

    def acceptbutton_press_event(self, widget, event):
        global win
        global edit
        #edit=0
        if event.button == 1:
            for item in modules:
                item.selected=0
                if item.toAdd:
                    item.addPort(self.name.get_text(),int(self.bitWidth.get_text()),self.connection_type)
                    item.toAdd=0
            self.name.set_text("")
            self.bitWidth.set_text("")
            self.hide()
            win.buttonArea.pop.hide()
        
            win.drawing_area.queue_draw()

    def cancelbutton_press_event(self, widget, event):
        global edit
        #edit=0
        if event.button == 1:
            
            for item in modules:
                item.selected=0
                if item.toAdd:
                    item.toAdd=0
            self.name.set_text("")
            self.bitWidth.set_text("")
            self.port_types.set_active(-1)
            self.connection_type=-1
            self.hide()

class ModPortWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Modify Ports")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        paned = Gtk.Paned().new(Gtk.Orientation.HORIZONTAL)
        hbox = Gtk.Box(spacing=12)         
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        nameBox = Gtk.Box(spacing=12)
        bitwidthBox = Gtk.Box(spacing=12)
        self.port_selected = 0
        nameLabel = Gtk.Label("Port Name: ")
        bitwidthLabel = Gtk.Label("Bit-Width:  ")
        self.bitWidth = Gtk.Entry()
        self.name = Gtk.Entry()

        self.port_types = Gtk.ListStore(int, str)
        self.port_types.append([0, "Input"])
        self.port_types.append([1, "Output"])
        self.port_types.append([2, "InOut"])
        self.port_types = Gtk.ComboBox.new_with_model_and_entry(self.port_types)
        self.port_types.connect("changed", self.on_port_combo_changed)
        self.port_types.set_entry_text_column(1)

        #deleteButton = Gtk.Button("Delete")
        exitButton = Gtk.Button("Exit")
        applyButton = Gtk.Button("Apply")



        #self.port_list = Gtk.ListStore(str)
        self.portlist = []
        self.port_listBox = Gtk.ListBox().new()
        self.port_listBox.connect("row-selected",self.on_row_selected)
        nameBox.pack_start(nameLabel, True, True, 0)
        nameBox.pack_start(self.name, True, True, 0)
        self.connection_type = 0
        bitwidthBox.pack_start(bitwidthLabel, True, True, 0)
        bitwidthBox.pack_start(self.bitWidth, True, True, 0)

        vbox.pack_start(nameBox, True, True, 0)
        vbox.pack_start(bitwidthBox, True, True, 0)
        vbox.pack_start(self.port_types, True, True, 0)
        #hbox.pack_start(deleteButton, True, True, 0)
        hbox.pack_start(exitButton, True, True, 0)
        hbox.pack_start(applyButton, True, True, 0)
        vbox.pack_start(hbox, True, True, 0)

        exitButton.connect("button-press-event",self.exitbutton_press_event)
        applyButton.connect("button-press-event",self.applybutton_press_event)

        paned.add1(self.port_listBox)
        paned.add2(vbox)

        self.add(paned)

    def update_port_list(self):
        for item in modules:
            if item.toMod:
                for port in item.portInfo:
                    #self.port_list.append(port)
                    #row = Gtk.Box(spacing=12) 
                    #row.pack_start(Gtk.Label(port[0]), True, True, 0)
                    self.port_listBox.insert(Gtk.Label(port[0]),-1)
                    self.portlist.append(port)
                break

    def on_row_selected(self, widget, row):
        self.name.set_text(self.portlist[row.get_index()][0])
        self.bitWidth.set_text(str(self.portlist[row.get_index()][1]))
        self.port_types.set_active(self.portlist[row.get_index()][2])
        self.port_selected = row.get_index()

    def on_port_combo_changed(self, combo):
        self.connection_type = combo.get_active()

    def applybutton_press_event(self, widget, event):
        global win
        if event.button == 1:
            for item in modules:
                if item.toMod:
                    item.portInfo[self.port_selected][0] = self.name.get_text()
                    item.portInfo[self.port_selected][1] = int(self.bitWidth.get_text())
                    item.portInfo[self.port_selected][2] = self.connection_type
                    self.portlist[self.port_selected][0] = item.portInfo[self.port_selected][0]
                    self.portlist[self.port_selected][1] = item.portInfo[self.port_selected][1]
                    self.portlist[self.port_selected][2] = item.portInfo[self.port_selected][2] 

    def exitbutton_press_event(self, widget, event):
        global edit
        #edit=0
        if event.button == 1: 
            for item in modules:
                if item.toMod:
                    item.toMod=0
            self.hide()        
            win.drawing_area.queue_draw()


class WireDefinitionWindow(Gtk.Window):

    def __init__(self):
        Gtk.Window.__init__(self, title="Define Wire")
        
        self.set_position(Gtk.WindowPosition.CENTER)
        
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        
        labelBox = Gtk.Box(spacing=12)
        paned = Gtk.Paned().new(Gtk.Orientation.HORIZONTAL)
        buttonBox = Gtk.Box(spacing=12)

        nameALabel = Gtk.Label("Port A Name: ")
        nameBLabel = Gtk.Label("Port B Name: ")
        labelBox.pack_start(nameALabel, True, True, 0)
        labelBox.pack_start(nameBLabel, True, True, 0)


        self.portlistA = []
        self.port_listBoxA = Gtk.ListBox().new()
        self.port_listBoxA.connect("row-selected",self.on_row_selectedA)
        self.port_selectedA=0

        self.portlistB = []
        self.port_listBoxB = Gtk.ListBox().new()
        self.port_listBoxB.connect("row-selected",self.on_row_selectedB)
        self.port_selectedB=0


        exitButton = Gtk.Button("Exit")
        acceptButton = Gtk.Button("Apply")

        exitButton.connect("button-press-event",self.exitbutton_press_event)
        acceptButton.connect("button-press-event",self.acceptbutton_press_event)

        buttonBox.pack_start(exitButton,True,True,0)
        buttonBox.pack_start(acceptButton,True,True,0)

        paned.add1(self.port_listBoxA)
        paned.add2(self.port_listBoxB)

        vbox.pack_start(labelBox, False, False, 0)
        vbox.pack_start(paned,True,True,0)
        vbox.pack_start(buttonBox, False, False, 0)

        self.add(vbox)

    def update_port_list(self):
        for item in modules:
            if item.id == wiringA:
                for port in self.port_listBoxA:
                    self.port_listBoxA.remove(port)
                for port in item.portInfo:
                    self.port_listBoxA.insert(Gtk.Label(port[0]),-1)
                    self.portlistA.append(port)
            elif item.id == wiringB:
                for port in self.port_listBoxB:
                    self.port_listBoxB.remove(port)
                for port in item.portInfo:
                    self.port_listBoxB.insert(Gtk.Label(port[0]),-1)
                    self.portlistB.append(port)
        for item in topConnections:
            if item.id == wiringA:
                for port in self.port_listBoxA:
                    self.port_listBoxA.remove(port)
                for port in item.portInfo:
                    self.port_listBoxA.insert(Gtk.Label(port[0]),-1)
                    self.portlistA.append(port)
            elif item.id == wiringB:
                for port in self.port_listBoxB:
                    self.port_listBoxB.remove(port)
                for port in item.portInfo:
                    self.port_listBoxB.insert(Gtk.Label(port[0]),-1)
                    self.portlistB.append(port)

    def on_row_selectedA(self, widget, row):
        if row != None: self.port_selectedA = row.get_index()

    def on_row_selectedB(self, widget, row):
        if row != None: self.port_selectedB = row.get_index()

    def acceptbutton_press_event(self, widget, event):
        global win
        global wiringW
        global wires
        global wireDefWin
        if event.button == 1:
            if not( (self.portlistA[self.port_selectedA][2] == self.portlistB[self.port_selectedB][2]) and self.portlistA[self.port_selectedA][2]<=1 ):
                wires[wiringW].idA = self.portlistA[self.port_selectedA][3]
                wires[wiringW].idB = self.portlistB[self.port_selectedB][3]
                wireDefWin.hide()

    def exitbutton_press_event(self, widget, event):
        if event.button == 1:
            self.hide()        
            win.drawing_area.queue_draw()

wireDefWin = WireDefinitionWindow()
optwin = OptionWindow()
topConWin = TopConnectionWindow()
addPortWin = AddPortWindow()
modPortWin = ModPortWindow()
win = SchematicWindow()
win.connect("destroy", Gtk.main_quit)
win.maximize()
win.show_all()
Gtk.main()
