EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 7500 2800 1    50   Input ~ 0
3V3
Text HLabel 7500 4900 3    50   Input ~ 0
GND
Text HLabel 6800 4000 0    50   Input ~ 0
3V3
Text HLabel 6800 4100 0    50   Input ~ 0
GND
Text HLabel 6800 4200 0    50   Input ~ 0
GND
Text HLabel 6800 4300 0    50   Input ~ 0
GND
Text HLabel 6800 4400 0    50   Input ~ 0
GND
Text HLabel 6800 4500 0    50   Input ~ 0
GND
Text HLabel 6800 3400 0    50   Input ~ 0
GND
Text HLabel 6800 3300 0    50   Input ~ 0
GND
Text HLabel 6800 3100 0    50   Input ~ 0
SCL
Text HLabel 6800 3200 0    50   Input ~ 0
SDA
$Comp
L Device:C C?
U 1 1 60B00837
P 7850 2550
AR Path="/60B00837" Ref="C?"  Part="1" 
AR Path="/6093B89C/60B00837" Ref="C?"  Part="1" 
AR Path="/60958BFE/60B00837" Ref="C?"  Part="1" 
AR Path="/60963995/60B00837" Ref="C?"  Part="1" 
AR Path="/609AFC8B/60B00837" Ref="C9"  Part="1" 
F 0 "C9" H 7650 2500 50  0000 C CNN
F 1 "100n" H 7650 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7888 2400 50  0001 C CNN
F 3 "~" H 7850 2550 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7850 2550 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 7850 2550 50  0001 C CNN "Description"
F 6 "Yes" H 7850 2550 50  0001 C CNN "Place"
F 7 "Digikey" H 7850 2550 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 7850 2550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 7850 2550 50  0001 C CNN "DistLink"
	1    7850 2550
	-1   0    0    1   
$EndComp
Text HLabel 7850 2400 1    50   Input ~ 0
3V3
Text HLabel 7850 2700 3    50   Input ~ 0
GND
Text HLabel 8800 3100 2    50   Output ~ 0
OUT17
Wire Wire Line
	8400 3100 8800 3100
Text HLabel 8800 3200 2    50   Output ~ 0
OUT18
Wire Wire Line
	8400 3200 8800 3200
Text HLabel 8800 3300 2    50   Output ~ 0
OUT19
Wire Wire Line
	8400 3300 8800 3300
Text HLabel 8800 3400 2    50   Output ~ 0
OUT20
Wire Wire Line
	8400 3400 8800 3400
NoConn ~ 8200 3500
NoConn ~ 8200 3600
NoConn ~ 8200 3700
NoConn ~ 8200 3800
NoConn ~ 8200 3900
NoConn ~ 8200 4000
NoConn ~ 8200 4100
NoConn ~ 8200 4200
NoConn ~ 8200 4300
NoConn ~ 8200 4400
NoConn ~ 8200 4500
NoConn ~ 8200 4600
Text Notes 7450 7000 0    276  ~ 0
LEDS
Wire Wire Line
	4400 4600 4800 4600
Text HLabel 4800 4600 2    50   Output ~ 0
OUT16
Wire Wire Line
	4400 4500 4800 4500
Text HLabel 4800 4500 2    50   Output ~ 0
OUT15
Wire Wire Line
	4400 4400 4800 4400
Text HLabel 4800 4400 2    50   Output ~ 0
OUT14
Wire Wire Line
	4400 4300 4800 4300
Text HLabel 4800 4300 2    50   Output ~ 0
OUT13
Wire Wire Line
	4400 4200 4800 4200
Text HLabel 4800 4200 2    50   Output ~ 0
OUT12
Wire Wire Line
	4400 4100 4800 4100
Text HLabel 4800 4100 2    50   Output ~ 0
OUT11
Wire Wire Line
	4400 4000 4800 4000
Text HLabel 4800 4000 2    50   Output ~ 0
OUT10
Wire Wire Line
	4400 3900 4800 3900
Text HLabel 4800 3900 2    50   Output ~ 0
OUT9
Wire Wire Line
	4400 3800 4800 3800
Text HLabel 4800 3100 2    50   Output ~ 0
OUT8
Wire Wire Line
	4400 3700 4800 3700
Text HLabel 4800 3200 2    50   Output ~ 0
OUT7
Wire Wire Line
	4400 3600 4800 3600
Text HLabel 4800 3300 2    50   Output ~ 0
OUT6
Wire Wire Line
	4400 3500 4800 3500
Text HLabel 4800 3400 2    50   Output ~ 0
OUT5
Wire Wire Line
	4400 3400 4800 3400
Text HLabel 4800 3500 2    50   Output ~ 0
OUT4
Wire Wire Line
	4400 3300 4800 3300
