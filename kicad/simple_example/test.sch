EESchema Schematic File Version 4
LIBS:test-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "pipeline"
Date "2019-06-11"
Rev "0.1"
Comp ""
Comment1 "Test of kicad as GUI for compiler"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5CFFE83C
P 2700 1650
F 0 "J2" H 2780 1692 50  0000 L CNN
F 1 "Conn_01x03" H 2780 1601 50  0000 L CNN
F 2 "" H 2700 1650 50  0001 C CNN
F 3 "~" H 2700 1650 50  0001 C CNN
	1    2700 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5CFFFBFF
P 1600 1650
F 0 "J1" H 1680 1692 50  0000 L CNN
F 1 "Conn_01x03" H 1680 1601 50  0000 L CNN
F 2 "" H 1600 1650 50  0001 C CNN
F 3 "~" H 1600 1650 50  0001 C CNN
	1    1600 1650
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 1550 2500 1550
Wire Wire Line
	1800 1650 2000 1650
Wire Wire Line
	2000 1650 2000 1750
Wire Wire Line
	2000 1750 1800 1750
Wire Wire Line
	2500 1650 2300 1650
Wire Wire Line
	2300 1650 2300 1750
Wire Wire Line
	2300 1750 2500 1750
$EndSCHEMATC
