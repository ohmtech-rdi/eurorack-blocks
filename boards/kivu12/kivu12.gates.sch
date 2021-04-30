EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
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
L 4xxx:4051 U?
U 1 1 6095DE74
P 9100 2150
AR Path="/6095DE74" Ref="U?"  Part="1" 
AR Path="/6093B89C/6095DE74" Ref="U?"  Part="1" 
AR Path="/60958BFE/6095DE74" Ref="U3"  Part="1" 
F 0 "U3" H 9500 1950 50  0000 L CNN
F 1 "4051" H 9500 1850 50  0000 L CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 9100 2150 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 9100 2150 50  0001 C CNN
F 4 "Multiplexer" H 9100 2150 50  0001 C CNN "Device"
F 5 "IC MUX/DEMUX 8X1 16TSSOP" H 9100 2150 50  0001 C CNN "Description"
F 6 "Yes" H 9100 2150 50  0001 C CNN "Place"
F 7 "Digikey" H 9100 2150 50  0001 C CNN "Dist"
F 8 "296-11993-1-ND" H 9100 2150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/CD4051BPWR/296-11993-1-ND/390442" H 9100 2150 50  0001 C CNN "DistLink"
	1    9100 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6095DE98
P 9950 2650
AR Path="/6095DE98" Ref="C?"  Part="1" 
AR Path="/6093B89C/6095DE98" Ref="C?"  Part="1" 
AR Path="/60958BFE/6095DE98" Ref="C5"  Part="1" 
F 0 "C5" H 9750 2600 50  0000 C CNN
F 1 "100n" H 9750 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9988 2500 50  0001 C CNN
F 3 "~" H 9950 2650 50  0001 C CNN
F 4 "Ceramic Capacitor" H 9950 2650 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 9950 2650 50  0001 C CNN "Description"
F 6 "Yes" H 9950 2650 50  0001 C CNN "Place"
F 7 "Digikey" H 9950 2650 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 9950 2650 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 9950 2650 50  0001 C CNN "DistLink"
	1    9950 2650
	-1   0    0    1   
$EndComp
Text Notes 900  5300 0    50   ~ 0
Inputs are potentially\nfrom -12V to 12V.\n\nAt the output of first stage,\nfrom 0V to 12V.
Text HLabel 8600 2550 0    50   Input ~ 0
A
Text HLabel 8600 2650 0    50   Input ~ 0
B
Text HLabel 8600 2750 0    50   Input ~ 0
C
Text HLabel 9900 1350 2    50   Output ~ 0
~OUT3~
$Comp
L Device:R R?
U 1 1 6096182B
P 9900 1200
AR Path="/6096182B" Ref="R?"  Part="1" 
AR Path="/60958BFE/6096182B" Ref="R1"  Part="1" 
F 0 "R1" H 10050 1250 50  0000 C CNN
F 1 "10k" H 10050 1150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9830 1200 50  0001 C CNN
F 3 "~" H 9900 1200 50  0001 C CNN
F 4 "Resistor" H 9900 1200 50  0001 C CNN "Device"
F 5 "RES SMD 10K OHM 1% 1/10W 0603" H 9900 1200 50  0001 C CNN "Description"
F 6 "Yes" H 9900 1200 50  0001 C CNN "Place"
F 7 "Digikey" H 9900 1200 50  0001 C CNN "Dist"
F 8 "311-10KLDCT-ND" H 9900 1200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-0710KL/311-10KLDCT-ND/2828135" H 9900 1200 50  0001 C CNN "DistLink"
	1    9900 1200
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q?
U 1 1 60961843
P 9800 1550
AR Path="/60961843" Ref="Q?"  Part="1" 
AR Path="/60958BFE/60961843" Ref="Q1"  Part="1" 
F 0 "Q1" H 9991 1596 50  0000 L CNN
F 1 "MMBT3904" H 9991 1505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10000 1475 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9800 1550 50  0001 L CNN
F 4 "Bipolar Transistor" H 9800 1550 50  0001 C CNN "Device"
F 5 "TRANS NPN 40V 0.2A SOT23" H 9800 1550 50  0001 C CNN "Description"
F 6 "Yes" H 9800 1550 50  0001 C CNN "Place"
F 7 "Digikey" H 9800 1550 50  0001 C CNN "Dist"
F 8 "MMBT3904LT3GOSCT-ND" H 9800 1550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/MMBT3904LT3G/MMBT3904LT3GOSCT-ND/1139814" H 9800 1550 50  0001 C CNN "DistLink"
	1    9800 1550
	1    0    0    -1  
$EndComp
Text HLabel 9100 1250 1    50   Input ~ 0
12V
Text HLabel 9100 3050 3    50   Input ~ 0
GND
Text HLabel 9200 3050 3    50   Input ~ 0
GND
Text HLabel 8600 2450 0    50   Input ~ 0
GND
Text HLabel 9900 1750 3    50   Input ~ 0
GND
Text HLabel 9950 2500 1    50   Input ~ 0
12V
Text HLabel 9900 1050 1    50   Input ~ 0
3V3
Text Label 8600 1750 2    50   ~ 0
IN1_POS
Text HLabel 9950 2800 3    50   Input ~ 0
GND
Text Notes 6800 5650 0    50   ~ 0
Outputs are inverted\nand from 0V to 3V3
Text Label 8600 1650 2    50   ~ 0
IN2_POS
Text Label 8600 1550 2    50   ~ 0
IN3_POS
Text Label 8600 1850 2    50   ~ 0
IN4_POS
Text Label 8600 1950 2    50   ~ 0
IN5_POS
Text Label 8600 2150 2    50   ~ 0
IN6_POS
Text Label 8600 2250 2    50   ~ 0
IN7_POS
Text Label 8600 2050 2    50   ~ 0
IN8_POS
Text Label 1850 1000 2    50   ~ 0
IN1_POS
Connection ~ 1400 1000
Wire Wire Line
	1400 1000 1850 1000
Text HLabel 1850 1300 3    50   Input ~ 0
GND
Text HLabel 1400 1300 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 6096184F
P 1400 1150
AR Path="/6096184F" Ref="D?"  Part="1" 
AR Path="/60958BFE/6096184F" Ref="D1"  Part="1" 
F 0 "D1" V 1354 1229 50  0000 L CNN
F 1 "1N4148" V 1445 1229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 1400 975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 1400 1150 50  0001 C CNN
F 4 "Rectifier Diode" H 1400 1150 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 1400 1150 50  0001 C CNN "Description"
F 6 "Yes" H 1400 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 1400 1150 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 1400 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 1400 1150 50  0001 C CNN "DistLink"
	1    1400 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60961837
P 1850 1150
AR Path="/60961837" Ref="R?"  Part="1" 
AR Path="/60958BFE/60961837" Ref="R9"  Part="1" 
F 0 "R9" H 1700 1100 50  0000 C CNN
F 1 "100k" H 1650 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1780 1150 50  0001 C CNN
F 3 "~" H 1850 1150 50  0001 C CNN
F 4 "Resistor" H 1850 1150 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1850 1150 50  0001 C CNN "Description"
F 6 "Yes" H 1850 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 1850 1150 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1850 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1850 1150 50  0001 C CNN "DistLink"
	1    1850 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 6096181F
