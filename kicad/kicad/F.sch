EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L OUTPUT:a U1
U 1 1 5E3C1125
P 2750 1950
F 0 "U1" H 3150 2615 50  0000 C CNN
F 1 "a" H 3150 2524 50  0000 C CNN
F 2 "" H 2750 1950 50  0001 C CNN
F 3 "" H 2750 1950 50  0001 C CNN
	1    2750 1950
	1    0    0    -1  
$EndComp
Text HLabel 1250 1100 0    50   Input ~ 0
in1
Text HLabel 3650 1550 2    50   Output ~ 0
out1
$Sheet
S 1250 1000 850  1150
U 5E3BF362
F0 "GG" 50
F1 "GG.sch" 50
F2 "in1" I L 1250 1100 50 
F3 "out1" O R 2100 1100 50 
$EndSheet
Wire Wire Line
	2100 1100 2450 1100
Wire Wire Line
	2450 1100 2450 1550
Wire Wire Line
	2450 1550 2650 1550
$EndSCHEMATC
