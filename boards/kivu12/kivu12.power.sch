EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 8
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
L Connector_Generic:Conn_02x05_Odd_Even J5
U 1 1 6095C792
P 4850 3450
F 0 "J5" H 4900 3867 50  0000 C CNN
F 1 "POWER BUS" H 4900 3776 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 4850 3450 50  0001 C CNN
F 3 "~" H 4850 3450 50  0001 C CNN
F 4 "IDC Header" H 4850 3450 50  0001 C CNN "Device"
F 5 "CONN HEADER VERT 10POS 2.54MM" H 4850 3450 50  0001 C CNN "Description"
F 6 "No" H 4850 3450 50  0001 C CNN "Place"
F 7 "Digikey" H 4850 3450 50  0001 C CNN "Dist"
F 8 "732-2094-ND" H 4850 3450 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/würth-elektronik/61201021621/732-2094-ND/2060590" H 4850 3450 50  0001 C CNN "DistLink"
	1    4850 3450
	1    0    0    -1  
$EndComp
Text HLabel 5150 3350 2    50   Output ~ 0
GND
Text HLabel 5150 3450 2    50   Output ~ 0
GND
Text HLabel 5150 3550 2    50   Output ~ 0
GND
Text HLabel 4650 3350 0    50   Output ~ 0
GND
Text HLabel 4650 3450 0    50   Output ~ 0
GND
Text HLabel 4650 3550 0    50   Output ~ 0
GND
Text HLabel 7350 3900 3    50   Output ~ 0
-12V
Text HLabel 7350 2900 1    50   Output ~ 0
+12V
$Comp
L Device:C C1
U 1 1 6095DF4D
P 7350 3650
F 0 "C1" H 7465 3696 50  0000 L CNN
F 1 "10u" H 7465 3605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7388 3500 50  0001 C CNN
F 3 "~" H 7350 3650 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7350 3650 50  0001 C CNN "Device"
F 5 "CAP CER 10UF 25V X5R 0805" H 7350 3650 50  0001 C CNN "Description"
F 6 "Yes" H 7350 3650 50  0001 C CNN "Place"
F 7 "Digikey" H 7350 3650 50  0001 C CNN "Dist"
F 8 "1276-2891-1-ND" H 7350 3650 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/samsung-electro-mechanics/CL21A106KAYNNNE/1276-2891-1-ND/3890977" H 7350 3650 50  0001 C CNN "DistLink"
	1    7350 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6095F9C0
P 7350 3150
F 0 "C2" H 7465 3196 50  0000 L CNN
F 1 "10u" H 7465 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7388 3000 50  0001 C CNN
F 3 "~" H 7350 3150 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7350 3150 50  0001 C CNN "Device"
F 5 "CAP CER 10UF 25V X5R 0805" H 7350 3150 50  0001 C CNN "Description"
F 6 "Yes" H 7350 3150 50  0001 C CNN "Place"
F 7 "Digikey" H 7350 3150 50  0001 C CNN "Dist"
F 8 "1276-2891-1-ND" H 7350 3150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/samsung-electro-mechanics/CL21A106KAYNNNE/1276-2891-1-ND/3890977" H 7350 3150 50  0001 C CNN "DistLink"
	1    7350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3000 7350 2900
Wire Wire Line
	7350 3300 7350 3400
Wire Wire Line
	7350 3400 7450 3400
Connection ~ 7350 3400
Wire Wire Line
	7350 3400 7350 3500
Wire Wire Line
	7350 3800 7350 3900
Text HLabel 7450 3400 2    50   Output ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
POWER
Text HLabel 4650 3250 0    50   Output ~ 0
-12V
Text HLabel 5150 3250 2    50   Output ~ 0
-12V
Text HLabel 5150 3650 2    50   Output ~ 0
+12V
Text HLabel 4650 3650 0    50   Output ~ 0
+12V
$EndSCHEMATC
