EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 8
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
L Device:R_Small R?
U 1 1 60964AFC
P 5550 2800
AR Path="/60964AFC" Ref="R?"  Part="1" 
AR Path="/60963995/60964AFC" Ref="R64"  Part="1" 
F 0 "R64" V 5746 2800 50  0000 C CNN
F 1 "10" V 5655 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5550 2800 50  0001 C CNN
F 3 "~" H 5550 2800 50  0001 C CNN
F 4 "Resistor" H 5550 2800 50  0001 C CNN "Device"
F 5 "RES SMD 10 OHM 1% 1/10W 0603" H 5550 2800 50  0001 C CNN "Description"
F 6 "Yes" H 5550 2800 50  0001 C CNN "Place"
F 7 "Digikey" H 5550 2800 50  0001 C CNN "Dist"
F 8 "311-10LDCT-ND" H 5550 2800 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-0710RL/311-10LDCT-ND/2828514" H 5550 2800 50  0001 C CNN "DistLink"
	1    5550 2800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60964B04
P 5550 3150
AR Path="/60964B04" Ref="R?"  Part="1" 
AR Path="/60963995/60964B04" Ref="R65"  Part="1" 
F 0 "R65" V 5746 3150 50  0000 C CNN
F 1 "33" V 5655 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5550 3150 50  0001 C CNN
F 3 "~" H 5550 3150 50  0001 C CNN
F 4 "Resistor" H 5550 3150 50  0001 C CNN "Device"
F 5 "RES SMD 33 OHM 5% 1/10W 0603" H 5550 3150 50  0001 C CNN "Description"
F 6 "Yes" H 5550 3150 50  0001 C CNN "Place"
F 7 "Digikey" H 5550 3150 50  0001 C CNN "Dist"
F 8 "YAG3666CT-ND" H 5550 3150 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603JR-0733RL/YAG3666CT-ND/6006515" H 5550 3150 50  0001 C CNN "DistLink"
	1    5550 3150
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 60964B0A
P 5450 3150
AR Path="/60964B0A" Ref="#PWR?"  Part="1" 
AR Path="/60963995/60964B0A" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 5450 3000 50  0001 C CNN
F 1 "+3V3" V 5450 3350 50  0000 C CNN
F 2 "" H 5450 3150 50  0001 C CNN
F 3 "" H 5450 3150 50  0001 C CNN
	1    5450 3150
	0    -1   -1   0   
$EndComp
Text HLabel 3800 4200 0    50   Input ~ 0
MIDI_IN_TIP
Text HLabel 3800 3700 0    50   Input ~ 0
MIDI_IN_RING
Text HLabel 5450 2800 0    50   Input ~ 0
MIDI_OUT
Text HLabel 5650 2800 2    50   Output ~ 0
MIDI_OUT_TIP
Text HLabel 5650 3150 2    50   Output ~ 0
MIDI_OUT_RING
$Comp
L Device:Jumper_NC_Dual JP1
U 1 1 60ABAB7B
P 3800 3950
F 0 "JP1" V 3754 4051 50  0000 L CNN
F 1 "Source" V 3845 4051 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 3800 3950 50  0001 C CNN
F 3 "~" H 3800 3950 50  0001 C CNN
	1    3800 3950
	0    -1   1    0   
$EndComp
$Comp
L Device:R R66
U 1 1 60ABC7AA
P 4300 3950
F 0 "R66" V 4093 3950 50  0000 C CNN
F 1 "220" V 4184 3950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4230 3950 50  0001 C CNN
F 3 "~" H 4300 3950 50  0001 C CNN
F 4 "Resistor" H 4300 3950 50  0001 C CNN "Device"
F 5 "RES SMD 220 OHM 1% 1/10W 0603" H 4300 3950 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3950 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3950 50  0001 C CNN "Dist"
F 8 "YAG3580CT-ND" H 4300 3950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-07220RL/YAG3580CT-ND/6006429" H 4300 3950 50  0001 C CNN "DistLink"
	1    4300 3950
	0    1    1    0   
$EndComp
Text Notes 3850 3850 0    50   ~ 0
TYPE A
Text Notes 3850 4100 0    50   ~ 0
TYPE B
Text HLabel 3800 4900 0    50   Input ~ 0
MIDI_IN_RING
Text HLabel 3800 4400 0    50   Input ~ 0
MIDI_IN_TIP
$Comp
L Device:Jumper_NC_Dual JP2
U 1 1 60ABF41E
P 3800 4650
F 0 "JP2" V 3754 4751 50  0000 L CNN
F 1 "Sink" V 3845 4751 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 3800 4650 50  0001 C CNN
F 3 "~" H 3800 4650 50  0001 C CNN
	1    3800 4650
	0    -1   1    0   
$EndComp
Text Notes 3850 4550 0    50   ~ 0
TYPE A
Text Notes 3850 4800 0    50   ~ 0
TYPE B
Wire Wire Line
	3900 3950 4150 3950