P 1250 1000
AR Path="/6096181F" Ref="R?"  Part="1" 
AR Path="/60958BFE/6096181F" Ref="R4"  Part="1" 
F 0 "R4" V 1043 1000 50  0000 C CNN
F 1 "100k" V 1134 1000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1180 1000 50  0001 C CNN
F 3 "~" H 1250 1000 50  0001 C CNN
F 4 "Resistor" H 1250 1000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1250 1000 50  0001 C CNN "Description"
F 6 "Yes" H 1250 1000 50  0001 C CNN "Place"
F 7 "Digikey" H 1250 1000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1250 1000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1250 1000 50  0001 C CNN "DistLink"
	1    1250 1000
	0    1    1    0   
$EndComp
Text HLabel 1100 1000 0    50   Input ~ 0
IN1
Text Label 3150 1000 2    50   ~ 0
IN2_POS
Connection ~ 2700 1000
Wire Wire Line
	2700 1000 3150 1000
Text HLabel 3150 1300 3    50   Input ~ 0
GND
Text HLabel 2700 1300 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609C3B06
P 2700 1150
AR Path="/609C3B06" Ref="D?"  Part="1" 
AR Path="/60958BFE/609C3B06" Ref="D2"  Part="1" 
F 0 "D2" V 2654 1229 50  0000 L CNN
F 1 "1N4148" V 2745 1229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 2700 975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 2700 1150 50  0001 C CNN
F 4 "Rectifier Diode" H 2700 1150 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 2700 1150 50  0001 C CNN "Description"
F 6 "Yes" H 2700 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 2700 1150 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 2700 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 2700 1150 50  0001 C CNN "DistLink"
	1    2700 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609C3B12
P 3150 1150
AR Path="/609C3B12" Ref="R?"  Part="1" 
AR Path="/60958BFE/609C3B12" Ref="R10"  Part="1" 
F 0 "R10" H 3000 1100 50  0000 C CNN
F 1 "100k" H 2950 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 1150 50  0001 C CNN
F 3 "~" H 3150 1150 50  0001 C CNN
F 4 "Resistor" H 3150 1150 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3150 1150 50  0001 C CNN "Description"
F 6 "Yes" H 3150 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 3150 1150 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3150 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3150 1150 50  0001 C CNN "DistLink"
	1    3150 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609C3B1E
P 2550 1000
AR Path="/609C3B1E" Ref="R?"  Part="1" 
AR Path="/60958BFE/609C3B1E" Ref="R5"  Part="1" 
F 0 "R5" V 2343 1000 50  0000 C CNN
F 1 "100k" V 2434 1000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 1000 50  0001 C CNN
F 3 "~" H 2550 1000 50  0001 C CNN
F 4 "Resistor" H 2550 1000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 2550 1000 50  0001 C CNN "Description"
F 6 "Yes" H 2550 1000 50  0001 C CNN "Place"
F 7 "Digikey" H 2550 1000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 2550 1000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 2550 1000 50  0001 C CNN "DistLink"
	1    2550 1000
	0    1    1    0   
$EndComp
Text HLabel 2400 1000 0    50   Input ~ 0
IN2
Text Label 4450 1000 2    50   ~ 0
IN3_POS
Connection ~ 4000 1000
Wire Wire Line
	4000 1000 4450 1000
Text HLabel 4450 1300 3    50   Input ~ 0
GND
Text HLabel 4000 1300 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609C6E6C
P 4000 1150
AR Path="/609C6E6C" Ref="D?"  Part="1" 
AR Path="/60958BFE/609C6E6C" Ref="D3"  Part="1" 
F 0 "D3" V 3954 1229 50  0000 L CNN
F 1 "1N4148" V 4045 1229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 4000 975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 1150 50  0001 C CNN
F 4 "Rectifier Diode" H 4000 1150 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 4000 1150 50  0001 C CNN "Description"
F 6 "Yes" H 4000 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 4000 1150 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 4000 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 4000 1150 50  0001 C CNN "DistLink"
	1    4000 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609C6E78
P 4450 1150
AR Path="/609C6E78" Ref="R?"  Part="1" 
AR Path="/60958BFE/609C6E78" Ref="R11"  Part="1" 
F 0 "R11" H 4300 1100 50  0000 C CNN
F 1 "100k" H 4250 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 1150 50  0001 C CNN
F 3 "~" H 4450 1150 50  0001 C CNN
F 4 "Resistor" H 4450 1150 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 4450 1150 50  0001 C CNN "Description"
F 6 "Yes" H 4450 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 4450 1150 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 4450 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 4450 1150 50  0001 C CNN "DistLink"
	1    4450 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609C6E84
P 3850 1000
AR Path="/609C6E84" Ref="R?"  Part="1" 
AR Path="/60958BFE/609C6E84" Ref="R6"  Part="1" 
F 0 "R6" V 3643 1000 50  0000 C CNN
F 1 "100k" V 3734 1000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 1000 50  0001 C CNN
F 3 "~" H 3850 1000 50  0001 C CNN
F 4 "Resistor" H 3850 1000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3850 1000 50  0001 C CNN "Description"
F 6 "Yes" H 3850 1000 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 1000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3850 1000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3850 1000 50  0001 C CNN "DistLink"
	1    3850 1000
	0    1    1    0   
$EndComp
Text HLabel 3700 1000 0    50   Input ~ 0
IN3
Text Label 5800 1000 2    50   ~ 0
IN4_POS
Connection ~ 5350 1000
Wire Wire Line
	5350 1000 5800 1000
Text HLabel 5800 1300 3    50   Input ~ 0
GND
Text HLabel 5350 1300 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609CA3D3
P 5350 1150
AR Path="/609CA3D3" Ref="D?"  Part="1" 
AR Path="/60958BFE/609CA3D3" Ref="D4"  Part="1" 
F 0 "D4" V 5304 1229 50  0000 L CNN
F 1 "1N4148" V 5395 1229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 5350 975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5350 1150 50  0001 C CNN
F 4 "Rectifier Diode" H 5350 1150 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 5350 1150 50  0001 C CNN "Description"
F 6 "Yes" H 5350 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 5350 1150 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 5350 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 5350 1150 50  0001 C CNN "DistLink"
	1    5350 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609CA3DF
P 5800 1150
AR Path="/609CA3DF" Ref="R?"  Part="1" 
AR Path="/60958BFE/609CA3DF" Ref="R12"  Part="1" 
F 0 "R12" H 5650 1100 50  0000 C CNN
F 1 "100k" H 5600 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 1150 50  0001 C CNN
F 3 "~" H 5800 1150 50  0001 C CNN
F 4 "Resistor" H 5800 1150 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5800 1150 50  0001 C CNN "Description"
F 6 "Yes" H 5800 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 5800 1150 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5800 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5800 1150 50  0001 C CNN "DistLink"
	1    5800 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609CA3EB
P 5200 1000
AR Path="/609CA3EB" Ref="R?"  Part="1" 
AR Path="/60958BFE/609CA3EB" Ref="R7"  Part="1" 
F 0 "R7" V 4993 1000 50  0000 C CNN
F 1 "100k" V 5084 1000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 1000 50  0001 C CNN
F 3 "~" H 5200 1000 50  0001 C CNN
F 4 "Resistor" H 5200 1000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5200 1000 50  0001 C CNN "Description"
F 6 "Yes" H 5200 1000 50  0001 C CNN "Place"
F 7 "Digikey" H 5200 1000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5200 1000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5200 1000 50  0001 C CNN "DistLink"
	1    5200 1000
	0    1    1    0   
$EndComp
Text HLabel 5050 1000 0    50   Input ~ 0
IN4
Text Label 7150 1000 2    50   ~ 0
IN5_POS
Connection ~ 6700 1000
Wire Wire Line
	6700 1000 7150 1000
