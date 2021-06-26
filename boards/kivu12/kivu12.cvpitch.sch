EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 7500 7000 0    276  ~ 0
CV PITCH/ADSR
$Comp
L Device:R R76
U 1 1 5FCAD1D2
P 7050 4850
F 0 "R76" V 6843 4850 50  0000 C CNN
F 1 "4.99k" V 6934 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6980 4850 50  0001 C CNN
F 3 "~" H 7050 4850 50  0001 C CNN
F 4 "Resistor" H 7050 4850 50  0001 C CNN "Device"
F 5 "RES SMD 4.99K OHM 1% 1/10W 0603" H 7050 4850 50  0001 C CNN "Description"
F 6 "Yes" H 7050 4850 50  0001 C CNN "Place"
F 7 "Digikey" H 7050 4850 50  0001 C CNN "Dist"
F 8 "P4.99KHCT-ND" H 7050 4850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/panasonic-electronic-components/ERJ-3EKF4991V/P4-99KHCT-ND/198373" H 7050 4850 50  0001 C CNN "DistLink"
	1    7050 4850
	0    1    1    0   
$EndComp
$Comp
L Reference_Voltage:LM4040DBZ-5 D22
U 1 1 5FCAD41B
P 7300 5000
F 0 "D22" V 7254 5079 50  0000 L CNN
F 1 "LM4040DBZ-5" V 7345 5079 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7300 4800 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm4040-n.pdf" H 7300 5000 50  0001 C CIN
F 4 "Voltage Reference" H 7300 5000 50  0001 C CNN "Device"
F 5 "IC VREF SHUNT 0.2% SOT23-3" H 7300 5000 50  0001 C CNN "Description"
F 6 "Yes" H 7300 5000 50  0001 C CNN "Place"
F 7 "Digikey" H 7300 5000 50  0001 C CNN "Dist"
F 8 "LM4040BIM3-5.0/NOPBCT-ND" H 7300 5000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/LM4040BIM3-5-0-NOPB/LM4040BIM3-5-0-NOPBCT-ND/212696" H 7300 5000 50  0001 C CNN "DistLink"
	1    7300 5000
	0    1    1    0   
$EndComp
$Comp
L Device:C C13
U 1 1 5FCAD62F
P 8100 5000
F 0 "C13" H 7900 4950 50  0000 C CNN
F 1 "1u" H 7900 5050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8138 4850 50  0001 C CNN
F 3 "~" H 8100 5000 50  0001 C CNN
F 4 "Ceramic Capacitor" H 8100 5000 50  0001 C CNN "Device"
F 5 "CAP CER 1UF 35V X7R 0603" H 8100 5000 50  0001 C CNN "Description"
F 6 "Yes" H 8100 5000 50  0001 C CNN "Place"
F 7 "Digikey" H 8100 5000 50  0001 C CNN "Dist"
F 8 "445-7414-1-ND" H 8100 5000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/tdk-corporation/C1608X7R1V105K080AC/445-7414-1-ND/2733486" H 8100 5000 50  0001 C CNN "DistLink"
	1    8100 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 4850 7300 4850
Connection ~ 7300 4850
Wire Wire Line
	7300 4850 8100 4850
Connection ~ 8100 4850
Wire Wire Line
	8100 4850 8400 4850
Text Label 8400 4850 2    50   ~ 0
VREF-5
$Comp
L Amplifier_Operational:TL072 U9
U 1 1 5FC92B57
P 3850 3100
F 0 "U9" H 3900 3400 50  0000 C CNN
F 1 "TL072" H 3900 3300 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3850 3100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 3850 3100 50  0001 C CNN
F 4 "Op Amp" H 3850 3100 50  0001 C CNN "Device"
F 5 "IC OPAMP JFET 2 CIRCUIT 8SOIC" H 3850 3100 50  0001 C CNN "Description"
F 6 "Yes" H 3850 3100 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 3100 50  0001 C CNN "Dist"
F 8 "296-1282-1-ND" H 3850 3100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/TL072CDR/296-1282-1-ND/404930" H 3850 3100 50  0001 C CNN "DistLink"
	1    3850 3100
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U9
U 2 1 5FC92BCC
P 3850 4800
F 0 "U9" H 3900 5100 50  0000 C CNN
F 1 "TL072" H 3900 5000 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3850 4800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 3850 4800 50  0001 C CNN
	2    3850 4800
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U9
U 3 1 5FC92C2F
P 7400 2950
F 0 "U9" H 7358 2996 50  0000 L CNN
F 1 "TL072" H 7358 2905 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7400 2950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 7400 2950 50  0001 C CNN
	3    7400 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5FC94671
