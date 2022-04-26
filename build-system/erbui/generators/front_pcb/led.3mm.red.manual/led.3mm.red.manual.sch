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
L power:GND #PWR0101
U 1 1 5FD27361
P 5250 5050
F 0 "#PWR0101" H 5250 4800 50  0001 C CNN
F 1 "GND" V 5250 4850 50  0000 C CNN
F 2 "" H 5250 5050 50  0001 C CNN
F 3 "" H 5250 5050 50  0001 C CNN
	1    5250 5050
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 5FD62DCA
P 5100 5050
F 0 "D1" H 5092 4795 50  0000 C CNN
F 1 "LED" H 5092 4886 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 5100 5050 50  0001 C CNN
F 3 "~" H 5100 5050 50  0001 C CNN
F 4 "LED" H 5100 5050 50  0001 C CNN "Device"
F 5 "LED RED DIFFUSED T-1 T/H" H 5100 5050 50  0001 C CNN "Description"
F 6 "No" H 5100 5050 50  0001 C CNN "Place"
F 7 "Digikey" H 5100 5050 50  0001 C CNN "Dist"
F 8 "754-1606-ND" H 5100 5050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.com/en/products/detail/kingbright/WP710A10ID/2769809" H 5100 5050 50  0001 C CNN "DistLink"
F 10 "erb::Led3mm <RedLight>" H 5100 5050 50  0001 C CNN "Simulator"
	1    5100 5050
	-1   0    0    1   
$EndComp
Text GLabel 4950 5050 0    50   Input ~ 0
Pin0
$EndSCHEMATC
