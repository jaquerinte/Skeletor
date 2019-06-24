from sexpdata import loads,car,cdr
import re

modules = set() # Set that contains all the modules

dicModName = dict() # Dictionary that saves {instance -> Module}

moduleSignals = dict() # Dictionary of modules and its signals. The signals are a dictionary of their name and type. i.e., module1 -> [clk -> [width, input], rst -> [width,input]], module2 -> [destination -> [width,input]]

topSignals = dict() # Dictionary with the top signals and the modules they connect to and their type. e.g., nameSignal -> {[instance1, instance2, instance3], input}

wires = []

symbol = re.compile(r'Symbol\(\'(?P<value>.*)\'\)')

bracket = re.compile(r'Bracket\(\[Symbol\(\'(?P<symbol>.*)\'\)\], \'(?P<value>.*)\'\)')

class wire (object):
    def __init__(self, id, no, ni, o, i, width=""):
        self.id = id
        self.name_ins_out = no
        self.name_ins_in = ni
        self.output = o
        self.input = i
        self.width = width
        self.wire_output = "wire %s.%s%s -> %s.%s" % (no,width,o,ni,i)


def symbol_value(s):
    result = symbol.search(s)
    if result:
        return result.group('value')
    return ''

def bracket_value(s):
    result = bracket.search(str(s))
    if result:
        return result.group('symbol'), result.group('value')
    return '',''


def main():
    # f = open("test.net", "r")
    f = open("test_big.net", "r")
    netList = loads(f.read())
    for header in netList:
        if isinstance(header, list):

            if symbol_value(str(header[0])) == "components": # components contains the instances of the modules.
                i = 1
                while i<len(header):
                    # We check the sizes of the entries to check if we can iterate over them.
                    if isinstance(header[i],list) >=1:
                        if isinstance(header[i][1],list) >=1 and isinstance(header[i][2],list) >=1:
                            # We store as a key the name of the instance and as a value, the name of the module.
                            dicModName[symbol_value(str(header[i][1][1]))] = symbol_value(str(header[i][2][1])) 
                    i+=1

            if symbol_value(str(header[0])) == "libparts": # libparts contains the name of the modules.
                i = 0
                while i<len(header):
                    if(isinstance(header[i],list) and len(header[i])>=3):
                        if(isinstance(header[i][2],list) and len(header[i])>=2):
                            modules.add(symbol_value(str(header[i][2][1]))) # We add the name of the modules 
                            moduleSignals[symbol_value(str(header[i][2][1]))] = {}

                            if isinstance(header[i],list):
                                for sect in header[i]:
                                    if isinstance(sect,list) and symbol_value(str(sect[0])):
                                        for pins in sect: # We cannot fix the value to 4, we must look for the one that is "pins".
                                            if isinstance(pins,list) and len(pins) == 4:
                                                if len(pins[2]) > 2: # If the name of the pin has brackets, the imported library chops it in a non-desired manner.
                                                    name_1, bracket = bracket_value(pins[2][1])
                                                    # print(name_1)
                                                    # print(bracket)
                                                    # We take care of the name of the pins with brackets.
                                                    moduleSignals[symbol_value(str(header[i][2][1]))][pins[1][1]] = [symbol_value(str(pins[2][2])), [str(bracket)+str(name_1)+"]",symbol_value(str(pins[3][1]))]] 
                                                else:
                                                    # And those without them, we take care of them in a different manner.
                                                    moduleSignals[symbol_value(str(header[i][2][1]))][pins[1][1]] = [symbol_value(str(pins[2][1])), ["",symbol_value(str(pins[3][1]))]]


                    i+=1
            
            
            if symbol_value(str(header[0])) == "nets":
                for net in header:
                    if isinstance(net,list):
                        id = net[1][1]

                        # First indexing to get the module name from the instance, second index to index the pin, third index to index the type of the pin.
                        if "Symbol" not in str(net[2][1]): # Signals that come from the top modules use the Symbol name convention.
                            
                            if moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][1][1] == "output" or moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][1][1] == "bidireccional":

                                name_ins_out = symbol_value(str(net[3][1][1])) # Module that outputs the signal.
                                name_ins_in = symbol_value(str(net[4][1][1])) # Module that inputs the signal.
                                

                                outpt = moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][0] # Output signal
                                inpt = moduleSignals[dicModName[symbol_value(str(net[4][1][1]))]][net[4][2][1]][0] # Input signal
                                inpt = inpt.replace("_","")
                                
                                width = moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][1][0] # The width that will be concatenated to the output signal.

                            elif moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][1][1] == "input":

                                name_ins_in = symbol_value(str(net[3][1][1])) # Module that inputs the signal.
                                
                                name_ins_out = symbol_value(str(net[4][1][1])) # Module that outputs the signal.

                                inpt = moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][0] # Input signal

                                inpt = inpt.replace("_","")
                                    
                                outpt = moduleSignals[dicModName[symbol_value(str(net[4][1][1]))]][net[4][2][1]][0] # Output signal

                                
                                width = moduleSignals[dicModName[symbol_value(str(net[4][1][1]))]][net[4][2][1]][1][0] # The width that will be concatenated to the output signal.

                            else:
                                print("Error, pins must be of type input, output or bidireccional")
                                exit()

                            wires.append(wire(id, name_ins_out, name_ins_in, outpt, inpt, width))

                        else:
                            width = ""
                            name = ""
                            if len(net[2]) > 2: # If the width of the signal is specified.

                                name = symbol_value(str(net[2][2])).replace("_","") # We get the name to use it as a key and remove the underscore used for the width.
                                
                                name_1, bracket = bracket_value(net[2][1])

                                width = bracket + name_1 + "]"

                                topSignals[name] = {}

                            else:
                                name = symbol_value(str(net[2][1]))
                                topSignals[name] = {}
                            modulesToSignal = {}
                            if isinstance(net,list):
                                for mod in net:
                                    if isinstance(mod,list) and len(mod)>=3 and symbol_value(str(mod[0])) == "node":

                                        modulesToSignal[symbol_value(str(mod[1][1]))] = moduleSignals[dicModName[symbol_value(str(mod[1][1]))]][net[3][2][1]][0]

                                topSignals[name] = [modulesToSignal, width, moduleSignals[dicModName[symbol_value(str(net[3][1][1]))]][net[3][2][1]][1][1]]
                            
                        

    for key,value in topSignals.items():
        print(key, ":",value)

    # for cable in wires:
        # print(cable.id)
        # print(cable.name_ins_out)
        # print(cable.name_ins_in)
        # print(cable.output)
        # print(cable.input)
        # print(cable.width)
        # print(cable.wire_output)
    # print(modules)
    # print(dicModName)
    # for key,value in moduleSignals.items():
    #     print(key, ":",value)

                



if __name__== "__main__":
  main()