P 7800 2700
F 0 "C11" H 7915 2746 50  0000 L CNN
F 1 "100n" H 7915 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7838 2550 50  0001 C CNN
F 3 "~" H 7800 2700 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7800 2700 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 7800 2700 50  0001 C CNN "Description"
F 6 "Yes" H 7800 2700 50  0001 C CNN "Place"
F 7 "Digikey" H 7800 2700 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 7800 2700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/avx-corporation/06033C104KAT4A/478-7018-1-ND/3247565" H 7800 2700 50  0001 C CNN "DistLink"
	1    7800 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2450 7300 2550
Wire Wire Line
	7300 2550 7800 2550
Connection ~ 7300 2550
Wire Wire Line
	7300 2550 7300 2650
Wire Wire Line
	7800 2850 7800 2950
Wire Wire Line
	7300 3250 7300 3350
Wire Wire Line
	7300 3350 7800 3350
Connection ~ 7300 3350
Wire Wire Line
	7300 3350 7300 3450
Wire Wire Line
	7800 2950 8100 2950
Connection ~ 7800 2950
Wire Wire Line
	7800 2950 7800 3050
$Comp
L Device:C C12
U 1 1 5FCA8BA7
P 7800 3200
F 0 "C12" H 7915 3246 50  0000 L CNN
F 1 "100n" H 7915 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7838 3050 50  0001 C CNN
F 3 "~" H 7800 3200 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7800 3200 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 7800 3200 50  0001 C CNN "Description"
F 6 "Yes" H 7800 3200 50  0001 C CNN "Place"
F 7 "Digikey" H 7800 3200 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 7800 3200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/avx-corporation/06033C104KAT4A/478-7018-1-ND/3247565" H 7800 3200 50  0001 C CNN "DistLink"
	1    7800 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R69
U 1 1 608EFA92
P 3000 3000
F 0 "R69" V 2793 3000 50  0000 C CNN
F 1 "100k" V 2884 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2930 3000 50  0001 C CNN
F 3 "~" H 3000 3000 50  0001 C CNN
F 4 "Resistor" H 3000 3000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3000 3000 50  0001 C CNN "Description"
F 6 "Yes" H 3000 3000 50  0001 C CNN "Place"
F 7 "Digikey" H 3000 3000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3000 3000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3000 3000 50  0001 C CNN "DistLink"
	1    3000 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3000 3250 3000
Wire Wire Line
	3250 2650 3150 2650
Connection ~ 3250 3000
Text Label 2850 2650 2    50   ~ 0
VREF-5
$Comp
L Device:R R68
U 1 1 608EFACE
P 3000 2650
F 0 "R68" V 2793 2650 50  0000 C CNN
F 1 "100k" V 2884 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2930 2650 50  0001 C CNN
F 3 "~" H 3000 2650 50  0001 C CNN
F 4 "Resistor" H 3000 2650 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3000 2650 50  0001 C CNN "Description"
F 6 "Yes" H 3000 2650 50  0001 C CNN "Place"
F 7 "Digikey" H 3000 2650 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3000 2650 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3000 2650 50  0001 C CNN "DistLink"
	1    3000 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R71
U 1 1 608EFADA
P 3900 3400
F 0 "R71" V 4000 3400 50  0000 C CNN
F 1 "100k" V 4100 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3830 3400 50  0001 C CNN
F 3 "~" H 3900 3400 50  0001 C CNN
F 4 "Resistor" H 3900 3400 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3900 3400 50  0001 C CNN "Description"
F 6 "Yes" H 3900 3400 50  0001 C CNN "Place"
F 7 "Digikey" H 3900 3400 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3900 3400 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3900 3400 50  0001 C CNN "DistLink"
	1    3900 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 3000 3550 3000
$Comp
L Device:R R70
U 1 1 608F6E3C
P 3550 3550
F 0 "R70" H 3450 3600 50  0000 R CNN
F 1 "100k" H 3450 3500 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3480 3550 50  0001 C CNN
F 3 "~" H 3550 3550 50  0001 C CNN
F 4 "Resistor" H 3550 3550 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3550 3550 50  0001 C CNN "Description"
F 6 "Yes" H 3550 3550 50  0001 C CNN "Place"
F 7 "Digikey" H 3550 3550 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3550 3550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3550 3550 50  0001 C CNN "DistLink"
	1    3550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3000 3250 2650
Text HLabel 2850 3000 0    50   Input ~ 0
IN1
Text HLabel 3550 3700 3    50   Input ~ 0
GND
Wire Wire Line
	3550 3200 3550 3400
Wire Wire Line
	3550 3400 3750 3400
Connection ~ 3550 3400
Wire Wire Line
	4150 3100 4150 3400
Wire Wire Line
	4150 3400 4050 3400