Text HLabel 4800 3600 2    50   Output ~ 0
OUT3
Wire Wire Line
	4400 3200 4800 3200
Text HLabel 4800 3700 2    50   Output ~ 0
OUT2
Wire Wire Line
	4400 3100 4800 3100
$Comp
L Device:R_Small R44
U 1 1 60AE1A7E
P 4300 3100
F 0 "R44" V 4250 3300 50  0000 C CNN
F 1 "1K" V 4250 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3100 50  0001 C CNN
F 3 "~" H 4300 3100 50  0001 C CNN
F 4 "Resistor" H 4300 3100 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3100 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3100 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3100 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3100 50  0001 C CNN "DistLink"
	1    4300 3100
	0    1    1    0   
$EndComp
Text HLabel 4800 3800 2    50   Output ~ 0
OUT1
Text HLabel 3850 2700 3    50   Input ~ 0
GND
Text HLabel 3850 2400 1    50   Input ~ 0
3V3
$Comp
L Device:C C?
U 1 1 60ADC737
P 3850 2550
AR Path="/60ADC737" Ref="C?"  Part="1" 
AR Path="/6093B89C/60ADC737" Ref="C?"  Part="1" 
AR Path="/60958BFE/60ADC737" Ref="C?"  Part="1" 
AR Path="/60963995/60ADC737" Ref="C?"  Part="1" 
AR Path="/609AFC8B/60ADC737" Ref="C8"  Part="1" 
F 0 "C8" H 3650 2500 50  0000 C CNN
F 1 "100n" H 3650 2600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3888 2400 50  0001 C CNN
F 3 "~" H 3850 2550 50  0001 C CNN
F 4 "Ceramic Capacitor" H 3850 2550 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 3850 2550 50  0001 C CNN "Description"
F 6 "Yes" H 3850 2550 50  0001 C CNN "Place"
F 7 "Digikey" H 3850 2550 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 3850 2550 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 3850 2550 50  0001 C CNN "DistLink"
	1    3850 2550
	-1   0    0    1   
$EndComp
Text HLabel 2800 3200 0    50   Input ~ 0
SDA
Text HLabel 2800 3100 0    50   Input ~ 0
SCL
Text HLabel 2800 3300 0    50   Input ~ 0
GND
Text HLabel 2800 3400 0    50   Input ~ 0
GND
Text HLabel 2800 4500 0    50   Input ~ 0
GND
Text HLabel 2800 4400 0    50   Input ~ 0
GND
Text HLabel 2800 4300 0    50   Input ~ 0
GND
Text HLabel 2800 4200 0    50   Input ~ 0
GND
Text HLabel 2800 4100 0    50   Input ~ 0
GND
Text HLabel 2800 4000 0    50   Input ~ 0
GND
Text HLabel 3500 4900 3    50   Input ~ 0
GND
Text HLabel 3500 2800 1    50   Input ~ 0
3V3
$Comp
L Driver_LED:PCA9685PW U6
U 1 1 60AD63F1
P 3500 3800
F 0 "U6" H 3850 2800 50  0000 C CNN
F 1 "PCA9685PW" H 4000 2700 50  0000 C CNN
F 2 "Package_SO:TSSOP-28_4.4x9.7mm_P0.65mm" H 3525 2825 50  0001 L CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCA9685.pdf" H 3100 4500 50  0001 C CNN
F 4 "PMIC - LED Driver" H 3500 3800 50  0001 C CNN "Device"
F 5 "IC LED DRIVER RGBA 28-TSSOP" H 3500 3800 50  0001 C CNN "Description"
F 6 "Yes" H 3500 3800 50  0001 C CNN "Place"
F 7 "Digikey" H 3500 3800 50  0001 C CNN "Dist"
F 8 "568-11925-1-ND" H 3500 3800 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/nxp-usa-inc/PCA9685PW-118/568-11925-1-ND/5221902" H 3500 3800 50  0001 C CNN "DistLink"
	1    3500 3800
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:PCA9685PW U7
U 1 1 608D963A
P 7500 3800
F 0 "U7" H 7850 2800 50  0000 C CNN
F 1 "PCA9685PW" H 8000 2700 50  0000 C CNN
F 2 "Package_SO:TSSOP-28_4.4x9.7mm_P0.65mm" H 7525 2825 50  0001 L CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCA9685.pdf" H 7100 4500 50  0001 C CNN
F 4 "PMIC - LED Driver" H 7500 3800 50  0001 C CNN "Device"
F 5 "IC LED DRIVER RGBA 28-TSSOP" H 7500 3800 50  0001 C CNN "Description"
F 6 "Yes" H 7500 3800 50  0001 C CNN "Place"
F 7 "Digikey" H 7500 3800 50  0001 C CNN "Dist"
F 8 "568-11925-1-ND" H 7500 3800 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/nxp-usa-inc/PCA9685PW-118/568-11925-1-ND/5221902" H 7500 3800 50  0001 C CNN "DistLink"
	1    7500 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R45
