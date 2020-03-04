import sys
#import kicad.Parser.parser_top_functions as func
import parser_top_functions as func

def main():
    files = func.checkArgs(sys.argv)
    modules_tree = func.readValues(files[0])
    #func.writeValues(files[1], modules_tree)
    print(modules_tree)
    #print(sys.argv)

if __name__== "__main__":
  main()