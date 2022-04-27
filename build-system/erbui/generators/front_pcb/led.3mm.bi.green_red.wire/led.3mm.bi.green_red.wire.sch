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
L Device:LED_Dual_ACA D1
U 1 1 5FD639C8
P 5100 4700
F 0 "D1" H 5100 5125 50  0000 C CNN
F 1 "LED_Dual_ACA" H 5100 5034 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm-3" H 5100 4700 50  0001 C CNN
F 3 "~" H 5100 4700 50  0001 C CNN
F 4 "LED" H 5100 4700 50  0001 C CNN "Device"
F 5 "LED GREEN/RED DIFFUSED T-1 T/H" H 5100 4700 50  0001 C CNN "Description"
F 6 "No" H 5100 4700 50  0001 C CNN "Place"
F 7 "Digikey" H 5100 4700 50  0001 C CNN "Dist"
F 8 "754-1221-ND" H 5100 4700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kingbright/WP3VEGW/754-1221-ND/1747620" H 5100 4700 50  0001 C CNN "DistLink"
F 10 "erb::Led3mm <GreenRedLight>" H 5100 4700 50  0001 C CNN "Simulator"
	1    5100 4700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5FD63BA1
P 5500 4700
F 0 "#PWR0105" H 5500 4450 50  0001 C CNN
F 1 "GND" V 5500 4500 50  0000 C CNN
F 2 "" H 5500 4700 50  0001 C CNN
F 3 "" H 5500 4700 50  0001 C CNN
	1    5500 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 4700 5500 4700
$Comp
L Connector:TestPoint TP1
U 1 1 60B93D2A
P 4050 4600
F 0 "TP1" V 4050 4850 50  0000 C CNN
F 1 "TestPoint" V 4154 4672 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 4250 4600 50  0001 C CNN
F 3 "~" H 4250 4600 50  0001 C CNN
	1    4050 4600
	0    -1   -1   0   
$EndComp
$Comp
L Connector:TestPoint TP2
U 1 1 60B94B75
P 4050 4800
F 0 "TP2" V 4050 5050 50  0000 C CNN
F 1 "TestPoint" V 4154 4872 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 4250 4800 50  0001 C CNN
F 3 "~" H 4250 4800 50  0001 C CNN
	1    4050 4800
	0    -1   -1   0   
$EndComp
Text GLabel 4800 4600 0    50   Input ~ 0
Pin0
Text GLabel 4800 4800 0    50   Input ~ 0
Pin1
Text GLabel 4050 4600 2    50   Output ~ 0
Pin0
Text GLabel 4050 4800 2    50   Output ~ 0
Pin1
$EndSCHEMATC
