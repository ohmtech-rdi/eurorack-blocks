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
L Device:R R1
U 1 1 5FF74120
P 4050 3400
F 0 "R1" V 3843 3400 50  0000 C CNN
F 1 "100k" V 3934 3400 50  0000 C CNN
F 2 "" V 3980 3400 50  0001 C CNN
F 3 "~" H 4050 3400 50  0001 C CNN
	1    4050 3400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF7469C
P 4500 3700
F 0 "#PWR?" H 4500 3450 50  0001 C CNN
F 1 "GND" V 4500 3500 50  0000 C CNN
F 2 "" H 4500 3700 50  0001 C CNN
F 3 "" H 4500 3700 50  0001 C CNN
	1    4500 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3400 3900 3400
$Comp
L Diode:1N4148 D1
U 1 1 613BAEEA
P 4500 3550
F 0 "D1" V 4454 3630 50  0000 L CNN
F 1 "1N4148" V 4545 3630 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4500 3375 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4500 3550 50  0001 C CNN
	1    4500 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 3400 4500 3400
Connection ~ 4500 3400
$Comp
L 4xxx:4051 U1
U 1 1 613B4F49
P 6250 4000
F 0 "U1" H 5800 3200 50  0000 L CNN
F 1 "4051" H 5750 3100 50  0000 L CNN
F 2 "" H 6250 4000 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 6250 4000 50  0001 C CNN
	1    6250 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 613B6E28
P 6250 4900
F 0 "#PWR?" H 6250 4650 50  0001 C CNN
F 1 "GND" V 6250 4700 50  0000 C CNN
F 2 "" H 6250 4900 50  0001 C CNN
F 3 "" H 6250 4900 50  0001 C CNN
	1    6250 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 613B71F5
P 6350 4900
F 0 "#PWR?" H 6350 4650 50  0001 C CNN
F 1 "GND" V 6350 4700 50  0000 C CNN
F 2 "" H 6350 4900 50  0001 C CNN
F 3 "" H 6350 4900 50  0001 C CNN
	1    6350 4900
	1    0    0    -1  
$EndComp
Text Notes 2450 3900 0    50   ~ 0
INPUT ranges theorically\nfrom -12V to +12V\n- Typically 5V for a gate\n- Can be 10V with Arturia Beatstep Pro
$Comp
L Device:R R3
U 1 1 613B8734
P 7300 3400
F 0 "R3" V 7093 3400 50  0000 C CNN
F 1 "100k" V 7184 3400 50  0000 C CNN
F 2 "" V 7230 3400 50  0001 C CNN
F 3 "~" H 7300 3400 50  0001 C CNN
	1    7300 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 613B8EDB
P 7650 3550
F 0 "R4" H 7500 3500 50  0000 C CNN
F 1 "1M" H 7500 3600 50  0000 C CNN
F 2 "" V 7580 3550 50  0001 C CNN
F 3 "~" H 7650 3550 50  0001 C CNN
	1    7650 3550
	-1   0    0    1   
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q1
U 1 1 613B9CE3
P 8100 3400
F 0 "Q1" H 8291 3446 50  0000 L CNN
F 1 "MMBT3904" H 8291 3355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 3325 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/2N3903-D.PDF" H 8100 3400 50  0001 L CNN
	1    8100 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 613BAEFD
P 8200 3600
F 0 "#PWR?" H 8200 3350 50  0001 C CNN
F 1 "GND" V 8200 3400 50  0000 C CNN
F 2 "" H 8200 3600 50  0001 C CNN
F 3 "" H 8200 3600 50  0001 C CNN
	1    8200 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 613BB520
P 7650 3700
F 0 "#PWR?" H 7650 3450 50  0001 C CNN
F 1 "GND" V 7650 3500 50  0000 C CNN
F 2 "" H 7650 3700 50  0001 C CNN
F 3 "" H 7650 3700 50  0001 C CNN
	1    7650 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 613BBA7F
P 8200 2950
F 0 "R5" H 8050 2900 50  0000 C CNN
F 1 "10k" H 8050 3000 50  0000 C CNN
F 2 "" V 8130 2950 50  0001 C CNN
F 3 "~" H 8200 2950 50  0001 C CNN
	1    8200 2950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 613BC156
P 8650 3150
F 0 "R6" V 8443 3150 50  0000 C CNN
F 1 "1k" V 8534 3150 50  0000 C CNN
F 2 "" V 8580 3150 50  0001 C CNN
F 3 "~" H 8650 3150 50  0001 C CNN
	1    8650 3150
	0    1    1    0   
$EndComp
Text GLabel 3400 3400 0    50   Input ~ 0
INPUT
Text GLabel 8800 3150 2    50   Output ~ 0
OUTPUT
Wire Notes Line
	6900 2400 9500 2400
Wire Notes Line
	9500 2400 9500 4600
Wire Notes Line
	9500 4600 6900 4600
Wire Notes Line
	6900 4600 6900 2400
Text Notes 9350 4500 2    100  ~ 0
DaisyPathSM
Text Notes 9350 3350 2    50   ~ 0
To STM32 GPIO
Wire Wire Line
	6750 3400 7150 3400
Wire Wire Line
	7450 3400 7650 3400
Connection ~ 7650 3400
Wire Wire Line
	7650 3400 7900 3400
Wire Wire Line
	8200 3100 8200 3150
Wire Wire Line
	8200 3150 8500 3150
Connection ~ 8200 3150
Wire Wire Line
	8200 3150 8200 3200
$Comp
L power:+3V3 #PWR?
U 1 1 613BE539
P 8200 2800
F 0 "#PWR?" H 8200 2650 50  0001 C CNN
F 1 "+3V3" H 8215 2973 50  0000 C CNN
F 2 "" H 8200 2800 50  0001 C CNN
F 3 "" H 8200 2800 50  0001 C CNN
	1    8200 2800
	1    0    0    -1  
$EndComp
Wire Notes Line
	2250 2300 2250 5550
Wire Notes Line
	2250 5550 6650 5550
Wire Notes Line
	6650 5550 6650 2300
Wire Notes Line
	6650 2300 2250 2300
Text Notes 2400 5400 0    100  ~ 0
Kivu12
Wire Wire Line
	4500 3400 5750 3400
$Comp
L power:+12V #PWR?
U 1 1 613B61F3
P 6250 3100
F 0 "#PWR?" H 6250 2950 50  0001 C CNN
F 1 "+12V" H 6265 3273 50  0000 C CNN
F 2 "" H 6250 3100 50  0001 C CNN
F 3 "" H 6250 3100 50  0001 C CNN
	1    6250 3100
	1    0    0    -1  
$EndComp
Text Notes 6000 3250 2    50   ~ 0
On input X0, the\nmax is 12 + 0.5V\nwhen powered with 12V
Text Notes 5650 4650 2    50   ~ 0
FAILURE\nAddress is in 3V3\nAnd minimum high threshold\nis around 7V when\npowered with 12V
Text Notes 2450 4450 0    50   ~ 0
When input is <0V\nThe 4051 inputs\nwill see -0.6V forward\nvoltage which is past\nthe absolute rating of the 4051
$EndSCHEMATC
