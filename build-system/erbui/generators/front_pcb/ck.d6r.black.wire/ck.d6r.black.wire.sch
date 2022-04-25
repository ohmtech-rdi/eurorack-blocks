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
L Switch:SW_Push SW1
U 1 1 5FD27819
P 4700 5300
F 0 "SW1" H 4700 5585 50  0000 C CNN
F 1 "SW_Push_Dual" H 4700 5494 50  0000 C CNN
F 2 "Switch_Thonk:SW_SPST_CKD6R" H 4700 5500 50  0001 C CNN
F 3 "" H 4700 5500 50  0001 C CNN
F 4 "Tactile Switch" H 4700 5300 50  0001 C CNN "Device"
F 5 "C&K TACTILE SWITCH" H 4700 5300 50  0001 C CNN "Description"
F 6 "No" H 4700 5300 50  0001 C CNN "Place"
F 7 "Thonk" H 4700 5300 50  0001 C CNN "Dist"
F 8 "https://www.thonk.co.uk/shop/radio-music-switch/" H 4700 5300 50  0001 C CNN "DistLink"
F 9 "Choose Black" H 4700 5300 50  0001 C CNN "Remarks"
	1    4700 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 60B97257
P 4500 5300
F 0 "#PWR?" H 4500 5150 50  0001 C CNN
F 1 "+3V3" V 4515 5428 50  0000 L CNN
F 2 "" H 4500 5300 50  0001 C CNN
F 3 "" H 4500 5300 50  0001 C CNN
	1    4500 5300
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 60B97905
P 5600 5300
F 0 "TP1" V 5600 5488 50  0000 L CNN
F 1 "TestPoint" V 5645 5488 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 5800 5300 50  0001 C CNN
F 3 "~" H 5800 5300 50  0001 C CNN
	1    5600 5300
	0    1    1    0   
$EndComp
Text GLabel 4900 5300 2    50   Output ~ 0
Pin0
Text GLabel 5600 5300 0    50   Input ~ 0
Pin0
$EndSCHEMATC
