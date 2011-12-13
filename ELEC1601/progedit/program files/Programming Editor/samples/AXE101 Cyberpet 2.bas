' Cyper Pet Program 2
' For PICAXE-08

' LDR on pin 1
' Push switch on pin 3
' LEDs on pins 0 and 4
' Piezo sounder on pin 2

symbol bright = b0
symbol light = b1
symbol pet = b2
symbol mark = b3
symbol space = b4

' ***** start of program reset counters *****

' first reset the pet count to 0
' and the PWM off time to 15
main:
	let pet = 0
	let space = 15
	
' ***** main loop *****

' loop here flashing lights
' and checking switch and light sensor


loop:
' first make LED brighter in 8 steps
	for mark = 0 to 8
	   gosub flash
	 next mark

' LEDs full on and read light value
	high 4
	high 0
	readadc 1,light

' if light value low then goto bed
	if light < 80 then bed

' if switch pushed add petting value
	if pin3 = 1 then addpet

' do a delay
	pause 200

' LED gets dimmer
	for mark = 8 to 0 step -1
	  gosub flash
	next mark

' LED full off and check sensors
	readadc 1,light

' if light value low then goto bed
	if light < 80 then bed

' if switch pushed add petting value
	if pin3 = 1 then addpet
	pause 250
	goto loop

' ***** end of main loop *****

' ***** add one to pet value *****
addpet:
	pet = pet + 1
	sound 2,(120,50)
	pause 200

' check pet value to see if it is three yet
' if under 3 go back to loop
	if pet < 3 then loop

' pet value is 3 so play a tune then reset
	high 0
	high 4
	sound 2,(80,50,100,50,120,50,100,50,120,50)
	goto main


' ***** bed routine when in dark ****
' in dark so switch off LEDs and wait till
' light again

bed:
	low 0
	low 4
	readadc 1,light
	if light > 80 then main
	goto bed

' ***** PWM routine to dim LEDs *****
' sub procedure to output PWM on LEDs
flash:
	for b0 = 1 to 10
	   high 0
	   high 4
	   pause mark
	   low 0
	   low 4
	   pause space
	next b0
	return