Text HLabel 7150 1300 3    50   Input ~ 0
GND
Text HLabel 6700 1300 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609CC527
P 6700 1150
AR Path="/609CC527" Ref="D?"  Part="1" 
AR Path="/60958BFE/609CC527" Ref="D5"  Part="1" 
F 0 "D5" V 6654 1229 50  0000 L CNN
F 1 "1N4148" V 6745 1229 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 6700 975 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6700 1150 50  0001 C CNN
F 4 "Rectifier Diode" H 6700 1150 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 6700 1150 50  0001 C CNN "Description"
F 6 "Yes" H 6700 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 6700 1150 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 6700 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 6700 1150 50  0001 C CNN "DistLink"
	1    6700 1150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609CC533
P 7150 1150
AR Path="/609CC533" Ref="R?"  Part="1" 
AR Path="/60958BFE/609CC533" Ref="R13"  Part="1" 
F 0 "R13" H 7000 1100 50  0000 C CNN
F 1 "100k" H 6950 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 1150 50  0001 C CNN
F 3 "~" H 7150 1150 50  0001 C CNN
F 4 "Resistor" H 7150 1150 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 7150 1150 50  0001 C CNN "Description"
F 6 "Yes" H 7150 1150 50  0001 C CNN "Place"
F 7 "Digikey" H 7150 1150 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 7150 1150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 7150 1150 50  0001 C CNN "DistLink"
	1    7150 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609CC53F
P 6550 1000
AR Path="/609CC53F" Ref="R?"  Part="1" 
AR Path="/60958BFE/609CC53F" Ref="R8"  Part="1" 
F 0 "R8" V 6343 1000 50  0000 C CNN
F 1 "100k" V 6434 1000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 1000 50  0001 C CNN
F 3 "~" H 6550 1000 50  0001 C CNN
F 4 "Resistor" H 6550 1000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 6550 1000 50  0001 C CNN "Description"
F 6 "Yes" H 6550 1000 50  0001 C CNN "Place"
F 7 "Digikey" H 6550 1000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 6550 1000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 6550 1000 50  0001 C CNN "DistLink"
	1    6550 1000
	0    1    1    0   
$EndComp
Text HLabel 6400 1000 0    50   Input ~ 0
IN5
Text Label 1850 1950 2    50   ~ 0
IN6_POS
Connection ~ 1400 1950
Wire Wire Line
	1400 1950 1850 1950
Text HLabel 1850 2250 3    50   Input ~ 0
GND
Text HLabel 1400 2250 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E1FA9
P 1400 2100
AR Path="/609E1FA9" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E1FA9" Ref="D6"  Part="1" 
F 0 "D6" V 1354 2179 50  0000 L CNN
F 1 "1N4148" V 1445 2179 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 1400 1925 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 1400 2100 50  0001 C CNN
F 4 "Rectifier Diode" H 1400 2100 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 1400 2100 50  0001 C CNN "Description"
F 6 "Yes" H 1400 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 1400 2100 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 1400 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 1400 2100 50  0001 C CNN "DistLink"
	1    1400 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E1FB5
P 1850 2100
AR Path="/609E1FB5" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E1FB5" Ref="R19"  Part="1" 
F 0 "R19" H 1700 2050 50  0000 C CNN
F 1 "100k" H 1650 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1780 2100 50  0001 C CNN
F 3 "~" H 1850 2100 50  0001 C CNN
F 4 "Resistor" H 1850 2100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1850 2100 50  0001 C CNN "Description"
F 6 "Yes" H 1850 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 1850 2100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1850 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1850 2100 50  0001 C CNN "DistLink"
	1    1850 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E1FC1
P 1250 1950
AR Path="/609E1FC1" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E1FC1" Ref="R14"  Part="1" 
F 0 "R14" V 1043 1950 50  0000 C CNN
F 1 "100k" V 1134 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1180 1950 50  0001 C CNN
F 3 "~" H 1250 1950 50  0001 C CNN
F 4 "Resistor" H 1250 1950 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1250 1950 50  0001 C CNN "Description"
F 6 "Yes" H 1250 1950 50  0001 C CNN "Place"
F 7 "Digikey" H 1250 1950 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1250 1950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1250 1950 50  0001 C CNN "DistLink"
	1    1250 1950
	0    1    1    0   
$EndComp
Text HLabel 1100 1950 0    50   Input ~ 0
IN6
Text Label 3150 1950 2    50   ~ 0
IN7_POS
Connection ~ 2700 1950
Wire Wire Line
	2700 1950 3150 1950
Text HLabel 3150 2250 3    50   Input ~ 0
GND
Text HLabel 2700 2250 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E1FD3
P 2700 2100
AR Path="/609E1FD3" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E1FD3" Ref="D7"  Part="1" 
F 0 "D7" V 2654 2179 50  0000 L CNN
F 1 "1N4148" V 2745 2179 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 2700 1925 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 2700 2100 50  0001 C CNN
F 4 "Rectifier Diode" H 2700 2100 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 2700 2100 50  0001 C CNN "Description"
F 6 "Yes" H 2700 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 2700 2100 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 2700 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 2700 2100 50  0001 C CNN "DistLink"
	1    2700 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E1FDF
P 3150 2100
AR Path="/609E1FDF" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E1FDF" Ref="R20"  Part="1" 
F 0 "R20" H 3000 2050 50  0000 C CNN
F 1 "100k" H 2950 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 2100 50  0001 C CNN
F 3 "~" H 3150 2100 50  0001 C CNN
F 4 "Resistor" H 3150 2100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3150 2100 50  0001 C CNN "Description"
F 6 "Yes" H 3150 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 3150 2100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3150 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3150 2100 50  0001 C CNN "DistLink"
	1    3150 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E1FEB
P 2550 1950
AR Path="/609E1FEB" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E1FEB" Ref="R15"  Part="1" 
F 0 "R15" V 2343 1950 50  0000 C CNN
F 1 "100k" V 2434 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 1950 50  0001 C CNN
F 3 "~" H 2550 1950 50  0001 C CNN
F 4 "Resistor" H 2550 1950 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 2550 1950 50  0001 C CNN "Description"
F 6 "Yes" H 2550 1950 50  0001 C CNN "Place"
F 7 "Digikey" H 2550 1950 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 2550 1950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 2550 1950 50  0001 C CNN "DistLink"
	1    2550 1950
	0    1    1    0   
$EndComp
Text HLabel 2400 1950 0    50   Input ~ 0
IN7
Text Label 4450 1950 2    50   ~ 0
IN8_POS
Connection ~ 4000 1950
Wire Wire Line
	4000 1950 4450 1950
Text HLabel 4450 2250 3    50   Input ~ 0
GND
Text HLabel 4000 2250 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E1FFD
P 4000 2100
AR Path="/609E1FFD" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E1FFD" Ref="D8"  Part="1" 
F 0 "D8" V 3954 2179 50  0000 L CNN
F 1 "1N4148" V 4045 2179 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 4000 1925 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 2100 50  0001 C CNN
F 4 "Rectifier Diode" H 4000 2100 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 4000 2100 50  0001 C CNN "Description"
F 6 "Yes" H 4000 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 4000 2100 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 4000 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 4000 2100 50  0001 C CNN "DistLink"
	1    4000 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E2009
P 4450 2100
AR Path="/609E2009" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E2009" Ref="R21"  Part="1" 
F 0 "R21" H 4300 2050 50  0000 C CNN
F 1 "100k" H 4250 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 2100 50  0001 C CNN
F 3 "~" H 4450 2100 50  0001 C CNN
F 4 "Resistor" H 4450 2100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 4450 2100 50  0001 C CNN "Description"
F 6 "Yes" H 4450 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 4450 2100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 4450 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 4450 2100 50  0001 C CNN "DistLink"
	1    4450 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E2015
