; Washing Machine Sample Program
; Program for internal PICAXE-18 

symbol motor_forward = 7
symbol motor_back = 6
symbol solenoid = 5
symbol red_led = 5
symbol green_led = 4

symbol door_switch = pin0
symbol red_switch = pin6
symbol blue_switch = pin7



'First wait for the door to be shut
main:
	low 4
	if pin0 = 1 then wait_for_start
	goto main


'Now wait for switch
'Light Green LED to show door is shut
'If door opens jump back to main
wait_for_start:
	high 4
	if pin0 = 0 then main
	if pin6 = 1 then do_red_cycle
	if pin7 = 1 then do_blue_cycle
	goto wait_for_start


'Red Cycle - 5 times each way at full speed
do_red_cycle:
	high 5			' lock door
	pause 500		' short delay for solenoid
	for b1 = 1 to 5		' loop 5 times with motor
		high 7
		pause 2000
		low 7
		high 6
		pause 2000
		low 6
	next b1
	low 5			'unlock door
	goto main		'back to start

'Blue Cycle - 5 times each way at low speed
do_blue_cycle:
	high 5			' lock door
	pause 500		' short delay for solenoid
	for b1 = 1 to 5		' loop 5 times with motor
		for b2 = 1 to 200	'PWM loop forwards
			high 7
			pause 3
			low 7
			pause 10
		next b2
		for b2 = 1 to 200	'PWM loop backwards
			high 6
			pause 3
			low 6
			pause 10
		next b2
	next b1
	low 5			'unlock door
	goto main		'back to start



