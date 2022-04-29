EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
U 1 1 60946352
P 4450 3750
AR Path="/60946352" Ref="U?"  Part="1" 
AR Path="/6093B89C/60946352" Ref="U1"  Part="1" 
F 0 "U1" H 4850 3550 50  0000 L CNN
F 1 "4051" H 4850 3450 50  0000 L CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 4450 3750 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 4450 3750 50  0001 C CNN
F 4 "Multiplexer" H 4450 3750 50  0001 C CNN "Device"
F 5 "IC MUX/DEMUX 8X1 16TSSOP" H 4450 3750 50  0001 C CNN "Description"
F 6 "Yes" H 4450 3750 50  0001 C CNN "Place"
F 7 "Digikey" H 4450 3750 50  0001 C CNN "Dist"
F 8 "296-11993-1-ND" H 4450 3750 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/CD4051BPWR/296-11993-1-ND/390442" H 4450 3750 50  0001 C CNN "DistLink"
	1    4450 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60946382
P 5300 4250
AR Path="/60946382" Ref="C?"  Part="1" 
AR Path="/6093B89C/60946382" Ref="C3"  Part="1" 
F 0 "C3" H 5100 4200 50  0000 C CNN
F 1 "100n" H 5100 4300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5338 4100 50  0001 C CNN
F 3 "~" H 5300 4250 50  0001 C CNN
F 4 "Ceramic Capacitor" H 5300 4250 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 5300 4250 50  0001 C CNN "Description"
F 6 "Yes" H 5300 4250 50  0001 C CNN "Place"
F 7 "Digikey" H 5300 4250 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 5300 4250 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 5300 4250 50  0001 C CNN "DistLink"
	1    5300 4250
	-1   0    0    1   
$EndComp
$Comp
L 4xxx:4051 U?
U 1 1 60946394
P 6950 3750
AR Path="/60946394" Ref="U?"  Part="1" 
AR Path="/6093B89C/60946394" Ref="U2"  Part="1" 
F 0 "U2" H 7350 3550 50  0000 L CNN
F 1 "4051" H 7350 3450 50  0000 L CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 6950 3750 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 6950 3750 50  0001 C CNN
F 4 "Multiplexer" H 6950 3750 50  0001 C CNN "Device"
F 5 "IC MUX/DEMUX 8X1 16TSSOP" H 6950 3750 50  0001 C CNN "Description"
F 6 "Yes" H 6950 3750 50  0001 C CNN "Place"
F 7 "Digikey" H 6950 3750 50  0001 C CNN "Dist"
F 8 "296-11993-1-ND" H 6950 3750 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/texas-instruments/CD4051BPWR/296-11993-1-ND/390442" H 6950 3750 50  0001 C CNN "DistLink"
	1    6950 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 609463C6
P 7800 4250
AR Path="/609463C6" Ref="C?"  Part="1" 
AR Path="/6093B89C/609463C6" Ref="C4"  Part="1" 
F 0 "C4" H 7600 4200 50  0000 C CNN
F 1 "100n" H 7600 4300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7838 4100 50  0001 C CNN
F 3 "~" H 7800 4250 50  0001 C CNN
F 4 "Ceramic Capacitor" H 7800 4250 50  0001 C CNN "Device"
F 5 "CAP CER 0.1UF 25V X7R 0603" H 7800 4250 50  0001 C CNN "Description"
F 6 "Yes" H 7800 4250 50  0001 C CNN "Place"
F 7 "Digikey" H 7800 4250 50  0001 C CNN "Dist"
F 8 "478-7018-1-ND" H 7800 4250 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/kemet/C0603C102J5GACTU/399-3293-1-ND/608488" H 7800 4250 50  0001 C CNN "DistLink"
	1    7800 4250
	-1   0    0    1   
$EndComp
Text Notes 4800 2550 0    50   ~ 0
Inputs, Outputs, A, B and C are from GND to VDD.
Text HLabel 3950 3550 0    50   Input ~ 0
IN1
Text HLabel 3950 3750 0    50   Input ~ 0
IN2
Text HLabel 3950 3850 0    50   Input ~ 0
IN3
Text HLabel 3950 3650 0    50   Input ~ 0
IN4
Text HLabel 3950 3350 0    50   Input ~ 0
IN5
Text HLabel 3950 3250 0    50   Input ~ 0
IN6
Text HLabel 3950 3150 0    50   Input ~ 0
IN7
Text HLabel 6450 3550 0    50   Input ~ 0
IN8
Text HLabel 3950 4150 0    50   Input ~ 0
A
Text HLabel 3950 4250 0    50   Input ~ 0
B
Text HLabel 3950 4350 0    50   Input ~ 0
C
Text HLabel 4950 3150 2    50   Output ~ 0
OUT1
Text HLabel 6450 4150 0    50   Input ~ 0
A
Text HLabel 6450 4250 0    50   Input ~ 0
B
Text HLabel 6450 4350 0    50   Input ~ 0
C
Text HLabel 7450 3150 2    50   Output ~ 0
OUT2
Text HLabel 4450 2850 1    50   Input ~ 0
VDD
Text HLabel 6950 2850 1    50   Input ~ 0
VDD
Text HLabel 5300 4100 1    50   Input ~ 0
VDD
Text HLabel 7800 4100 1    50   Input ~ 0
VDD
Text HLabel 4450 4650 3    50   Input ~ 0
GND
Text HLabel 4550 4650 3    50   Input ~ 0
GND
Text HLabel 5300 4400 3    50   Input ~ 0
GND
Text HLabel 6950 4650 3    50   Input ~ 0
GND
Text HLabel 7050 4650 3    50   Input ~ 0
GND
Text HLabel 3950 4050 0    50   Input ~ 0
GND
Text HLabel 6450 4050 0    50   Input ~ 0
GND
Text HLabel 7800 4400 3    50   Input ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
POTS
Text HLabel 6450 3750 0    50   Input ~ 0
IN9
Text HLabel 6450 3850 0    50   Input ~ 0
IN10
Text HLabel 6450 3650 0    50   Input ~ 0
IN11
Text HLabel 6450 3350 0    50   Input ~ 0
IN12
Text HLabel 6450 3450 0    50   Input ~ 0
GND
Text HLabel 6450 3150 0    50   Input ~ 0
GND
Text HLabel 6450 3250 0    50   Input ~ 0
GND
Text HLabel 3950 3450 0    50   Input ~ 0
GND
$EndSCHEMATC
