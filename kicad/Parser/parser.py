from sexpdata import loads,car,cdr
import re

modules = set() # Set that contains all the modules

dicModName = dict() # Dictionary that saves {instance -> Module}

moduleSignals = dict() # Dictionary of modules and its signals. The signals are a dictionary of their name and type. i.e., module1 -> [clk -> input, rst -> input], module2 -> ["[BITS_REGFILE:0]_destination" -> input]

symbol = re.compile(r'Symbol\(\'(?P<value>.*)\'\)')

bracket = re.compile(r'Bracket\(\[Symbol\(\'(?P<symbol>.*)\'\)\], \'(?P<value>.*)\'\)')

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

# regex = re.compile(r'^Symbol\(\'(?P<value>.*)\'\)$')



# def symbol_value(s):
#     result = regex.search(s)
#     if result:
#         return result.group('value')
#     return ''


def main():
    #f = open("test.net", "r")
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

                            if(isinstance(header[i],list) and len(header[i])>=4):
                                for pins in header[i][4]:
                                    if isinstance(pins,list) and len(pins) == 4:
                                        if len(pins[2]) > 2: # If the name of the pin has brackets, the imported library chops it in a non-desired manner.
                                            name_1, bracket = bracket_value(pins[2][1])
                                            # We take care of the name of the pins with brackets.
                                            moduleSignals[symbol_value(str(header[i][2][1]))][pins[1][1]] = [str(bracket)+str(name_1)+"]"+symbol_value(str(pins[2][2])), symbol_value(str(pins[3][1]))] 
                                        else:
                                            # And those without them, we take care of them in a different manner.
                                            moduleSignals[symbol_value(str(header[i][2][1]))][pins[1][1]] = [symbol_value(str(pins[2][1])), symbol_value(str(pins[3][1]))]


                    i+=1
    # for key,value in moduleSignals.items():
    #     print(key, ":",value)
        

                



if __name__== "__main__":
  main()