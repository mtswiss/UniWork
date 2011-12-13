; Bank Safe Test Program
; Program for internal PICAXE-18 

symbol siren = 7
symbol solenoid = 5
symbol red_led = 5
symbol green_led = 4

symbol door_switch = pin0
symbol column3 = pin6
symbol column2 = pin7
symbol column1 = pin2


'Door switch activate solenoid
'Column 1 switch activates siren
'Column 2 switch activates green LED


'** Only press one switch at a time !! **

main:	if pin0 = 1 then solenoid_on
	if pin2 = 1 then siren_on
	if pin7 = 1 then green_on
	goto main

solenoid_on:
	high 5
loop1:	if pin0 = 1 then loop1
	low 5
	goto main

siren_on:
	high 7
loop2:	if pin2 = 1 then loop2
	low 7
	goto main

green_on:
	high 4
loop3:	if pin7 = 1 then loop3
	low 4
	goto main