Text HLabel 4400 3200 3    50   Output ~ 0
OUT1
Text HLabel 7300 3450 3    50   Input ~ 0
-12V
Text HLabel 7300 2450 1    50   Input ~ 0
+12V
Text HLabel 8100 2950 2    50   Input ~ 0
GND
$Comp
L Device:Jumper_NC_Dual JP3
U 1 1 609044D2
P 4400 3100
F 0 "JP3" H 4400 3339 50  0000 C CNN
F 1 "Jumper" H 4400 3248 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4400 3100 50  0001 C CNN
F 3 "~" H 4400 3100 50  0001 C CNN
	1    4400 3100
	1    0    0    -1  
$EndComp
Connection ~ 4150 3100
Text HLabel 4650 3100 2    50   Input ~ 0
IN1
Text Notes 2700 2050 0    50   ~ 0
TL072 common-mode voltage range is -8V to 12V
$Comp
L Device:R R73
U 1 1 609169CE
P 3000 4700
F 0 "R73" V 2793 4700 50  0000 C CNN
F 1 "100k" V 2884 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2930 4700 50  0001 C CNN
F 3 "~" H 3000 4700 50  0001 C CNN
F 4 "Resistor" H 3000 4700 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3000 4700 50  0001 C CNN "Description"
F 6 "Yes" H 3000 4700 50  0001 C CNN "Place"
F 7 "Digikey" H 3000 4700 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3000 4700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3000 4700 50  0001 C CNN "DistLink"
	1    3000 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 4700 3250 4700
Wire Wire Line
	3250 4350 3150 4350
Connection ~ 3250 4700
Text Label 2850 4350 2    50   ~ 0
VREF-5
$Comp
L Device:R R72
U 1 1 609169DE
P 3000 4350
F 0 "R72" V 2793 4350 50  0000 C CNN
F 1 "100k" V 2884 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2930 4350 50  0001 C CNN
F 3 "~" H 3000 4350 50  0001 C CNN
F 4 "Resistor" H 3000 4350 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3000 4350 50  0001 C CNN "Description"
F 6 "Yes" H 3000 4350 50  0001 C CNN "Place"
F 7 "Digikey" H 3000 4350 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3000 4350 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3000 4350 50  0001 C CNN "DistLink"
	1    3000 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R R75
U 1 1 609169EA
P 3900 5100
F 0 "R75" V 4000 5100 50  0000 C CNN
F 1 "100k" V 4100 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3830 5100 50  0001 C CNN
F 3 "~" H 3900 5100 50  0001 C CNN
F 4 "Resistor" H 3900 5100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3900 5100 50  0001 C CNN "Description"
F 6 "Yes" H 3900 5100 50  0001 C CNN "Place"
F 7 "Digikey" H 3900 5100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3900 5100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3900 5100 50  0001 C CNN "DistLink"
	1    3900 5100
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 4700 3550 4700
$Comp
L Device:R R74
U 1 1 609169F7
P 3550 5250
F 0 "R74" H 3450 5300 50  0000 R CNN
F 1 "100k" H 3450 5200 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3480 5250 50  0001 C CNN
F 3 "~" H 3550 5250 50  0001 C CNN
F 4 "Resistor" H 3550 5250 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3550 5250 50  0001 C CNN "Description"
F 6 "Yes" H 3550 5250 50  0001 C CNN "Place"
F 7 "Digikey" H 3550 5250 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3550 5250 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3550 5250 50  0001 C CNN "DistLink"
	1    3550 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 4700 3250 4350
Text HLabel 2850 4700 0    50   Input ~ 0
IN2
Text HLabel 3550 5400 3    50   Input ~ 0
GND
Wire Wire Line
	3550 4900 3550 5100
Wire Wire Line
	3550 5100 3750 5100
Connection ~ 3550 5100
Wire Wire Line
	4150 4800 4150 5100
Wire Wire Line
	4150 5100 4050 5100
Text HLabel 4400 4900 3    50   Output ~ 0
OUT2
$Comp
L Device:Jumper_NC_Dual JP4
U 1 1 60916A06
P 4400 4800
F 0 "JP4" H 4400 5039 50  0000 C CNN
F 1 "Jumper" H 4400 4948 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4400 4800 50  0001 C CNN
F 3 "~" H 4400 4800 50  0001 C CNN
	1    4400 4800
	1    0    0    -1  
$EndComp
Text HLabel 4650 4800 2    50   Input ~ 0
IN2
Connection ~ 4150 4800
Text HLabel 6900 4850 0    50   Input ~ 0
-12V
Text HLabel 7300 5150 3    50   Input ~ 0
GND
Text HLabel 8100 5150 3    50   Input ~ 0
GND
Text Notes 4050 4050 0    50   ~ 0
OUT1 = (IN1+VREFm5)/2 * (1 + R71/R70)\n      = IN1 + VREFm5
$EndSCHEMATC
