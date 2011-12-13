' AXE106 Simon Says Game

' *** Define the variables used ***

' Push switches on inputs 0,1,6,7
' Preset (speed) on input 2
' LEDs on outputs 0-3
' Piezo on output 7

symbol rand = b1	' random number store for loading memory
symbol value = b2	' switch value 0-1-2-3 
symbol playerstep= b3	' position of player in game
symbol freq = b4	' sound variable
symbol topstep = b5	' number of steps in sequence
symbol counter = b6	' general purpose counter
symbol speed = b7	' speed of playback

' *** Section 1 **********************
' *** This section waits for start ***
' ************************************

' wait for any switch to be pushed
' with all four LEDs lit
' preload rand with any number by repeatedly
' using the random command in the loop

init:
	let pins = %00001111
	random rand
	if pin0 = 1 then preload
	if pin1 = 1 then preload
	if pin6 = 1 then preload
	if pin7 = 1 then preload
	goto init

' *** Section 2 ****************************
' *** This section loads memory for game ***
' ******************************************

' load EEPROM data memory with 100 numbers
' first get the random number (0 to 255)
' and then change to either 1,2,3 or 4
' and then save into data memory

preload:
	let pins = %00000000	' all LEDs off

	for counter = 0 to 100	' for..next loop

	let value = 0
	random rand		' get random number 0-255
	if rand > 180 then set0
	if rand > 120 then set1
	if rand > 60 then set2

set3: 	let value = value + 1	'1+1+1 = 3
set2: 	let value = value + 1	'1+1 = 2
set1:	let value = value + 1	'1
set0:				'0

	write counter,value 	' save in data memory

	next counter		' next loop

' *** Section 3 ****************************
' *** This section plays back a sequence ***
' ******************************************

' switch off the LEDs and then start
' a game with the end counter as 1
	let pins = %00000000		' LEDs off
	let topstep = 1			' reset step number to 1

' playback the game sequence
playback:

' first read the playback speed
	readadc	2,speed

' now do a playback
	for counter = 1 to topstep	' for...next loop
	   read counter,value		' get value
	   gosub beep			' make the noise
	   pause 300			' short delay
	next counter			' loop

' *** Section 4 *****************************************
' *** This section detects the players reply sequence ***
' *******************************************************

' now the user responds
' reset the players position to 1
	playerstep = 1

gameloop:
' if playerstep is greater than topstep then all done
	if playerstep > topstep then success	

' get the correct key value is supposed to hit
' from the EEPROM memory 
	read playerstep,value		

' now wait for switch to be pressed
loop:	if pin7 = 1 then pushed0
	if pin0 = 1 then pushed1
	if pin1 = 1 then pushed2
	if pin6 = 1 then pushed3
	goto loop

' switch pressed so check it is the correct one
' if it is make a beep sound and then continue
' else fail the game
pushed0:
	if value <> 0 then fail
	let playerstep = playerstep + 1
	gosub beep
	goto gameloop

pushed1:
	if value <> 1 then fail
	let playerstep = playerstep + 1
	gosub beep
	goto gameloop

pushed2:
	if value <> 2 then fail
	let playerstep = playerstep + 1
	gosub beep
	goto gameloop

pushed3:
	if value <> 3 then fail
	let playerstep = playerstep + 1
	gosub beep
	goto gameloop

' *** Failed so make noise and jump back to start ***
' failed so make failed noise, switch off all LEDs
' and go back to start
fail: 
	let pins = %0000000		' all LEDs off
	sound 7,(80,100)		' make a noise
	sound 7,(50,100)
	goto init			' back to start

' *** Succeeded so add another step to sequence and loop ***

' success so make a success sound 
' and then increment topstep and do another sequence
success:
	pause 100			' short delay
	let pins = %00001111		' all LEDs on
	sound 7,(120,50)		' success beep
	let pins = %00000000		' all LEDs off
	pause 100			' short delay
	let topstep = topstep + 1	' add another step
	goto playback			' loop again

' *** Section 5 ****************
' *** sub light LED and beep ***
' ******************************

'sub-procedure to light correct LED
'and make a different beep sound for each LED
'value always contains number 0,1,2 or 3.
'add 1 and multiply by 20 to give larger difference
'in the sound noise 

beep:
	high value		' switch on LED
	freq = value + 1	' generate sound freq.
	freq = freq * 25
	sound 7,(freq,speed)	' play sound
	low value		' switch off LED
	return			' return






