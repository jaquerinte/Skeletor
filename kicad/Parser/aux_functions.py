from sexpdata import loads,car,cdr
import re
symbol = re.compile(r'Symbol\(\'(?P<value>.*)\'\)')

bracket = re.compile(r'Bracket\(\[Symbol\(\'(?P<symbol>.*)\'\)\], \'(?P<value>.*)\'\)')
def symbol_value(s):
    result = symbol.search(s)
    if result:
        return result.group('value')
    return ''