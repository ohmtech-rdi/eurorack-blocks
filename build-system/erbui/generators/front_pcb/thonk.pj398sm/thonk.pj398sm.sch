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
L Connector:AudioJack2_SwitchT ZZ1
U 1 1 5FC82E98
P 3650 4200
F 0 "ZZ1" H 3654 4542 50  0000 C CNN
F 1 "IN" H 3654 4451 50  0000 C CNN
F 2 "Connector_Thonk:ThonkiconnJack" H 3650 4200 50  0001 C CNN
F 3 "~" H 3650 4200 50  0001 C CNN
F 4 "Jack Connector" H 3650 4200 50  0001 C CNN "Device"
F 5 "Thonkiconn – 3.5mm Jack Sockets" H 3650 4200 50  0001 C CNN "Description"
F 6 "No" H 3650 4200 50  0001 C CNN "Place"
F 7 "Thonk" H 3650 4200 50  0001 C CNN "Dist"
F 8 "PJ398SM" H 3650 4200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.thonk.co.uk/shop/thonkiconn/" H 3650 4200 50  0001 C CNN "DistLink"
	1    3650 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 60B90F5A
P 3850 4100
F 0 "#PWR0101" H 3850 3850 50  0001 C CNN
F 1 "GND" V 3855 3972 50  0000 R CNN
F 2 "" H 3850 4100 50  0001 C CNN
F 3 "" H 3850 4100 50  0001 C CNN
	1    3850 4100
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint Pin0
U 1 1 60B91AE3
P 4250 4200
F 0 "Pin0" V 4250 4388 50  0000 L CNN
F 1 "TestPoint" V 4295 4388 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 4450 4200 50  0001 C CNN
F 3 "~" H 4450 4200 50  0001 C CNN
	1    4250 4200
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint Cascade0
U 1 1 60B927EB
P 3850 4300
F 0 "Cascade0" V 3850 4488 50  0000 L CNN
F 1 "TestPoint" V 3895 4488 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 4050 4300 50  0001 C CNN
F 3 "~" H 4050 4300 50  0001 C CNN
	1    3850 4300
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint ZZ2
U 1 1 60BC9738
P 4250 4300
F 0 "ZZ2" V 4250 4488 50  0000 L CNN
F 1 "TestPoint" V 4295 4488 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 4450 4300 50  0001 C CNN
F 3 "~" H 4450 4300 50  0001 C CNN
	1    4250 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 4200 4250 4200
Wire Wire Line
	4250 4200 4250 4300
Connection ~ 4250 4200
$EndSCHEMATC