P 3850 1950
AR Path="/609E2015" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E2015" Ref="R16"  Part="1" 
F 0 "R16" V 3643 1950 50  0000 C CNN
F 1 "100k" V 3734 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 1950 50  0001 C CNN
F 3 "~" H 3850 1950 50  0001 C CNN
F 4 "Resistor" H 3850 1950 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3850 1950 50  0001 C CNN "Description"
F 6 "Yes" H 3850 1950 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 1950 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3850 1950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3850 1950 50  0001 C CNN "DistLink"
	1    3850 1950
	0    1    1    0   
$EndComp
Text HLabel 3700 1950 0    50   Input ~ 0
IN8
Text Label 5800 1950 2    50   ~ 0
IN9_POS
Connection ~ 5350 1950
Wire Wire Line
	5350 1950 5800 1950
Text HLabel 5800 2250 3    50   Input ~ 0
GND
Text HLabel 5350 2250 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E2027
P 5350 2100
AR Path="/609E2027" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E2027" Ref="D9"  Part="1" 
F 0 "D9" V 5304 2179 50  0000 L CNN
F 1 "1N4148" V 5395 2179 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 5350 1925 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5350 2100 50  0001 C CNN
F 4 "Rectifier Diode" H 5350 2100 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 5350 2100 50  0001 C CNN "Description"
F 6 "Yes" H 5350 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 5350 2100 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 5350 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 5350 2100 50  0001 C CNN "DistLink"
	1    5350 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E2033
P 5800 2100
AR Path="/609E2033" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E2033" Ref="R22"  Part="1" 
F 0 "R22" H 5650 2050 50  0000 C CNN
F 1 "100k" H 5600 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 2100 50  0001 C CNN
F 3 "~" H 5800 2100 50  0001 C CNN
F 4 "Resistor" H 5800 2100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5800 2100 50  0001 C CNN "Description"
F 6 "Yes" H 5800 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 5800 2100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5800 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5800 2100 50  0001 C CNN "DistLink"
	1    5800 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E203F
P 5200 1950
AR Path="/609E203F" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E203F" Ref="R17"  Part="1" 
F 0 "R17" V 4993 1950 50  0000 C CNN
F 1 "100k" V 5084 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 1950 50  0001 C CNN
F 3 "~" H 5200 1950 50  0001 C CNN
F 4 "Resistor" H 5200 1950 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5200 1950 50  0001 C CNN "Description"
F 6 "Yes" H 5200 1950 50  0001 C CNN "Place"
F 7 "Digikey" H 5200 1950 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5200 1950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5200 1950 50  0001 C CNN "DistLink"
	1    5200 1950
	0    1    1    0   
$EndComp
Text HLabel 5050 1950 0    50   Input ~ 0
IN9
Text Label 7150 1950 2    50   ~ 0
IN10_POS
Connection ~ 6700 1950
Wire Wire Line
	6700 1950 7150 1950
Text HLabel 7150 2250 3    50   Input ~ 0
GND
Text HLabel 6700 2250 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E2051
P 6700 2100
AR Path="/609E2051" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E2051" Ref="D10"  Part="1" 
F 0 "D10" V 6654 2179 50  0000 L CNN
F 1 "1N4148" V 6745 2179 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 6700 1925 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6700 2100 50  0001 C CNN
F 4 "Rectifier Diode" H 6700 2100 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 6700 2100 50  0001 C CNN "Description"
F 6 "Yes" H 6700 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 6700 2100 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 6700 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 6700 2100 50  0001 C CNN "DistLink"
	1    6700 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E205D
P 7150 2100
AR Path="/609E205D" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E205D" Ref="R23"  Part="1" 
F 0 "R23" H 7000 2050 50  0000 C CNN
F 1 "100k" H 6950 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 2100 50  0001 C CNN
F 3 "~" H 7150 2100 50  0001 C CNN
F 4 "Resistor" H 7150 2100 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 7150 2100 50  0001 C CNN "Description"
F 6 "Yes" H 7150 2100 50  0001 C CNN "Place"
F 7 "Digikey" H 7150 2100 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 7150 2100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 7150 2100 50  0001 C CNN "DistLink"
	1    7150 2100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E2069
P 6550 1950
AR Path="/609E2069" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E2069" Ref="R18"  Part="1" 
F 0 "R18" V 6343 1950 50  0000 C CNN
F 1 "100k" V 6434 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 1950 50  0001 C CNN
F 3 "~" H 6550 1950 50  0001 C CNN
F 4 "Resistor" H 6550 1950 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 6550 1950 50  0001 C CNN "Description"
F 6 "Yes" H 6550 1950 50  0001 C CNN "Place"
F 7 "Digikey" H 6550 1950 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 6550 1950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 6550 1950 50  0001 C CNN "DistLink"
	1    6550 1950
	0    1    1    0   
$EndComp
Text HLabel 6400 1950 0    50   Input ~ 0
IN10
Text Label 1850 2900 2    50   ~ 0
IN11_POS
Connection ~ 1400 2900
Wire Wire Line
	1400 2900 1850 2900
Text HLabel 1850 3200 3    50   Input ~ 0
GND
Text HLabel 1400 3200 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E869C
P 1400 3050
AR Path="/609E869C" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E869C" Ref="D11"  Part="1" 
F 0 "D11" V 1354 3129 50  0000 L CNN
F 1 "1N4148" V 1445 3129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 1400 2875 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 1400 3050 50  0001 C CNN
F 4 "Rectifier Diode" H 1400 3050 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 1400 3050 50  0001 C CNN "Description"
F 6 "Yes" H 1400 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 1400 3050 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 1400 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 1400 3050 50  0001 C CNN "DistLink"
	1    1400 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E86A8
P 1850 3050
AR Path="/609E86A8" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E86A8" Ref="R29"  Part="1" 
F 0 "R29" H 1700 3000 50  0000 C CNN
F 1 "100k" H 1650 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1780 3050 50  0001 C CNN
F 3 "~" H 1850 3050 50  0001 C CNN
F 4 "Resistor" H 1850 3050 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1850 3050 50  0001 C CNN "Description"
F 6 "Yes" H 1850 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 1850 3050 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1850 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1850 3050 50  0001 C CNN "DistLink"
	1    1850 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E86B4
P 1250 2900
AR Path="/609E86B4" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E86B4" Ref="R24"  Part="1" 
F 0 "R24" V 1043 2900 50  0000 C CNN
F 1 "100k" V 1134 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1180 2900 50  0001 C CNN
F 3 "~" H 1250 2900 50  0001 C CNN
F 4 "Resistor" H 1250 2900 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1250 2900 50  0001 C CNN "Description"
F 6 "Yes" H 1250 2900 50  0001 C CNN "Place"
F 7 "Digikey" H 1250 2900 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1250 2900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1250 2900 50  0001 C CNN "DistLink"
	1    1250 2900
	0    1    1    0   
$EndComp
Text HLabel 1100 2900 0    50   Input ~ 0
IN11
Text Label 3150 2900 2    50   ~ 0
IN12_POS
Connection ~ 2700 2900
Wire Wire Line
	2700 2900 3150 2900
