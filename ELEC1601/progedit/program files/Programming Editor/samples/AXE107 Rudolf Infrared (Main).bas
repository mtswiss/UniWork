' Rudolf Infrared Program
' For PICAXE-08M

' LDR on pin 1
' Infrared sensor on pin 3 
' LEDs on pins 0 (nose) and 4 (eyes)
' Piezo sounder on pin 2
	
' ***** main loop *****
' wait until infrared signal
main:
	infrain2


' ***** play tune *****

	'debug infra	' optional display on screen for testing

' play tune depending on light level	
	if infra = 3 then play_xmas
	if infra = 2 then play_rudolf
	if infra = 1 then play_jingle
	goto main

play_jingle:		' internal tune Jingle Bells

	play 1,3
	goto main
 
play_silent:		' internal tune Silent Night
	play 2,3
	goto main
	
play_rudolf:		' internal tune Rudolf The Red Nosed Reindeer
	play 3,3
	goto main

play_xmas:			' external ringtone tune

' We wish you a Merry Xmas
tune 3, 4,($22,$27,$67,$69,$67,$66,$24,$24,$24,$29,$69,$6B,$69,$67,$26,$22,$22,$2B,$6B,$40,$6B,$69,$27,$24,$22,$24,$29,$26,$E7,$22,$27,$67,$69,$67,$66,$24,$24,$24,$29,$69,$6B,$69,$67,$26,$22,$22,$2B,$6B,$40,$6B,$69,$27,$24,$22,$24,$29,$26,$A7,$22,$27,$27,$27,$E6,$26,$27,$26,$24,$E2,$29,$2B,$69,$69,$67,$67,$02,$22,$22,$24,$29,$26,$E7)

	goto main



