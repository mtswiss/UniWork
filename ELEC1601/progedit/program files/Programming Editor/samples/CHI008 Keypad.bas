' Keypad Lock
' For PICAXE-18

'output 7 - FET to drive solenoid bolt
'output 6 - piezo sounder
'output 4,5 - bicolour LED
'output 3 - row 4
'output 2 - row 3
'output 1 - row 2
'output 0 - row 1

'input 0 - column 1
'input 1 - column 2
'input 2 - column 3

symbol key_pos = b0	' number of keys pressed
symbol key_value = b1	' value of key pressed

' *** reset position to zero ***

init:	
	let key_pos = 0

' *** now scan each row in turn ***
' *** by setting only 1 row (and LED) high ***
' *** if a switch is hit jump call score sub below ***

scan:
	let key_value = 0
	let pins = %00010001
	gosub key_test

	let key_value = 3
	let pins = %00010010
	gosub key_test

	let key_value = 6
	let pins = %00010100
	gosub key_test

	let key_value = 9
	let pins = %00011000
	gosub key_test

	goto scan


' *** Score sub procedure. ***
' *** return straight away if no key pressed ***

key_test:
	if pin0 = 1 then add1
	if pin1 = 1 then add2
	if pin2 = 1 then add3
	return

' *** key value will already be 0, 3, 6, or 9 ***
' *** so add 1, 2 or 3 to this value *** 

add3:	let key_value = key_value + 1
add2:	let key_value = key_value + 1
add1:	let key_value = key_value + 1

' *** Make a beep ***

	sound 6,(60,50)

' *** Now increase position counter by 1 ***
' *** and test for 1st, 2nd 3rd or 4th push ***

	let key_pos = key_pos + 1

	if key_pos = 1 then test1
	if key_pos = 2 then test2
	if key_pos = 3 then test3
'	if key_pos = 4 then test4 
	
' *** Now test the value for each position individually ***
' *** If value is wrong restart, if correct loop until ***
' *** fourth go. If fourth is correct open lock! ***

' *** Key code is set to 9-3-5-1 ***

test4:	if key_value = 1 then open
	goto reset

test3:	if key_value = 5 then continue
	goto reset

test2:	if key_value = 3 then continue
	goto reset

test1:	if key_value = 9 then continue
	goto reset


' *** Got here so open lock and set LED green for 5 sec ***

open:	let pins = %10100000
	wait 5
	goto reset

' *** Not correct value so reset position counter then return ***

reset:
	let key_pos = 0

' *** Okay so continue by returning back to main loop ***

continue:
	return



