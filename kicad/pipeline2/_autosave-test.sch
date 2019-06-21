EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title "pipeline"
Date "2019-06-11"
Rev "0.1"
Comp ""
Comment1 "Test of kicad as GUI for compiler"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3700 2550 2900 2550
Wire Wire Line
	3700 2650 2650 2650
Wire Wire Line
	2650 2650 2650 2450
Text GLabel 2650 2450 0    50   Input ~ 0
GLOBAL_CLK
Text GLabel 2800 2250 0    50   Input ~ 0
GLOBAL_RST
Wire Wire Line
	2900 2250 2800 2250
Wire Wire Line
	2900 2250 2900 2550
$Sheet
S 3700 2400 1800 1500
U 5D0CED5A
F0 "TOP" 50
F1 "TOP.sch" 50
F2 "clk" I L 3700 2650 50 
F3 "rst" I L 3700 2550 50 
F4 "out1" O R 5500 2700 50 
$EndSheet
Text GLabel 6150 2350 0    50   Output ~ 0
GLOBAL_OUT1
Wire Wire Line
	5500 2700 6250 2700
Wire Wire Line
	6250 2700 6250 2350
Wire Wire Line
	6250 2350 6150 2350
$EndSCHEMATC
