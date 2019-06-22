EESchema Schematic File Version 4
LIBS:test-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2400 2100 0    50   Input ~ 0
clk
Text HLabel 2400 2200 0    50   Input ~ 0
rst
Text HLabel 2400 2300 0    50   Input ~ 0
pc
Text HLabel 3300 2300 0    50   Output ~ 0
nextpc
Text HLabel 3300 2100 0    50   Output ~ 0
instruction
$Comp
L test:fetch U1
U 1 1 5D0E5C28
P 2750 2300
AR Path="/5D0CED5A/5D105301/5D0E5C28" Ref="U1"  Part="1" 
AR Path="/5D0CED5A/5D11577B/5D0E5C28" Ref="U6"  Part="1" 
F 0 "U6" H 2850 2725 50  0000 C CNN
F 1 "fetch" H 2850 2634 50  0000 C CNN
F 2 "" H 2700 2750 50  0001 C CNN
F 3 "" H 2700 2750 50  0001 C CNN
	1    2750 2300
	1    0    0    -1  
$EndComp
$EndSCHEMATC