Text HLabel 3150 3200 3    50   Input ~ 0
GND
Text HLabel 2700 3200 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E86C6
P 2700 3050
AR Path="/609E86C6" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E86C6" Ref="D12"  Part="1" 
F 0 "D12" V 2654 3129 50  0000 L CNN
F 1 "1N4148" V 2745 3129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 2700 2875 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 2700 3050 50  0001 C CNN
F 4 "Rectifier Diode" H 2700 3050 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 2700 3050 50  0001 C CNN "Description"
F 6 "Yes" H 2700 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 2700 3050 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 2700 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 2700 3050 50  0001 C CNN "DistLink"
	1    2700 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E86D2
P 3150 3050
AR Path="/609E86D2" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E86D2" Ref="R30"  Part="1" 
F 0 "R30" H 3000 3000 50  0000 C CNN
F 1 "100k" H 2950 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 3050 50  0001 C CNN
F 3 "~" H 3150 3050 50  0001 C CNN
F 4 "Resistor" H 3150 3050 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3150 3050 50  0001 C CNN "Description"
F 6 "Yes" H 3150 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 3150 3050 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3150 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3150 3050 50  0001 C CNN "DistLink"
	1    3150 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E86DE
P 2550 2900
AR Path="/609E86DE" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E86DE" Ref="R25"  Part="1" 
F 0 "R25" V 2343 2900 50  0000 C CNN
F 1 "100k" V 2434 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 2900 50  0001 C CNN
F 3 "~" H 2550 2900 50  0001 C CNN
F 4 "Resistor" H 2550 2900 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 2550 2900 50  0001 C CNN "Description"
F 6 "Yes" H 2550 2900 50  0001 C CNN "Place"
F 7 "Digikey" H 2550 2900 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 2550 2900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 2550 2900 50  0001 C CNN "DistLink"
	1    2550 2900
	0    1    1    0   
$EndComp
Text HLabel 2400 2900 0    50   Input ~ 0
IN12
Text Label 4450 2900 2    50   ~ 0
IN13_POS
Connection ~ 4000 2900
Wire Wire Line
	4000 2900 4450 2900
Text HLabel 4450 3200 3    50   Input ~ 0
GND
Text HLabel 4000 3200 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E86F0
P 4000 3050
AR Path="/609E86F0" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E86F0" Ref="D13"  Part="1" 
F 0 "D13" V 3954 3129 50  0000 L CNN
F 1 "1N4148" V 4045 3129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 4000 2875 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 3050 50  0001 C CNN
F 4 "Rectifier Diode" H 4000 3050 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 4000 3050 50  0001 C CNN "Description"
F 6 "Yes" H 4000 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 4000 3050 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 4000 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 4000 3050 50  0001 C CNN "DistLink"
	1    4000 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E86FC
P 4450 3050
AR Path="/609E86FC" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E86FC" Ref="R31"  Part="1" 
F 0 "R31" H 4300 3000 50  0000 C CNN
F 1 "100k" H 4250 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 3050 50  0001 C CNN
F 3 "~" H 4450 3050 50  0001 C CNN
F 4 "Resistor" H 4450 3050 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 4450 3050 50  0001 C CNN "Description"
F 6 "Yes" H 4450 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 4450 3050 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 4450 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 4450 3050 50  0001 C CNN "DistLink"
	1    4450 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E8708
P 3850 2900
AR Path="/609E8708" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E8708" Ref="R26"  Part="1" 
F 0 "R26" V 3643 2900 50  0000 C CNN
F 1 "100k" V 3734 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 2900 50  0001 C CNN
F 3 "~" H 3850 2900 50  0001 C CNN
F 4 "Resistor" H 3850 2900 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3850 2900 50  0001 C CNN "Description"
F 6 "Yes" H 3850 2900 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 2900 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3850 2900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3850 2900 50  0001 C CNN "DistLink"
	1    3850 2900
	0    1    1    0   
$EndComp
Text HLabel 3700 2900 0    50   Input ~ 0
IN13
Text Label 5800 2900 2    50   ~ 0
IN14_POS
Connection ~ 5350 2900
Wire Wire Line
	5350 2900 5800 2900
Text HLabel 5800 3200 3    50   Input ~ 0
GND
Text HLabel 5350 3200 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E871A
P 5350 3050
AR Path="/609E871A" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E871A" Ref="D14"  Part="1" 
F 0 "D14" V 5304 3129 50  0000 L CNN
F 1 "1N4148" V 5395 3129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 5350 2875 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5350 3050 50  0001 C CNN
F 4 "Rectifier Diode" H 5350 3050 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 5350 3050 50  0001 C CNN "Description"
F 6 "Yes" H 5350 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 5350 3050 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 5350 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 5350 3050 50  0001 C CNN "DistLink"
	1    5350 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E8726
P 5800 3050
AR Path="/609E8726" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E8726" Ref="R32"  Part="1" 
F 0 "R32" H 5650 3000 50  0000 C CNN
F 1 "100k" H 5600 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 3050 50  0001 C CNN
F 3 "~" H 5800 3050 50  0001 C CNN
F 4 "Resistor" H 5800 3050 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5800 3050 50  0001 C CNN "Description"
F 6 "Yes" H 5800 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 5800 3050 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5800 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5800 3050 50  0001 C CNN "DistLink"
	1    5800 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E8732
P 5200 2900
AR Path="/609E8732" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E8732" Ref="R27"  Part="1" 
F 0 "R27" V 4993 2900 50  0000 C CNN
F 1 "100k" V 5084 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 2900 50  0001 C CNN
F 3 "~" H 5200 2900 50  0001 C CNN
F 4 "Resistor" H 5200 2900 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5200 2900 50  0001 C CNN "Description"
F 6 "Yes" H 5200 2900 50  0001 C CNN "Place"
F 7 "Digikey" H 5200 2900 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5200 2900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5200 2900 50  0001 C CNN "DistLink"
	1    5200 2900
	0    1    1    0   
$EndComp
Text HLabel 5050 2900 0    50   Input ~ 0
IN14
Text Label 7150 2900 2    50   ~ 0
IN15_POS
Connection ~ 6700 2900
Wire Wire Line
	6700 2900 7150 2900
Text HLabel 7150 3200 3    50   Input ~ 0
GND
Text HLabel 6700 3200 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609E8744
P 6700 3050
AR Path="/609E8744" Ref="D?"  Part="1" 
AR Path="/60958BFE/609E8744" Ref="D15"  Part="1" 
F 0 "D15" V 6654 3129 50  0000 L CNN
F 1 "1N4148" V 6745 3129 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 6700 2875 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6700 3050 50  0001 C CNN
F 4 "Rectifier Diode" H 6700 3050 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 6700 3050 50  0001 C CNN "Description"
F 6 "Yes" H 6700 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 6700 3050 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 6700 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 6700 3050 50  0001 C CNN "DistLink"
	1    6700 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609E8750
P 7150 3050
AR Path="/609E8750" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E8750" Ref="R33"  Part="1" 
F 0 "R33" H 7000 3000 50  0000 C CNN
F 1 "100k" H 6950 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 3050 50  0001 C CNN
F 3 "~" H 7150 3050 50  0001 C CNN
F 4 "Resistor" H 7150 3050 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 7150 3050 50  0001 C CNN "Description"
F 6 "Yes" H 7150 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 7150 3050 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 7150 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 7150 3050 50  0001 C CNN "DistLink"
	1    7150 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609E875C
P 6550 2900
AR Path="/609E875C" Ref="R?"  Part="1" 
AR Path="/60958BFE/609E875C" Ref="R28"  Part="1" 
F 0 "R28" V 6343 2900 50  0000 C CNN
F 1 "100k" V 6434 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 2900 50  0001 C CNN
F 3 "~" H 6550 2900 50  0001 C CNN
F 4 "Resistor" H 6550 2900 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 6550 2900 50  0001 C CNN "Description"
F 6 "Yes" H 6550 2900 50  0001 C CNN "Place"
F 7 "Digikey" H 6550 2900 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 6550 2900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 6550 2900 50  0001 C CNN "DistLink"
	1    6550 2900
	0    1    1    0   
