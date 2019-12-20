EESchema Schematic File Version 5
LIBS:sifflet-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4850 4700 4850 4650
Connection ~ 5350 3200
Wire Wire Line
	6850 3700 6850 4100
Wire Wire Line
	8850 4100 8850 3700
Wire Wire Line
	3450 4400 3450 5050
Connection ~ 6250 3200
Wire Wire Line
	6450 3700 6850 3700
Wire Wire Line
	5950 3000 5950 3700
Wire Wire Line
	8100 4000 8100 5050
Wire Wire Line
	5350 5050 6850 5050
Connection ~ 3450 5050
Wire Wire Line
	6250 3200 6250 3400
Wire Notes Line
	9300 5250 2350 5250
Wire Notes Line
	9300 2650 9300 5250
Text Label 6950 3700 0    50   ~ 0
V_UNREG
Wire Wire Line
	5950 3700 6050 3700
Text Notes 2350 2600 0    50   ~ 0
3.75V - 6V in, min 100mAh 3.7V LiPo, 3V max 250mA out
Connection ~ 4850 5050
Wire Wire Line
	8450 4650 9300 4650
Wire Wire Line
	6850 3700 7800 3700
Text Notes 4750 5000 2    50   ~ 0
iReg = 1000 V / rProg\nrProg = 1000 V / iReg\niReg is 100 mA for a 120 mAh\nso rProg is 10 kOhm
Wire Wire Line
	7350 3200 6850 3200
$Comp
L power:GND #PWR0120
U 1 1 5CF879F1
P 5350 5250
F 0 "#PWR0120" H 5350 5000 50  0001 C CNN
F 1 "GND" H 5355 5077 50  0000 C CNN
F 2 "" H 5350 5250 50  0001 C CNN
F 3 "" H 5350 5250 50  0001 C CNN
	1    5350 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5CF879F2
P 4850 4850
F 0 "R13" H 4920 4896 50  0000 L CNN
F 1 "10K CALIB CHRG" H 4920 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4780 4850 50  0001 C CNN
F 3 "~" H 4850 4850 50  0001 C CNN
	1    4850 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5050 5350 5250
$Comp
L Device:C C9
U 1 1 5CF879F3
P 8850 4250
F 0 "C9" H 8965 4296 50  0000 L CNN
F 1 "1µF" H 8965 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8888 4100 50  0001 C CNN
F 3 "~" H 8850 4250 50  0001 C CNN
	1    8850 4250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:MCP1700-3302E_SOT23 U5
U 1 1 5CF879F4
P 8100 3700
F 0 "U5" H 8100 3942 50  0000 C CNN
F 1 "MCP1700-3302E_SOT23" H 8100 3851 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8100 3925 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001826D.pdf" H 8100 3700 50  0001 C CNN
	1    8100 3700
	1    0    0    -1  
$EndComp
$Comp
L Battery_Management:MCP73831-2-OT U4
U 1 1 5CF879F5
P 5350 4550
F 0 "U4" H 5650 4850 50  0000 C CNN
F 1 "MCP73831-2-OT" H 4950 4850 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 5400 4300 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001984g.pdf" H 5200 4500 50  0001 C CNN
	1    5350 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D4
U 1 1 5CF879F6
P 6850 3400
F 0 "D4" V 6896 3321 50  0000 R CNN
F 1 "BAT60JFILM" H 7000 3500 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 6850 3400 50  0001 C CNN
F 3 "~" H 6850 3400 50  0001 C CNN
	1    6850 3400
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C8
U 1 1 5CF879F7
P 6850 4250
F 0 "C8" H 6965 4296 50  0000 L CNN
F 1 "4.7µF" H 6965 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6888 4100 50  0001 C CNN
F 3 "~" H 6850 4250 50  0001 C CNN
	1    6850 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper JP1
U 1 1 5CF879F8
P 2950 3000
F 0 "JP1" H 2950 3264 50  0000 C CNN
F 1 "Current test point" H 2950 3173 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 2950 3000 50  0001 C CNN
F 3 "~" H 2950 3000 50  0001 C CNN
	1    2950 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5CF879F9
P 3450 4250
F 0 "C7" H 3565 4296 50  0000 L CNN
F 1 "4.7µF" H 3565 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3488 4100 50  0001 C CNN
F 3 "~" H 3450 4250 50  0001 C CNN
	1    3450 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5CF879FA
