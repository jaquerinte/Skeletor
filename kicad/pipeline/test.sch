EESchema Schematic File Version 4
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
L test:fetch U1
U 1 1 5CFFAB2A
P 1850 1800
F 0 "U1" H 1950 2225 50  0000 C CNN
F 1 "fetch" H 1950 2134 50  0000 C CNN
F 2 "" H 1800 2250 50  0001 C CNN
F 3 "" H 1800 2250 50  0001 C CNN
	1    1850 1800
	1    0    0    -1  
$EndComp
$Comp
L test:decode U2
U 1 1 5CFFAFA1
P 3500 2100
F 0 "U2" H 4100 2765 50  0000 C CNN
F 1 "decode" H 4100 2674 50  0000 C CNN
F 2 "" H 3050 2350 50  0001 C CNN
F 3 "" H 3050 2350 50  0001 C CNN
	1    3500 2100
	1    0    0    -1  
$EndComp
$Comp
L test:memory U3
U 1 1 5CFFF824
P 4150 4400
F 0 "U3" H 4150 4965 50  0000 C CNN
F 1 "memory" H 4150 4874 50  0000 C CNN
F 2 "" H 4000 4900 50  0001 C CNN
F 3 "" H 4000 4900 50  0001 C CNN
	1    4150 4400
	1    0    0    -1  
$EndComp
$Comp
L test:writeback U5
U 1 1 5CFFFCC8
P 7550 4400
F 0 "U5" H 7550 4965 50  0000 C CNN
F 1 "writeback" H 7550 4874 50  0000 C CNN
F 2 "" H 7550 5000 50  0001 C CNN
F 3 "" H 7550 5000 50  0001 C CNN
	1    7550 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1600 2400 1300
Wire Wire Line
	2400 1300 1250 1300
Wire Wire Line
	1250 1300 1250 1800
Wire Wire Line
	1250 1800 1500 1800
Wire Wire Line
	5400 1700 6000 1700
Wire Wire Line
	6000 1700 6000 1850
Wire Wire Line
	6000 1850 6250 1850
Wire Wire Line
	5400 1800 5950 1800
Wire Wire Line
	5950 1800 5950 1950
Wire Wire Line
	5950 1950 6250 1950
Wire Wire Line
	5400 1900 5900 1900
Wire Wire Line
	5900 1900 5900 2050
Wire Wire Line
	5900 2050 6250 2050
Wire Wire Line
	5400 2000 5850 2000
Wire Wire Line
	5850 2000 5850 2150
Wire Wire Line
	5850 2150 6250 2150
Wire Wire Line
	5400 2100 5800 2100
Wire Wire Line
	5800 2100 5800 2250
Wire Wire Line
	5800 2250 6250 2250
Wire Wire Line
	5750 2200 5750 2350
Wire Wire Line
	5750 2350 6250 2350
Wire Wire Line
	5400 2200 5750 2200
$Comp
L test:execute U4
U 1 1 5CFFB5C1
P 7550 2050
F 0 "U4" H 7550 2715 50  0000 C CNN
F 1 "execute" H 7550 2624 50  0000 C CNN
F 2 "" H 7400 2650 50  0001 C CNN
F 3 "" H 7400 2650 50  0001 C CNN
	1    7550 2050
	1    0    0    -1  
$EndComp
Text GLabel 1500 1700 0    50   Input ~ 0
rst
Text GLabel 1500 1600 0    50   Input ~ 0
clk
Text GLabel 2800 1800 0    50   Input ~ 0
rst
Text GLabel 2800 1700 0    50   Input ~ 0
clk
Text GLabel 2900 4200 0    50   Input ~ 0
rst
Text GLabel 2900 4100 0    50   Input ~ 0
clk
Text GLabel 6300 4200 0    50   Input ~ 0
rst
Text GLabel 6300 4100 0    50   Input ~ 0
clk
Wire Wire Line
	8850 1650 9000 1650
Wire Wire Line
	9000 1650 9000 3600
Wire Wire Line
	8850 1750 9100 1750
