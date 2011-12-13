' AXE104 Simon Says Game
' Note requires PICAXE-18A microcontroller
' as program is too long for PICAXE-18

' Push swithes on inputs 1,2,6,7
' LEDs on outputs 1-4
' Piezo on output 7

symbol rand = b1	' random for loading memory
symbol key = b2		' switch 1-2-3-4 
symbol position = b3	' position of player in game
symbol freq = b4	' sound variable
symbol counter = b5	' number of steps in sequence

' *** This section waits for start ***

' wait for any switch to be pushed
' with all four LEDs lit
' preload rand with any number by repeatedly
' using the random command in the loop

init:
	let pins = %00011110
	random rand
	if pin1 = 1 then preload
	if pin2 = 1 then preload
	if pin6 = 1 then preload
	if pin7 = 1 then preload
	goto init

' *** This section loads memory for game ***

' load EEPROM data memory with 64 numbers
' first get the random number (0 to 255)
' and then change to either 1,2,3 or 4
' and then save into data memory

preload:
	for position = 0 to 63	' for..next loop

	let key = 0
	random rand		' get random number 0-255
	if rand > 180 then set1
	if rand > 120 then set2
	if rand > 60 then set3

set4:	let key = key + 1	'1+1+1+1 = 4
set3: 	let key = key + 1	'1+1+1 = 3
set2: 	let key = key + 1	'1+1 = 2
set1:	let key = key + 1	'1

	write position,key	' save in data memory

	next position		' next loop

' *** This section plays back a sequence ***

' switch off the LEDs and then start
' a game with the end counter as 1
	let pins = %00000000
	let counter = 1

' playback the game sequence
playback:
	for position = 0 to counter
	   read position,key
	   gosub beep
	   pause 500
	next position

' *** This section detects the players reply sequence ***

' now the user responds
' reset the players position to 0
	position = 0

' get the correct key player is supposed to hit
' from the EEPROM memory 
gameloop:
	read position,key

' if position is equal to counter then all done
	if position = counter then success	

' else wait for switch to be pressed
loop:	if pin1 = 1 then played1
	if pin2 = 1 then played2
	if pin6 = 1 then played3
	if pin7 = 1 then played4
	goto loop

' switch pressed so check it is the correct one
' if it is make a beep sound and then continue
' else fail the game
played1:
	if key <> 1 then fail
	let position = position + 1
	gosub beep
	goto gameloop

played2:
	if key <> 2 then fail
	let position = position + 1
	gosub beep
	goto gameloop

played3:
	if key <> 3 then fail
	let position = position + 1
	gosub beep
	goto gameloop

played4:
	if key <> 4 then fail
	let position = position + 1
	gosub beep
	goto gameloop

' *** Failed so make noise and jump back to start ***
' failed so make failed noise, light all LEDs
' and go back to start
fail: 
	pause 250
	let pins = %00011110
	sound 7,(100,300)
	goto init

' *** Succeeded so add another step to sequence and loop ***

' success so make a success sound 
' and then increment counter and do another sequence
success:
	pause 50
	sound 7,(50,100)
	pause 50
	sound 7,(50,100)
	pause 500
	let counter = counter + 1
	goto playback

' *** sub light LED and beep ***

'sub-procedure to light correct LED
'and make a different beep sound for each LED
'key always contains number 1,2,3 or 4
'multiply sound freq by 10 to give larger difference

beep:
	high key
	freq = key * 10
	sound 7,(freq,100)
	low key
	return