$Comp
L Diode:1N4148WS D21
U 1 1 60AC05A3
P 4500 4350
F 0 "D21" V 4454 4430 50  0000 L CNN
F 1 "1N4148WS" V 4545 4430 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 4500 4175 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85751/1n4148ws.pdf" H 4500 4350 50  0001 C CNN
F 4 "Rectifier Diode" H 4500 4350 50  0001 C CNN "Device"
F 5 "DIODE GEN PURP 75V 150MA SOD323F" H 4500 4350 50  0001 C CNN "Description"
F 6 "Yes" H 4500 4350 50  0001 C CNN "Place"
F 7 "Digikey" H 4500 4350 50  0001 C CNN "Dist"
F 8 "1N4148WSFSCT-ND" H 4500 4350 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/1N4148WS/1N4148WSFSCT-ND/1873821" H 4500 4350 50  0001 C CNN "DistLink"
	1    4500 4350
	0    1    1    0   
$EndComp
$Comp
L Isolator:H11L1 U8
U 1 1 60AC1C51
P 5400 4350
F 0 "U8" H 5700 4250 50  0000 L CNN
F 1 "H11L1" H 5700 4150 50  0000 L CNN
F 2 "Package_DIP:DIP-6_W8.89mm_SMDSocket_LongPads" H 5310 4350 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/H11L3M-D.PDF" H 5310 4350 50  0001 C CNN
F 4 "Optoisolator" H 5400 4350 50  0001 C CNN "Device"
F 5 "OPTOISO 4.17KV OPN COLL 6SMD" H 5400 4350 50  0001 C CNN "Description"
F 6 "Yes" H 5400 4350 50  0001 C CNN "Place"
F 7 "Digikey" H 5400 4350 50  0001 C CNN "Dist"
F 8 "H11L1SR2MCT-ND" H 5400 4350 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/on-semiconductor/H11L1SR2M/H11L1SR2MCT-ND/458959" H 5400 4350 50  0001 C CNN "DistLink"
	1    5400 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4650 4500 4650
Wire Wire Line
	5100 4650 5100 4450
Wire Wire Line
	4500 4650 4500 4500
Connection ~ 4500 4650
Wire Wire Line
	4500 4650 5100 4650
Wire Wire Line
	4450 3950 4500 3950
Wire Wire Line
	5100 3950 5100 4250
Wire Wire Line
	4500 4200 4500 3950
Connection ~ 4500 3950
Wire Wire Line
	4500 3950 5100 3950
Text HLabel 5400 4650 3    50   Input ~ 0
GND
Text HLabel 5400 4050 1    50   Input ~ 0
3V3
$Comp
L Device:R R67
U 1 1 60AC4AFB
P 5850 4200
F 0 "R67" H 5780 4154 50  0000 R CNN
F 1 "270" H 5780 4245 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5780 4200 50  0001 C CNN
F 3 "~" H 5850 4200 50  0001 C CNN
F 4 "Resistor" H 5850 4200 50  0001 C CNN "Device"
F 5 "RES SMD 270 OHM 5% 1/10W 0603" H 5850 4200 50  0001 C CNN "Description"
F 6 "Yes" H 5850 4200 50  0001 C CNN "Place"
F 7 "Digikey" H 5850 4200 50  0001 C CNN "Dist"
F 8 "13-AC0603JR-07270RLCT-ND" H 5850 4200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603JR-07270RL/13-AC0603JR-07270RLCT-ND/12708252" H 5850 4200 50  0001 C CNN "DistLink"
	1    5850 4200
	-1   0    0    1   
$EndComp
Text HLabel 6100 4350 2    50   Output ~ 0
MIDI_IN
Wire Wire Line
	5700 4350 5850 4350
Connection ~ 5850 4350
Wire Wire Line
	5850 4350 6100 4350
Text HLabel 5850 4050 1    50   Input ~ 0
3V3
$Comp
L Device:C C?
U 1 1 60AC9B65
P 6200 4950
AR Path="/60AC9B65" Ref="C?"  Part="1" 
AR Path="/6093B89C/60AC9B65" Ref="C?"  Part="1" 
AR Path="/60958BFE/60AC9B65" Ref="C?"  Part="1" 
AR Path="/60963995/60AC9B65" Ref="C10"  Part="1" 
F 0 "C10" H 6000 4900 50  0000 C CNN
F 1 "100n" H 6000 5000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6238 4800 50  0001 C CNN
F 3 "~" H 6200 4950 50  0001 C CNN
F 4 "Ceramic Capacitor" H 6200 4950 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 6200 4950 50  0001 C CNN "Description"
F 6 "Yes" H 6200 4950 50  0001 C CNN "Place"
F 7 "Digikey" H 6200 4950 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 6200 4950 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 6200 4950 50  0001 C CNN "DistLink"
	1    6200 4950
	-1   0    0    1   
$EndComp
Text HLabel 6200 4800 1    50   Input ~ 0
3V3
Text HLabel 6200 5100 3    50   Input ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
MIDI
$EndSCHEMATC