$EndComp
Text HLabel 6400 2900 0    50   Input ~ 0
IN15
Text Label 1850 3850 2    50   ~ 0
IN16_POS
Connection ~ 1400 3850
Wire Wire Line
	1400 3850 1850 3850
Text HLabel 1850 4150 3    50   Input ~ 0
GND
Text HLabel 1400 4150 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609EEB73
P 1400 4000
AR Path="/609EEB73" Ref="D?"  Part="1" 
AR Path="/60958BFE/609EEB73" Ref="D16"  Part="1" 
F 0 "D16" V 1354 4079 50  0000 L CNN
F 1 "1N4148" V 1445 4079 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 1400 3825 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 1400 4000 50  0001 C CNN
F 4 "Rectifier Diode" H 1400 4000 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 1400 4000 50  0001 C CNN "Description"
F 6 "Yes" H 1400 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 1400 4000 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 1400 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 1400 4000 50  0001 C CNN "DistLink"
	1    1400 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEB7F
P 1850 4000
AR Path="/609EEB7F" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEB7F" Ref="R39"  Part="1" 
F 0 "R39" H 1700 3950 50  0000 C CNN
F 1 "100k" H 1650 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1780 4000 50  0001 C CNN
F 3 "~" H 1850 4000 50  0001 C CNN
F 4 "Resistor" H 1850 4000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1850 4000 50  0001 C CNN "Description"
F 6 "Yes" H 1850 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 1850 4000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1850 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1850 4000 50  0001 C CNN "DistLink"
	1    1850 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEB8B
P 1250 3850
AR Path="/609EEB8B" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEB8B" Ref="R34"  Part="1" 
F 0 "R34" V 1043 3850 50  0000 C CNN
F 1 "100k" V 1134 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1180 3850 50  0001 C CNN
F 3 "~" H 1250 3850 50  0001 C CNN
F 4 "Resistor" H 1250 3850 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 1250 3850 50  0001 C CNN "Description"
F 6 "Yes" H 1250 3850 50  0001 C CNN "Place"
F 7 "Digikey" H 1250 3850 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 1250 3850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 1250 3850 50  0001 C CNN "DistLink"
	1    1250 3850
	0    1    1    0   
$EndComp
Text HLabel 1100 3850 0    50   Input ~ 0
IN16
Text Label 3150 3850 2    50   ~ 0
IN17_POS
Connection ~ 2700 3850
Wire Wire Line
	2700 3850 3150 3850
Text HLabel 3150 4150 3    50   Input ~ 0
GND
Text HLabel 2700 4150 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609EEB9D
P 2700 4000
AR Path="/609EEB9D" Ref="D?"  Part="1" 
AR Path="/60958BFE/609EEB9D" Ref="D17"  Part="1" 
F 0 "D17" V 2654 4079 50  0000 L CNN
F 1 "1N4148" V 2745 4079 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 2700 3825 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 2700 4000 50  0001 C CNN
F 4 "Rectifier Diode" H 2700 4000 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 2700 4000 50  0001 C CNN "Description"
F 6 "Yes" H 2700 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 2700 4000 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 2700 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 2700 4000 50  0001 C CNN "DistLink"
	1    2700 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEBA9
P 3150 4000
AR Path="/609EEBA9" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEBA9" Ref="R40"  Part="1" 
F 0 "R40" H 3000 3950 50  0000 C CNN
F 1 "100k" H 2950 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 4000 50  0001 C CNN
F 3 "~" H 3150 4000 50  0001 C CNN
F 4 "Resistor" H 3150 4000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3150 4000 50  0001 C CNN "Description"
F 6 "Yes" H 3150 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 3150 4000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3150 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3150 4000 50  0001 C CNN "DistLink"
	1    3150 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEBB5
P 2550 3850
AR Path="/609EEBB5" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEBB5" Ref="R35"  Part="1" 
F 0 "R35" V 2343 3850 50  0000 C CNN
F 1 "100k" V 2434 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 3850 50  0001 C CNN
F 3 "~" H 2550 3850 50  0001 C CNN
F 4 "Resistor" H 2550 3850 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 2550 3850 50  0001 C CNN "Description"
F 6 "Yes" H 2550 3850 50  0001 C CNN "Place"
F 7 "Digikey" H 2550 3850 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 2550 3850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 2550 3850 50  0001 C CNN "DistLink"
	1    2550 3850
	0    1    1    0   
$EndComp
Text HLabel 2400 3850 0    50   Input ~ 0
IN17
Text Label 4450 3850 2    50   ~ 0
IN18_POS
Connection ~ 4000 3850
Wire Wire Line
	4000 3850 4450 3850
Text HLabel 4450 4150 3    50   Input ~ 0
GND
Text HLabel 4000 4150 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609EEBC7
P 4000 4000
AR Path="/609EEBC7" Ref="D?"  Part="1" 
AR Path="/60958BFE/609EEBC7" Ref="D18"  Part="1" 
F 0 "D18" V 3954 4079 50  0000 L CNN
F 1 "1N4148" V 4045 4079 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 4000 3825 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 4000 4000 50  0001 C CNN
F 4 "Rectifier Diode" H 4000 4000 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 4000 4000 50  0001 C CNN "Description"
F 6 "Yes" H 4000 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 4000 4000 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 4000 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 4000 4000 50  0001 C CNN "DistLink"
	1    4000 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEBD3
P 4450 4000
AR Path="/609EEBD3" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEBD3" Ref="R41"  Part="1" 
F 0 "R41" H 4300 3950 50  0000 C CNN
F 1 "100k" H 4250 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 4000 50  0001 C CNN
F 3 "~" H 4450 4000 50  0001 C CNN
F 4 "Resistor" H 4450 4000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 4450 4000 50  0001 C CNN "Description"
F 6 "Yes" H 4450 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 4450 4000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 4450 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 4450 4000 50  0001 C CNN "DistLink"
	1    4450 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEBDF
P 3850 3850
AR Path="/609EEBDF" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEBDF" Ref="R36"  Part="1" 
F 0 "R36" V 3643 3850 50  0000 C CNN
F 1 "100k" V 3734 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 3850 50  0001 C CNN
F 3 "~" H 3850 3850 50  0001 C CNN
F 4 "Resistor" H 3850 3850 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 3850 3850 50  0001 C CNN "Description"
F 6 "Yes" H 3850 3850 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 3850 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 3850 3850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 3850 3850 50  0001 C CNN "DistLink"
	1    3850 3850
	0    1    1    0   
$EndComp
Text HLabel 3700 3850 0    50   Input ~ 0
IN18
Text Label 5800 3850 2    50   ~ 0
IN19_POS
Connection ~ 5350 3850
Wire Wire Line
	5350 3850 5800 3850
Text HLabel 5800 4150 3    50   Input ~ 0
GND
Text HLabel 5350 4150 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609EEBF1
P 5350 4000
AR Path="/609EEBF1" Ref="D?"  Part="1" 
AR Path="/60958BFE/609EEBF1" Ref="D19"  Part="1" 
F 0 "D19" V 5304 4079 50  0000 L CNN
F 1 "1N4148" V 5395 4079 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 5350 3825 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 5350 4000 50  0001 C CNN
F 4 "Rectifier Diode" H 5350 4000 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 5350 4000 50  0001 C CNN "Description"
F 6 "Yes" H 5350 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 5350 4000 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 5350 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 5350 4000 50  0001 C CNN "DistLink"
	1    5350 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEBFD
P 5800 4000
AR Path="/609EEBFD" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEBFD" Ref="R42"  Part="1" 
F 0 "R42" H 5650 3950 50  0000 C CNN
F 1 "100k" H 5600 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5730 4000 50  0001 C CNN
F 3 "~" H 5800 4000 50  0001 C CNN
F 4 "Resistor" H 5800 4000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5800 4000 50  0001 C CNN "Description"
F 6 "Yes" H 5800 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 5800 4000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5800 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5800 4000 50  0001 C CNN "DistLink"
	1    5800 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEC09
P 5200 3850
AR Path="/609EEC09" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEC09" Ref="R37"  Part="1" 
F 0 "R37" V 4993 3850 50  0000 C CNN
F 1 "100k" V 5084 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5130 3850 50  0001 C CNN
F 3 "~" H 5200 3850 50  0001 C CNN
F 4 "Resistor" H 5200 3850 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 5200 3850 50  0001 C CNN "Description"
F 6 "Yes" H 5200 3850 50  0001 C CNN "Place"
F 7 "Digikey" H 5200 3850 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 5200 3850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 5200 3850 50  0001 C CNN "DistLink"
	1    5200 3850
	0    1    1    0   
$EndComp
Text HLabel 5050 3850 0    50   Input ~ 0
IN19
Text Label 7150 3850 2    50   ~ 0
IN20_POS
Connection ~ 6700 3850
Wire Wire Line
	6700 3850 7150 3850
Text HLabel 7150 4150 3    50   Input ~ 0
GND
Text HLabel 6700 4150 3    50   Input ~ 0
GND
$Comp
L Diode:1N4148 D?
U 1 1 609EEC1B
P 6700 4000
AR Path="/609EEC1B" Ref="D?"  Part="1" 
AR Path="/60958BFE/609EEC1B" Ref="D20"  Part="1" 
F 0 "D20" V 6654 4079 50  0000 L CNN
F 1 "1N4148" V 6745 4079 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 6700 3825 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/1N4148_1N4448.pdf" H 6700 4000 50  0001 C CNN
F 4 "Rectifier Diode" H 6700 4000 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 200MA SOD523F" H 6700 4000 50  0001 C CNN "Description"
F 6 "Yes" H 6700 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 6700 4000 50  0001 C CNN "Dist"
F 8 "1N4148WTCT-ND" H 6700 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WT/1N4148WTCT-ND/2094398" H 6700 4000 50  0001 C CNN "DistLink"
	1    6700 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEC27
P 7150 4000
AR Path="/609EEC27" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEC27" Ref="R43"  Part="1" 
F 0 "R43" H 7000 3950 50  0000 C CNN
F 1 "100k" H 6950 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7080 4000 50  0001 C CNN
F 3 "~" H 7150 4000 50  0001 C CNN
F 4 "Resistor" H 7150 4000 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 7150 4000 50  0001 C CNN "Description"
F 6 "Yes" H 7150 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 7150 4000 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 7150 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 7150 4000 50  0001 C CNN "DistLink"
	1    7150 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 609EEC33
P 6550 3850
AR Path="/609EEC33" Ref="R?"  Part="1" 
AR Path="/60958BFE/609EEC33" Ref="R38"  Part="1" 
F 0 "R38" V 6343 3850 50  0000 C CNN
F 1 "100k" V 6434 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6480 3850 50  0001 C CNN
F 3 "~" H 6550 3850 50  0001 C CNN
F 4 "Resistor" H 6550 3850 50  0001 C CNN "Device"
F 5 "RES SMD 100K OHM 1% 1/10W 0603" H 6550 3850 50  0001 C CNN "Description"
F 6 "Yes" H 6550 3850 50  0001 C CNN "Place"
F 7 "Digikey" H 6550 3850 50  0001 C CNN "Dist"
F 8 "541-100KHCT-ND" H 6550 3850 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/vishay-dale/CRCW0603100KFKEA/541-100KHCT-ND/1180038" H 6550 3850 50  0001 C CNN "DistLink"
	1    6550 3850
	0    1    1    0   
$EndComp
Text HLabel 6400 3850 0    50   Input ~ 0
IN20
$Comp
L 4xxx:4051 U?
U 1 1 60A214CA
P 9150 4700
AR Path="/60A214CA" Ref="U?"  Part="1" 
AR Path="/6093B89C/60A214CA" Ref="U?"  Part="1" 
AR Path="/60958BFE/60A214CA" Ref="U4"  Part="1" 
F 0 "U4" H 9550 4500 50  0000 L CNN
F 1 "4051" H 9550 4400 50  0000 L CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 9150 4700 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 9150 4700 50  0001 C CNN
F 4 "Multiplexer" H 9150 4700 50  0001 C CNN "Device"
F 5 "IC MUX/DEMUX 8X1 16TSSOP" H 9150 4700 50  0001 C CNN "Description"
F 6 "Yes" H 9150 4700 50  0001 C CNN "Place"
F 7 "Digikey" H 9150 4700 50  0001 C CNN "Dist"
F 8 "296-11993-1-ND" H 9150 4700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/CD4051BPWR/296-11993-1-ND/390442" H 9150 4700 50  0001 C CNN "DistLink"
	1    9150 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60A214D6
P 10000 5200
AR Path="/60A214D6" Ref="C?"  Part="1" 
AR Path="/6093B89C/60A214D6" Ref="C?"  Part="1" 
AR Path="/60958BFE/60A214D6" Ref="C6"  Part="1" 
F 0 "C6" H 9800 5150 50  0000 C CNN
F 1 "100n" H 9800 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10038 5050 50  0001 C CNN
F 3 "~" H 10000 5200 50  0001 C CNN
F 4 "Ceramic Capacitor" H 10000 5200 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 10000 5200 50  0001 C CNN "Description"
F 6 "Yes" H 10000 5200 50  0001 C CNN "Place"
F 7 "Digikey" H 10000 5200 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 10000 5200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 10000 5200 50  0001 C CNN "DistLink"
	1    10000 5200
	-1   0    0    1   
$EndComp
Text HLabel 8650 5100 0    50   Input ~ 0
A
Text HLabel 8650 5200 0    50   Input ~ 0
B
Text HLabel 8650 5300 0    50   Input ~ 0
C
Text HLabel 9950 3900 2    50   Output ~ 0
~OUT1~
$Comp
L Device:R R?
U 1 1 60A214E6
P 9950 3750
AR Path="/60A214E6" Ref="R?"  Part="1" 
AR Path="/60958BFE/60A214E6" Ref="R2"  Part="1" 
F 0 "R2" H 10100 3800 50  0000 C CNN
F 1 "10k" H 10100 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9880 3750 50  0001 C CNN
F 3 "~" H 9950 3750 50  0001 C CNN
F 4 "Resistor" H 9950 3750 50  0001 C CNN "Device"
F 5 "RES SMD 10K OHM 1% 1/10W 0603" H 9950 3750 50  0001 C CNN "Description"
F 6 "Yes" H 9950 3750 50  0001 C CNN "Place"
F 7 "Digikey" H 9950 3750 50  0001 C CNN "Dist"
F 8 "311-10KLDCT-ND" H 9950 3750 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-0710KL/311-10KLDCT-ND/2828135" H 9950 3750 50  0001 C CNN "DistLink"
	1    9950 3750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q?
