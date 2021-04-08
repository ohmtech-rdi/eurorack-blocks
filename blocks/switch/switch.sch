EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L power:PWR_FLAG #FLG0101
U 1 1 5FC83467
P 7900 4700
F 0 "#FLG0101" H 7900 4775 50  0001 C CNN
F 1 "PWR_FLAG" H 7900 4874 50  0000 C CNN
F 2 "" H 7900 4700 50  0001 C CNN
F 3 "~" H 7900 4700 50  0001 C CNN
	1    7900 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5FC83485
P 7900 4700
F 0 "#PWR0106" H 7900 4450 50  0001 C CNN
F 1 "GND" H 7905 4527 50  0000 C CNN
F 2 "" H 7900 4700 50  0001 C CNN
F 3 "" H 7900 4700 50  0001 C CNN
	1    7900 4700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5FD25C62
P 3700 4000
F 0 "J1" H 3620 3675 50  0000 C CNN
F 1 "POWER" H 3620 3766 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3700 4000 50  0001 C CNN
F 3 "~" H 3700 4000 50  0001 C CNN
F 4 "Male Hader" H 3700 4000 50  0001 C CNN "Device"
F 5 "CONN HEADER VERT 3POS 2.54MM" H 3700 4000 50  0001 C CNN "Description"
F 6 "No" H 3700 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 3700 4000 50  0001 C CNN "Dist"
F 8 "609-3468-ND" H 3700 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/amphenol-icc-fci/68001-103HLF/609-3468-ND/2023306" H 3700 4000 50  0001 C CNN "DistLink"
	1    3700 4000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5FD260DD
P 6300 4000
F 0 "J2" H 6219 3675 50  0000 C CNN
F 1 "OUT" H 6219 3766 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6300 4000 50  0001 C CNN
F 3 "~" H 6300 4000 50  0001 C CNN
F 4 "Male Hader" H 6300 4000 50  0001 C CNN "Device"
F 5 "CONN HEADER VERT 3POS 2.54MM" H 6300 4000 50  0001 C CNN "Description"
F 6 "No" H 6300 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 6300 4000 50  0001 C CNN "Dist"
F 8 "609-3468-ND" H 6300 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/amphenol-icc-fci/68001-103HLF/609-3468-ND/2023306" H 6300 4000 50  0001 C CNN "DistLink"
	1    6300 4000
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5FD2628F
P 3900 3900
F 0 "#PWR0102" H 3900 3650 50  0001 C CNN
F 1 "GND" V 3900 3700 50  0000 C CNN
F 2 "" H 3900 3900 50  0001 C CNN
F 3 "" H 3900 3900 50  0001 C CNN
	1    3900 3900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5FD262CC
P 3900 4100
F 0 "#PWR0103" H 3900 3850 50  0001 C CNN
F 1 "GND" V 3900 3900 50  0000 C CNN
F 2 "" H 3900 4100 50  0001 C CNN
F 3 "" H 3900 4100 50  0001 C CNN
	1    3900 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FD262EB
P 6100 4000
F 0 "#PWR0105" H 6100 3750 50  0001 C CNN
F 1 "GND" V 6100 3800 50  0000 C CNN
F 2 "" H 6100 4000 50  0001 C CNN
F 3 "" H 6100 4000 50  0001 C CNN
	1    6100 4000
	0    1    1    0   
$EndComp
Text GLabel 6100 3900 0    50   Input ~ 0
OUT1
Text GLabel 6100 4100 0    50   Input ~ 0
OUT0
$Comp
L Switch:SW_SPDT SW1
U 1 1 5FD259E4
P 5000 4000
F 0 "SW1" H 5000 4285 50  0000 C CNN
F 1 "SW_SPDT" H 5000 4194 50  0000 C CNN
F 2 "Switch_Thonk:SW_SPDT_Dailywell" H 5000 4000 50  0001 C CNN
F 3 "https://www.thonk.co.uk/wp-content/uploads/2017/05/DW1-SPDT-ON-ON-2MS1T1B1M2QES.pdf" H 5000 4000 50  0001 C CNN
F 4 "Toggle Switch" H 5000 4000 50  0001 C CNN "Device"
F 5 "DW2 - SPDT ON-OFF-ON - Dailywell Sub-mini Toggle Switch" H 5000 4000 50  0001 C CNN "Description"
F 6 "No" H 5000 4000 50  0001 C CNN "Place"
F 7 "Thonk" H 5000 4000 50  0001 C CNN "Dist"
F 8 "DW2" H 5000 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.thonk.co.uk/shop/sub-mini-toggle-switches/" H 5000 4000 50  0001 C CNN "DistLink"
	1    5000 4000
	1    0    0    -1  
$EndComp
Text GLabel 5200 4100 2    50   Output ~ 0
OUT0
Text GLabel 5200 3900 2    50   Output ~ 0
OUT1
$Comp
L power:GND #PWR?
U 1 1 5FF6361E
P 3900 4000
F 0 "#PWR?" H 3900 3750 50  0001 C CNN
F 1 "GND" V 3900 3800 50  0000 C CNN
F 2 "" H 3900 4000 50  0001 C CNN
F 3 "" H 3900 4000 50  0001 C CNN
	1    3900 4000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF6362F
P 4800 4000
F 0 "#PWR?" H 4800 3750 50  0001 C CNN
F 1 "GND" V 4800 3800 50  0000 C CNN
F 2 "" H 4800 4000 50  0001 C CNN
F 3 "" H 4800 4000 50  0001 C CNN
	1    4800 4000
	0    1    1    0   
$EndComp
$EndSCHEMATC
