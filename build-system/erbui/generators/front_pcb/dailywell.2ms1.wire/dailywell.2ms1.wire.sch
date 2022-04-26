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
L Switch:SW_SPDT SW1
U 1 1 5FD259E4
P 5000 4700
F 0 "SW1" H 5000 4985 50  0000 C CNN
F 1 "SW_SPDT" H 5000 4894 50  0000 C CNN
F 2 "Switch_Thonk:SW_SPDT_Dailywell" H 5000 4700 50  0001 C CNN
F 3 "https://www.thonk.co.uk/wp-content/uploads/2017/05/DW1-SPDT-ON-ON-2MS1T1B1M2QES.pdf" H 5000 4700 50  0001 C CNN
F 4 "Toggle Switch" H 5000 4700 50  0001 C CNN "Device"
F 5 "DW1 - SPDT ON-ON - Dailywell Sub-mini Toggle Switch" H 5000 4700 50  0001 C CNN "Description"
F 6 "No" H 5000 4700 50  0001 C CNN "Place"
F 7 "Thonk" H 5000 4700 50  0001 C CNN "Dist"
F 8 "DW1" H 5000 4700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.thonk.co.uk/shop/sub-mini-toggle-switches/" H 5000 4700 50  0001 C CNN "DistLink"
F 10 "erb::Dailywell2Ms1" H 5000 4700 50  0001 C CNN "Simulator"
	1    5000 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 60B938C9
P 4800 4700
F 0 "#PWR?" H 4800 4550 50  0001 C CNN
F 1 "+3V3" V 4815 4828 50  0000 L CNN
F 2 "" H 4800 4700 50  0001 C CNN
F 3 "" H 4800 4700 50  0001 C CNN
	1    4800 4700
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 60B942BC
P 5950 4600
F 0 "TP1" V 5950 4788 50  0000 L CNN
F 1 "TestPoint" V 5995 4788 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 6150 4600 50  0001 C CNN
F 3 "~" H 6150 4600 50  0001 C CNN
	1    5950 4600
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 60B947FF
P 5950 4800
F 0 "TP2" V 5950 4988 50  0000 L CNN
F 1 "TestPoint" V 5995 4988 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 6150 4800 50  0001 C CNN
F 3 "~" H 6150 4800 50  0001 C CNN
	1    5950 4800
	0    1    1    0   
$EndComp
Text GLabel 5950 4600 0    50   Input ~ 0
Pin0
Text GLabel 5950 4800 0    50   Input ~ 0
Pin1
Text GLabel 5200 4600 2    50   Output ~ 0
Pin0
Text GLabel 5200 4800 2    50   Output ~ 0
Pin1
$EndSCHEMATC