U 1 1 608E26C6
P 4300 3200
F 0 "R45" V 4250 3400 50  0000 C CNN
F 1 "1K" V 4250 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3200 50  0001 C CNN
F 3 "~" H 4300 3200 50  0001 C CNN
F 4 "Resistor" H 4300 3200 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3200 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3200 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3200 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3200 50  0001 C CNN "DistLink"
	1    4300 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R46
U 1 1 608E30A7
P 4300 3300
F 0 "R46" V 4250 3500 50  0000 C CNN
F 1 "1K" V 4250 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3300 50  0001 C CNN
F 3 "~" H 4300 3300 50  0001 C CNN
F 4 "Resistor" H 4300 3300 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3300 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3300 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3300 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3300 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3300 50  0001 C CNN "DistLink"
	1    4300 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R47
U 1 1 608E4365
P 4300 3400
F 0 "R47" V 4250 3600 50  0000 C CNN
F 1 "1K" V 4250 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3400 50  0001 C CNN
F 3 "~" H 4300 3400 50  0001 C CNN
F 4 "Resistor" H 4300 3400 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3400 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3400 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3400 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3400 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3400 50  0001 C CNN "DistLink"
	1    4300 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R48
U 1 1 608E4776
P 4300 3500
F 0 "R48" V 4250 3700 50  0000 C CNN
F 1 "1K" V 4250 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3500 50  0001 C CNN
F 3 "~" H 4300 3500 50  0001 C CNN
F 4 "Resistor" H 4300 3500 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3500 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3500 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3500 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3500 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3500 50  0001 C CNN "DistLink"
	1    4300 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R49
U 1 1 608E4B02
P 4300 3600
F 0 "R49" V 4250 3800 50  0000 C CNN
F 1 "1K" V 4250 3950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3600 50  0001 C CNN
F 3 "~" H 4300 3600 50  0001 C CNN
F 4 "Resistor" H 4300 3600 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3600 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3600 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3600 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3600 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3600 50  0001 C CNN "DistLink"
	1    4300 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R50
U 1 1 608E4F52
P 4300 3700
F 0 "R50" V 4250 3900 50  0000 C CNN
F 1 "1K" V 4250 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3700 50  0001 C CNN
F 3 "~" H 4300 3700 50  0001 C CNN
F 4 "Resistor" H 4300 3700 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3700 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3700 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3700 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3700 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3700 50  0001 C CNN "DistLink"
	1    4300 3700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R51
U 1 1 608E530F
P 4300 3800
F 0 "R51" V 4250 4000 50  0000 C CNN
F 1 "1K" V 4250 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3800 50  0001 C CNN
F 3 "~" H 4300 3800 50  0001 C CNN
F 4 "Resistor" H 4300 3800 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3800 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3800 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3800 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3800 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3800 50  0001 C CNN "DistLink"
	1    4300 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R52
U 1 1 608E5754
P 4300 3900
F 0 "R52" V 4250 4100 50  0000 C CNN
F 1 "1K" V 4250 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 3900 50  0001 C CNN
F 3 "~" H 4300 3900 50  0001 C CNN
F 4 "Resistor" H 4300 3900 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 3900 50  0001 C CNN "Description"
F 6 "Yes" H 4300 3900 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 3900 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 3900 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 3900 50  0001 C CNN "DistLink"
	1    4300 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R53
U 1 1 608E5AD4
P 4300 4000
F 0 "R53" V 4250 4200 50  0000 C CNN
F 1 "1K" V 4250 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4000 50  0001 C CNN
F 3 "~" H 4300 4000 50  0001 C CNN
F 4 "Resistor" H 4300 4000 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4000 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4000 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4000 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4000 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4000 50  0001 C CNN "DistLink"
	1    4300 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R54
U 1 1 608E5ECD
P 4300 4100
F 0 "R54" V 4250 4300 50  0000 C CNN
F 1 "1K" V 4250 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4100 50  0001 C CNN
F 3 "~" H 4300 4100 50  0001 C CNN
F 4 "Resistor" H 4300 4100 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4100 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4100 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4100 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4100 50  0001 C CNN "DistLink"
	1    4300 4100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R55
