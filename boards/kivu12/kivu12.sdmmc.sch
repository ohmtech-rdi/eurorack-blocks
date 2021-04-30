EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L Device:Jumper_NC_Dual JP5
U 1 1 60AA9B96
P 4000 2500
F 0 "JP5" H 4000 2739 50  0000 C CNN
F 1 "CLK" H 4000 2648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 4000 2500 50  0001 C CNN
F 3 "~" H 4000 2500 50  0001 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
Text HLabel 3750 2500 0    50   Output ~ 0
SD_CLK
Text Label 4250 2500 0    50   ~ 0
MMC_CLK
Text HLabel 4000 2600 3    50   Input ~ 0
OUT_CLK
$Comp
L Device:Jumper_NC_Dual JP6
U 1 1 60AAD163
P 5500 2500
F 0 "JP6" H 5500 2739 50  0000 C CNN
F 1 "CMD" H 5500 2648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 5500 2500 50  0001 C CNN
F 3 "~" H 5500 2500 50  0001 C CNN
	1    5500 2500
	1    0    0    -1  
$EndComp
Text HLabel 5250 2500 0    50   Output ~ 0
SD_CMD
Text Label 5750 2500 0    50   ~ 0
MMC_CMD
Text HLabel 5500 2600 3    50   Input ~ 0
OUT_CMD
$Comp
L Device:Jumper_NC_Dual JP7
U 1 1 60AAEFC4
P 4000 3500
F 0 "JP7" H 4000 3739 50  0000 C CNN
F 1 "D0" H 4000 3648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 4000 3500 50  0001 C CNN
F 3 "~" H 4000 3500 50  0001 C CNN
	1    4000 3500
	1    0    0    -1  
$EndComp
Text HLabel 3750 3500 0    50   BiDi ~ 0
SD_D0
Text Label 4250 3500 0    50   ~ 0
MMC_D0
Text HLabel 4000 3600 3    50   BiDi ~ 0
OUT_DO
$Comp
L Device:Jumper_NC_Dual JP8
U 1 1 60AAEFCD
P 5500 3500
F 0 "JP8" H 5500 3739 50  0000 C CNN
F 1 "D1" H 5500 3648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 5500 3500 50  0001 C CNN
F 3 "~" H 5500 3500 50  0001 C CNN
	1    5500 3500
	1    0    0    -1  
$EndComp
Text HLabel 5250 3500 0    50   BiDi ~ 0
SD_D1
Text Label 5750 3500 0    50   ~ 0
MMC_D1
Text HLabel 5500 3600 3    50   BiDi ~ 0
OUT_D1
$Comp
L Device:Jumper_NC_Dual JP9
U 1 1 60AB12D6
P 4000 4500
F 0 "JP9" H 4000 4739 50  0000 C CNN
F 1 "D2" H 4000 4648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 4000 4500 50  0001 C CNN
F 3 "~" H 4000 4500 50  0001 C CNN
	1    4000 4500
	1    0    0    -1  
$EndComp
Text HLabel 3750 4500 0    50   BiDi ~ 0
SD_D2
Text Label 4250 4500 0    50   ~ 0
MMC_D2
Text HLabel 4000 4600 3    50   BiDi ~ 0
OUT_D2
$Comp
L Device:Jumper_NC_Dual JP10
U 1 1 60AB12DF
P 5500 4500
F 0 "JP10" H 5500 4739 50  0000 C CNN
F 1 "D3" H 5500 4648 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x03_P1.27mm_Vertical" H 5500 4500 50  0001 C CNN
F 3 "~" H 5500 4500 50  0001 C CNN
	1    5500 4500
	1    0    0    -1  
$EndComp
Text HLabel 5250 4500 0    50   BiDi ~ 0
SD_D3
Text Label 5750 4500 0    50   ~ 0
MMC_D3
Text HLabel 5500 4600 3    50   BiDi ~ 0
OUT_D3
Text HLabel 7350 3050 0    50   Input ~ 0
3V3
Text HLabel 7350 3250 0    50   Input ~ 0
GND
Text Notes 7450 7000 0    276  ~ 0
SD/MMC
$Comp
L Connector:Micro_SD_Card J6
U 1 1 60B2E16C
P 8250 3050
F 0 "J6" H 8200 3767 50  0000 C CNN
F 1 "Micro_SD_Card" H 8200 3676 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Wuerth_693072010801" H 9400 3350 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 8250 3050 50  0001 C CNN
F 4 "PC Card Socket Connector" H 8250 3050 50  0001 C CNN "Device"
F 5 "CONN MICRO SD CARD HINGED TYPE" H 8250 3050 50  0001 C CNN "Description"
F 6 "Yes" H 8250 3050 50  0001 C CNN "Place"
F 7 "Digikey" H 8250 3050 50  0001 C CNN "Dist"
F 8 "732-3820-1-ND" H 8250 3050 50  0001 C CNN "DistPartNumber"
F 9 "https://www.digikey.de/product-detail/en/würth-elektronik/693072010801/732-3820-1-ND/3124605" H 8250 3050 50  0001 C CNN "DistLink"
	1    8250 3050
	1    0    0    -1  
$EndComp
Text Label 7350 2950 2    50   ~ 0
MMC_CMD
Text Label 7350 3150 2    50   ~ 0
MMC_CLK
Text Label 7350 3350 2    50   ~ 0
MMC_D0
Text Label 7350 3450 2    50   ~ 0
MMC_D1
Text Label 7350 2750 2    50   ~ 0
MMC_D2
Text Label 7350 2850 2    50   ~ 0
MMC_D3
Text HLabel 9050 3650 2    50   Input ~ 0
GND
$EndSCHEMATC
