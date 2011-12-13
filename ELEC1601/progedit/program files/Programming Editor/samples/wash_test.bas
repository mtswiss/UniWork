; Washing Machine Test Program
; Program for internal PICAXE-18 

symbol motor_forward = 7
symbol motor_back = 6
symbol solenoid = 5
symbol red_led = 5
symbol green_led = 4

symbol door_switch = pin0
symbol red_switch = pin6
symbol blue_switch = pin7


'Door switch activate solenoid
'Blue switch activates green LED
'Red switch activates motor


'** Only press one switch at a time !! **

main:	if pin0 = 1 then solenoid_on
	if pin6 = 1 then motor_on
	if pin7 = 1 then green_on
	goto main

solenoid_on:
	high 5
loop1:	if pin0 = 1 then loop1
	low 5
	goto main

motor_on:
	high 7
loop2:	if pin6 = 1 then loop2
	low 7
	goto main

green_on:
	high 4
loop3:	if pin7 = 1 then loop3
	low 4
	goto main