P 2950 4250
F 0 "C6" H 3065 4296 50  0000 L CNN
F 1 "4.7µF" H 3065 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2988 4100 50  0001 C CNN
F 3 "~" H 2950 4250 50  0001 C CNN
	1    2950 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5CF879FB
P 8450 4250
F 0 "R15" H 8520 4296 50  0000 L CNN
F 1 "47K PULLUP 3V" H 8500 4100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8380 4250 50  0001 C CNN
F 3 "~" H 8450 4250 50  0001 C CNN
	1    8450 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_DGS Q2
U 1 1 5CF879FC
P 6250 3600
F 0 "Q2" V 6500 3600 50  0000 C CNN
F 1 "DMP1045U" V 6591 3600 50  0000 C CNN
F 2 "procsynth:SOT23_FET" H 6450 3700 50  0001 C CNN
F 3 "~" H 6250 3600 50  0001 C CNN
	1    6250 3600
	0    -1   1    0   
$EndComp
$Comp
L Device:R R14
U 1 1 5CF879FD
P 7350 4250
F 0 "R14" H 7420 4296 50  0000 L CNN
F 1 "100K CHRG INIT LOAD" H 7420 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7280 4250 50  0001 C CNN
F 3 "~" H 7350 4250 50  0001 C CNN
	1    7350 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4650 8450 4650
Wire Wire Line
	3450 3000 3450 4100
Wire Wire Line
	8450 4100 8450 3700
Wire Wire Line
	2350 3200 2950 3200
Wire Wire Line
	8400 3700 8450 3700
Wire Notes Line
	2350 5250 2350 2650
Connection ~ 8100 5050
Wire Wire Line
	8450 3700 8850 3700
Wire Wire Line
	3450 5050 4850 5050
Wire Wire Line
	2950 4400 2950 5050
Wire Wire Line
	5350 4850 5350 5050
Wire Wire Line
	5350 3200 6250 3200
Connection ~ 3450 3000
Wire Wire Line
	8850 5050 8850 4400
Connection ~ 6850 3700
Wire Wire Line
	6850 4400 6850 5050
Wire Wire Line
	2950 4100 2950 3200
Connection ~ 5350 5050
Text HLabel 9300 3700 2    50   Output ~ 0
VOUT
Connection ~ 2950 3200
Connection ~ 8850 3700
Text HLabel 2350 3200 0    50   Input ~ 0
VIN
Wire Wire Line
	2950 3200 5350 3200
Text Notes 9250 2750 2    50   ~ 0
based on the charger described by Zak Kemble at http://blog.zakkemble.net/a-lithium-battery-charger-with-load-sharing/
Wire Wire Line
	7350 4400 7350 5050
Wire Wire Line
	8850 3700 9300 3700
Wire Wire Line
	3450 3000 5950 3000
Wire Wire Line
	3250 3000 3450 3000
Wire Wire Line
	4850 5000 4850 5050
Text HLabel 2350 3000 0    50   Input ~ 0
LIPO_IN
Wire Wire Line
	5750 4450 5950 4450
Wire Wire Line
	5350 3200 5350 4250
Wire Wire Line
	6250 3200 6850 3200
Wire Wire Line
	5950 3700 5950 4450
Connection ~ 5950 3700
Wire Wire Line
	2350 3000 2650 3000
Wire Wire Line
	8100 5050 8850 5050
Connection ~ 8450 3700
Wire Wire Line
	8450 4400 8450 4650
Wire Wire Line
	7350 4100 7350 3200
Wire Wire Line
	6850 3200 6850 3250
Connection ~ 8450 4650
Wire Wire Line
	7350 5050 8100 5050
Wire Wire Line
	6850 3550 6850 3700
Wire Wire Line
	4850 4650 4950 4650
Connection ~ 6850 5050
Text HLabel 9300 4650 2    50   Output ~ 0
STAT
Wire Wire Line
	4850 5050 5350 5050
Wire Notes Line
	2350 2650 9300 2650
Wire Wire Line
	6850 5050 7350 5050
Wire Wire Line
	2950 5050 3450 5050
Connection ~ 6850 3200
Connection ~ 7350 5050
$EndSCHEMATC