Wire Wire Line
	9100 1750 9100 3500
Wire Wire Line
	8850 1850 9200 1850
Wire Wire Line
	9200 1850 9200 3400
Wire Wire Line
	8850 1950 9300 1950
Wire Wire Line
	9300 1950 9300 3300
Wire Wire Line
	8850 2050 9400 2050
Wire Wire Line
	9400 2050 9400 3200
Wire Wire Line
	8850 2150 9500 2150
Wire Wire Line
	9500 2150 9500 3100
Wire Wire Line
	9000 3600 2700 3600
Wire Wire Line
	2700 3600 2700 4300
Wire Wire Line
	2700 4300 2900 4300
Wire Wire Line
	2600 3500 2600 4400
Wire Wire Line
	2600 4400 2900 4400
Wire Wire Line
	2600 3500 9100 3500
Wire Wire Line
	9200 3400 2500 3400
Wire Wire Line
	2500 3400 2500 4500
Wire Wire Line
	2500 4500 2900 4500
Wire Wire Line
	9300 3300 2400 3300
Wire Wire Line
	2400 3300 2400 4600
Wire Wire Line
	2400 4600 2900 4600
Wire Wire Line
	2900 4700 2300 4700
Wire Wire Line
	2300 4700 2300 3200
Wire Wire Line
	2300 3200 9400 3200
Wire Wire Line
	2900 4800 2200 4800
Wire Wire Line
	2200 4800 2200 3100
Wire Wire Line
	2200 3100 9500 3100
Wire Wire Line
	5400 4100 6100 4100
Wire Wire Line
	6100 4100 6100 4300
Wire Wire Line
	6100 4300 6300 4300
Wire Wire Line
	5400 4200 6000 4200
Wire Wire Line
	6000 4200 6000 4400
Wire Wire Line
	6000 4400 6300 4400
Wire Wire Line
	5400 4300 5900 4300
Wire Wire Line
	5900 4300 5900 4700
Wire Wire Line
	5900 4700 6300 4700
Wire Wire Line
	5400 4400 5800 4400
Wire Wire Line
	5800 4400 5800 4500
Wire Wire Line
	5800 4500 6300 4500
Wire Wire Line
	5400 4500 5650 4500
Wire Wire Line
	5650 4500 5650 4600
Wire Wire Line
	5650 4600 6300 4600
Wire Wire Line
	2800 2200 2100 2200
Wire Wire Line
	2100 2200 2100 5100
Wire Wire Line
	2100 5100 8900 5100
Wire Wire Line
	8900 5100 8900 4100
Wire Wire Line
	8900 4100 8800 4100
Wire Wire Line
	8800 4200 9000 4200
Wire Wire Line
	9000 4200 9000 5200
Wire Wire Line
	9000 5200 2000 5200
Wire Wire Line
	2000 5200 2000 2000
Wire Wire Line
	8800 4300 9100 4300
Wire Wire Line
	9100 4300 9100 5300
Wire Wire Line
	9100 5300 1900 5300
Wire Wire Line
	1900 5300 1900 2100
Wire Wire Line
	1900 2100 2800 2100
Wire Wire Line
	2000 2000 2800 2000
Wire Wire Line
	2800 1900 2500 1900
Wire Wire Line
	2400 1800 2500 1800
Wire Wire Line
	2500 1800 2500 1900
Wire Wire Line
	5700 2450 6250 2450
Wire Wire Line
	5400 2300 5700 2300
Wire Wire Line
	5700 2300 5700 2450
Wire Wire Line
	5650 2550 6250 2550
Wire Wire Line
	5400 2400 5650 2400
Wire Wire Line
	5650 2400 5650 2550
Wire Wire Line
	5600 2650 6250 2650
Wire Wire Line
	5400 2500 5600 2500
Wire Wire Line
	5600 2500 5600 2650
Text GLabel 6250 1750 0    50   Input ~ 0
rst
Text GLabel 6250 1650 0    50   Input ~ 0
clk
$EndSCHEMATC
