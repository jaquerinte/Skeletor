from sexpdata import loads,car,cdr
import re
# class token(object):
#  def init (self,name,value):
#   pass

modules = set()
regex = re.compile(r'^Symbol\(\'(?P<value>.*)\'\)$')

def symbol_value(s):
    result = regex.search(s)
    if result:
        return result.group('value')
    return ''


def main():
    #f = open("test.net", "r")
    f = open("test_big.net", "r")
    #print(f.readline())
    netList = loads(f.read())
    for header in netList:
        if isinstance(header, list):
            if symbol_value(str(header[0])) == "libparts": # libparts contains the name of the modules that are going to be included in a set.
                i = 0
                while i<len(header):
                    if(isinstance(header[i],list) and len(header[i])>=3):
                        if(isinstance(header[i][2],list) and len(header[i])>=2):
                            modules.add(symbol_value(str(header[i][2][1])))
                    i+=1




    # for subitme in item:
    #  if isinstance(subitme, list):
    #   if str(subitme[0]) == "Symbol('comp')":
    #    print(subitme[1][1])

 #print(car(cdr(cdr(cdr(a)))))

if __name__== "__main__":
  main()