
' Test Program for AXE104 Electronic Game

' Analogue pot on input 0
' Digital input on input 2
' LEDs on output 0 to 4
' Piezo sounder on output 7

' When switch is pressed the potentiometer
' on input 0 is read into variable b1.
' This value is then used to make a sound
' and as the time delay for flashing LEDs
' CPS 2002

main:
	if input2 is on then flash	' test for switch press
	goto main			' no press so loop

flash:
	readadc 0,b1		' read the analogue value
				' from pin0 into variable b1

	sound 7,(b1,50)		' make sound on piezo (output 7)

	high 0			' flash each LED in turn
	pause b1
	low 0
	high 1
	pause b1
	low 1
	high 2
	pause b1
	low 2
	high 3
	pause b1
	low 3
	high 4
	pause b1
	low 4
	goto main



