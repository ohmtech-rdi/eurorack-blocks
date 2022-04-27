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
L Device:R_POT RV1
U 1 1 5FCAE65B
P 4750 4100
F 0 "RV1" H 4680 4146 50  0000 R CNN
F 1 "100k" H 4680 4055 50  0000 R CNN
F 2 "Potentiometer_Thonk:SongHueiTallTrim9" H 4750 4100 50  0001 C CNN
F 3 "~" H 4750 4100 50  0001 C CNN
F 4 "Potentiometer" H 4750 4100 50  0001 C CNN "Device"
F 5 "B100K - Song Huei TALL Trimmer Potentiometer" H 4750 4100 50  0001 C CNN "Description"
F 6 "No" H 4750 4100 50  0001 C CNN "Place"
F 7 "Thonk" H 4750 4100 50  0001 C CNN "Dist"
F 8 "R0904N-B100K" H 4750 4100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.thonk.co.uk/shop/ttpots/" H 4750 4100 50  0001 C CNN "DistLink"
F 10 "erb::SongHuei9" H 4750 4100 50  0001 C CNN "Simulator"
	1    4750 4100
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60B955C8
P 4600 4100
F 0 "#PWR?" H 4600 3850 50  0001 C CNN
F 1 "GND" V 4605 3972 50  0000 R CNN
F 2 "" H 4600 4100 50  0001 C CNN
F 3 "" H 4600 4100 50  0001 C CNN
	1    4600 4100
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 60B95DAB
P 4900 4100
F 0 "#PWR?" H 4900 3950 50  0001 C CNN
F 1 "+3V3" V 4915 4228 50  0000 L CNN
F 2 "" H 4900 4100 50  0001 C CNN
F 3 "" H 4900 4100 50  0001 C CNN
	1    4900 4100
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 60B967CE
P 5950 4100
F 0 "TP1" V 5850 4250 50  0000 R CNN
F 1 "TestPoint" H 5892 4217 50  0001 R CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 6150 4100 50  0001 C CNN
F 3 "~" H 6150 4100 50  0001 C CNN
	1    5950 4100
	0    1    1    0   
$EndComp
Text GLabel 5950 4100 0    50   Input ~ 0
Pin0
Text GLabel 4750 4250 3    50   Output ~ 0
Pin0
$EndSCHEMATC