U 1 1 608E632D
P 4300 4200
F 0 "R55" V 4250 4400 50  0000 C CNN
F 1 "1K" V 4250 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4200 50  0001 C CNN
F 3 "~" H 4300 4200 50  0001 C CNN
F 4 "Resistor" H 4300 4200 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4200 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4200 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4200 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4200 50  0001 C CNN "DistLink"
	1    4300 4200
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R56
U 1 1 608E6725
P 4300 4300
F 0 "R56" V 4250 4500 50  0000 C CNN
F 1 "1K" V 4250 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4300 50  0001 C CNN
F 3 "~" H 4300 4300 50  0001 C CNN
F 4 "Resistor" H 4300 4300 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4300 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4300 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4300 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4300 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4300 50  0001 C CNN "DistLink"
	1    4300 4300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R57
U 1 1 608E6A02
P 4300 4400
F 0 "R57" V 4250 4600 50  0000 C CNN
F 1 "1K" V 4250 4750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4400 50  0001 C CNN
F 3 "~" H 4300 4400 50  0001 C CNN
F 4 "Resistor" H 4300 4400 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4400 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4400 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4400 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4400 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4400 50  0001 C CNN "DistLink"
	1    4300 4400
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R58
U 1 1 608E6E41
P 4300 4500
F 0 "R58" V 4250 4700 50  0000 C CNN
F 1 "1K" V 4250 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4500 50  0001 C CNN
F 3 "~" H 4300 4500 50  0001 C CNN
F 4 "Resistor" H 4300 4500 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4500 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4500 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4500 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4500 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4500 50  0001 C CNN "DistLink"
	1    4300 4500
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R59
U 1 1 608E71E8
P 4300 4600
F 0 "R59" V 4250 4800 50  0000 C CNN
F 1 "1K" V 4250 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4300 4600 50  0001 C CNN
F 3 "~" H 4300 4600 50  0001 C CNN
F 4 "Resistor" H 4300 4600 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 4300 4600 50  0001 C CNN "Description"
F 6 "Yes" H 4300 4600 50  0001 C CNN "Place"
F 7 "Digikey" H 4300 4600 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 4300 4600 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 4300 4600 50  0001 C CNN "DistLink"
	1    4300 4600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R60
U 1 1 608E8FF5
P 8300 3100
F 0 "R60" V 8250 3300 50  0000 C CNN
F 1 "1K" V 8250 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 3100 50  0001 C CNN
F 3 "~" H 8300 3100 50  0001 C CNN
F 4 "Resistor" H 8300 3100 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 8300 3100 50  0001 C CNN "Description"
F 6 "Yes" H 8300 3100 50  0001 C CNN "Place"
F 7 "Digikey" H 8300 3100 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 8300 3100 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 8300 3100 50  0001 C CNN "DistLink"
	1    8300 3100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R61
U 1 1 608E988D
P 8300 3200
F 0 "R61" V 8250 3400 50  0000 C CNN
F 1 "1K" V 8250 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 3200 50  0001 C CNN
F 3 "~" H 8300 3200 50  0001 C CNN
F 4 "Resistor" H 8300 3200 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 8300 3200 50  0001 C CNN "Description"
F 6 "Yes" H 8300 3200 50  0001 C CNN "Place"
F 7 "Digikey" H 8300 3200 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 8300 3200 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 8300 3200 50  0001 C CNN "DistLink"
	1    8300 3200
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R62
U 1 1 608EA0AB
P 8300 3300
F 0 "R62" V 8250 3500 50  0000 C CNN
F 1 "1K" V 8250 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 3300 50  0001 C CNN
F 3 "~" H 8300 3300 50  0001 C CNN
F 4 "Resistor" H 8300 3300 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 8300 3300 50  0001 C CNN "Description"
F 6 "Yes" H 8300 3300 50  0001 C CNN "Place"
F 7 "Digikey" H 8300 3300 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 8300 3300 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 8300 3300 50  0001 C CNN "DistLink"
	1    8300 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R63
U 1 1 608EA55D
P 8300 3400
F 0 "R63" V 8250 3600 50  0000 C CNN
F 1 "1K" V 8250 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 3400 50  0001 C CNN
F 3 "~" H 8300 3400 50  0001 C CNN
F 4 "Resistor" H 8300 3400 50  0001 C CNN "Device"
F 5 "RES SMD 1K OHM 1% 1/10W 0603" H 8300 3400 50  0001 C CNN "Description"
F 6 "Yes" H 8300 3400 50  0001 C CNN "Place"
F 7 "Digikey" H 8300 3400 50  0001 C CNN "Dist"
F 8 "311-1KLDCT-ND" H 8300 3400 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/yageo/AC0603FR-071KL/311-1KLDCT-ND/2828140" H 8300 3400 50  0001 C CNN "DistLink"
	1    8300 3400
	0    1    1    0   
$EndComp
$EndSCHEMATC
