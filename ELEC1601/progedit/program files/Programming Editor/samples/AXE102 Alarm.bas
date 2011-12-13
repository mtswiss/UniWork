' AXE102 Alarm
' For PICAXE-08

' Analogue input on pin 1
' Digital input on pin 3
' LED on pin 0
' Piezo sounder on pin 2
' Output on pin 4

symbol light = b1
	
' ***** main loop *****

' loop here flashing lights
' and checking sensors

main:

' LEDs full on and read light value
	high 0
	readadc 1,light

' if analogue value low then make sound
	if light < 40 then beep

' if switch pushed do alarm
	if pin3 = 1 then alarm

' do a delay
	pause 500

' LEDs full off and check sensor again
	low 0
	readadc 1,light

' if analogue value low then make sound
	if light < 40 then beep

' if switch pushed do alarm
	if pin3 = 1 then alarm

' do a delay
	pause 500

'loop back to start
	goto main

' ***** make sound *****
beep:
	sound 2,(120,50,80,50,120,50)
	pause 200
	goto main


' ***** alarm output on ****
alarm:
	high 4
	pause 2000
	low 4
	goto main





