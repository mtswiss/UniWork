
'Buggy Test Program For PICAXE18 microcontroller
'using www.rev-ed.co.uk Buggy Kit (CHI007 or MOD001)
'make sure piezo link LK3 is connected for sound to work on pin0!

'CPS May 2001

'output pin allocation (%76543210)
'76 = motor B
'54 = motor A
'3  = not used 
'2  = LED B
'1  = LED A
'0  = piezo sounder

'input pin allocation
'1  = sensor B
'0  = sensor A


'start going forwards
'testing switches as you go

main:
	let pins = %01010000
	if pin0 = 1 then left
	if pin1 = 1 then right
	goto main


'left switch hit
'so stop, light LED, beep, reverse, turn 

left:
	let pins =%00000100
	sound 0,(100,150)
	let pins =%10100100
	pause 2000
	let pins =%10010100
	pause 1500
	goto main

'right switch hit
'so stop, light LED, beep, reverse, turn other way

right:
	let pins =%00000010
	sound 0,(50,150)
	let pins =%10100010
	pause 2000
	let pins =%01100010
	pause 1500
	goto main






	




