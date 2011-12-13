; Bank Safe Sample Program
; Program for internal PICAXE-18 

symbol siren = 7
symbol solenoid = 5
symbol red_led = 5
symbol green_led = 4

symbol door_switch = pin0
symbol column3 = pin6
symbol column2 = pin7
symbol column1 = pin2


'First wait for the door to be shut
'as it is presumed to be open at first

main:
	low 5
	high 4
	if pin0 = 1 then door_shut
	goto main

'Now lock the door
'by switching on solenoid

door_shut:
	pause 1000
	high 5
	low 4

' To open the door you must press any switch in
' column 1, then any switch in column 2, then column 3
' The green LED flashes when a correct switch is pushed.
' A beep is made if an incorrect switch is pushed.
' NB You must wait for the green LED to go out before pressing 
' the next switch. Remember that all switches in a column are 
' connected together so it doesn't matter which one is pushed.


'Test for first column switch
'If other column pushed - beep, then return to first column

test1:
	high 4
	pause 500
	low 4
loop1:	if pin6 = 1 then alarm	
	if pin7 = 1 then alarm
	if pin2 = 1 then test2
	goto loop1

'Test for second column switch
'If other column pushed - beep, then return to first column

test2:
	high 4
	pause 500
	low 4
loop2:	if pin2 =1 then alarm
	if pin6 = 1 then alarm
	if pin7 = 1 then test3
	goto loop2

'Test for third column switch
'If other column pushed - beep, then return to first column

test3:
	high 4
	pause 500
	low 4
loop3:	if pin2 = 1 then alarm
	if pin7 = 1 then alarm
	if pin6 = 1 then unlock_door
	goto loop3

'OK so unlock door and wait for door to open
'then go back to main

unlock_door:
	high 4
	low 5
	if pin0 = 1 then unlock_door
	
	pause 500
	goto main


'This is alarm - beep when wrong column switch pushed
'simple make a beep then return to first column test

alarm:
	high 7
	pause 1000
	low 7
	goto loop1