U 1 1 60A214F2
P 9850 4100
AR Path="/60A214F2" Ref="Q?"  Part="1" 
AR Path="/60958BFE/60A214F2" Ref="Q2"  Part="1" 
F 0 "Q2" H 10041 4146 50  0000 L CNN
F 1 "MMBT3904" H 10041 4055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10050 4025 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9850 4100 50  0001 L CNN
F 4 "Bipolar Transistor" H 9850 4100 50  0001 C CNN "Device"
F 5 "TRANS NPN 40V 0.2A SOT23" H 9850 4100 50  0001 C CNN "Description"
F 6 "Yes" H 9850 4100 50  0001 C CNN "Place"
F 7 "Digikey" H 9850 4100 50  0001 C CNN "Dist"
F 8 "MMBT3904LT3GOSCT-ND" H 9850 4100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/MMBT3904LT3G/MMBT3904LT3GOSCT-ND/1139814" H 9850 4100 50  0001 C CNN "DistLink"
	1    9850 4100
	1    0    0    -1  
$EndComp
Text HLabel 9150 3800 1    50   Input ~ 0
12V
Text HLabel 9150 5600 3    50   Input ~ 0
GND
Text HLabel 9250 5600 3    50   Input ~ 0
GND
Text HLabel 8650 5000 0    50   Input ~ 0
GND
Text HLabel 9950 4300 3    50   Input ~ 0
GND
Text HLabel 10000 5050 1    50   Input ~ 0
12V
Text HLabel 9950 3600 1    50   Input ~ 0
3V3
Text Label 8650 4300 2    50   ~ 0
IN9_POS
Text HLabel 10000 5350 3    50   Input ~ 0
GND
Text Label 8650 4200 2    50   ~ 0
IN10_POS
Text Label 8650 4100 2    50   ~ 0
IN11_POS
Text Label 8650 4400 2    50   ~ 0
IN12_POS
Text Label 8650 4500 2    50   ~ 0
IN13_POS
Text Label 8650 4700 2    50   ~ 0
IN14_POS
Text Label 8650 4800 2    50   ~ 0
IN15_POS
Text Label 8650 4600 2    50   ~ 0
IN16_POS
$Comp
L 4xxx:4051 U?
U 1 1 60A25F8E
P 4950 6100
AR Path="/60A25F8E" Ref="U?"  Part="1" 
AR Path="/6093B89C/60A25F8E" Ref="U?"  Part="1" 
AR Path="/60958BFE/60A25F8E" Ref="U5"  Part="1" 
F 0 "U5" H 5350 5900 50  0000 L CNN
F 1 "4051" H 5350 5800 50  0000 L CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 4950 6100 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 4950 6100 50  0001 C CNN
F 4 "Multiplexer" H 4950 6100 50  0001 C CNN "Device"
F 5 "IC MUX/DEMUX 8X1 16TSSOP" H 4950 6100 50  0001 C CNN "Description"
F 6 "Yes" H 4950 6100 50  0001 C CNN "Place"
F 7 "Digikey" H 4950 6100 50  0001 C CNN "Dist"
F 8 "296-11993-1-ND" H 4950 6100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/CD4051BPWR/296-11993-1-ND/390442" H 4950 6100 50  0001 C CNN "DistLink"
	1    4950 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60A25F9A
P 5800 6600
AR Path="/60A25F9A" Ref="C?"  Part="1" 
AR Path="/6093B89C/60A25F9A" Ref="C?"  Part="1" 
AR Path="/60958BFE/60A25F9A" Ref="C7"  Part="1" 
F 0 "C7" H 5600 6550 50  0000 C CNN
F 1 "100n" H 5600 6650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5838 6450 50  0001 C CNN
F 3 "~" H 5800 6600 50  0001 C CNN
F 4 "Ceramic Capacitor" H 5800 6600 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 5800 6600 50  0001 C CNN "Description"
F 6 "Yes" H 5800 6600 50  0001 C CNN "Place"
F 7 "Digikey" H 5800 6600 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 5800 6600 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 5800 6600 50  0001 C CNN "DistLink"
	1    5800 6600
	-1   0    0    1   
$EndComp
Text HLabel 4450 6500 0    50   Input ~ 0
A
Text HLabel 4450 6600 0    50   Input ~ 0
B
Text HLabel 4450 6700 0    50   Input ~ 0
C
Text HLabel 5750 5300 2    50   Output ~ 0
~OUT2~
$Comp
L Device:R R?
U 1 1 60A25FAA
P 5750 5150
AR Path="/60A25FAA" Ref="R?"  Part="1" 
AR Path="/60958BFE/60A25FAA" Ref="R3"  Part="1" 
F 0 "R3" H 5900 5200 50  0000 C CNN
F 1 "10k" H 5900 5100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 5150 50  0001 C CNN
F 3 "~" H 5750 5150 50  0001 C CNN
F 4 "Resistor" H 5750 5150 50  0001 C CNN "Device"
F 5 "RES SMD 10K OHM 1% 1/10W 0603" H 5750 5150 50  0001 C CNN "Description"
F 6 "Yes" H 5750 5150 50  0001 C CNN "Place"
F 7 "Digikey" H 5750 5150 50  0001 C CNN "Dist"
F 8 "311-10KLDCT-ND" H 5750 5150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-0710KL/311-10KLDCT-ND/2828135" H 5750 5150 50  0001 C CNN "DistLink"
	1    5750 5150
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q?
U 1 1 60A25FB6
P 5650 5500
AR Path="/60A25FB6" Ref="Q?"  Part="1" 
AR Path="/60958BFE/60A25FB6" Ref="Q3"  Part="1" 
F 0 "Q3" H 5841 5546 50  0000 L CNN
F 1 "MMBT3904" H 5841 5455 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5850 5425 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 5650 5500 50  0001 L CNN
F 4 "Bipolar Transistor" H 5650 5500 50  0001 C CNN "Device"
F 5 "TRANS NPN 40V 0.2A SOT23" H 5650 5500 50  0001 C CNN "Description"
F 6 "Yes" H 5650 5500 50  0001 C CNN "Place"
F 7 "Digikey" H 5650 5500 50  0001 C CNN "Dist"
F 8 "MMBT3904LT3GOSCT-ND" H 5650 5500 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/MMBT3904LT3G/MMBT3904LT3GOSCT-ND/1139814" H 5650 5500 50  0001 C CNN "DistLink"
	1    5650 5500
	1    0    0    -1  
$EndComp
Text HLabel 4950 5200 1    50   Input ~ 0
12V
Text HLabel 4950 7000 3    50   Input ~ 0
GND
Text HLabel 5050 7000 3    50   Input ~ 0
GND
Text HLabel 4450 6400 0    50   Input ~ 0
GND
Text HLabel 5750 5700 3    50   Input ~ 0
GND
Text HLabel 5800 6450 1    50   Input ~ 0
12V
Text HLabel 5750 5000 1    50   Input ~ 0
3V3
Text Label 4450 5700 2    50   ~ 0
IN17_POS
Text HLabel 5800 6750 3    50   Input ~ 0
GND
Text Label 4450 5600 2    50   ~ 0
IN18_POS
Text Label 4450 5500 2    50   ~ 0
IN19_POS
Text Label 4450 5800 2    50   ~ 0
IN20_POS
Text HLabel 4450 5900 0    50   Input ~ 0
GND
Text HLabel 4450 6000 0    50   Input ~ 0
GND
Text HLabel 4450 6100 0    50   Input ~ 0
GND
Text HLabel 4450 6200 0    50   Input ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
BUTTONS/GATES
$EndSCHEMATC
