' Rudolf Infrared Transmitter Program
' For PICAXE-08M

' LED on pin 4
' Infrared LED on pin 0 
' Switches on pins 1,2,3
	
' ***** main loop *****
' wait until switch press
main:
	if pin1 = 1 then tx_1
	if pin2 = 1 then tx_2
	if pin3 = 1 then tx_3
	goto main

tx_1:
	let b1 = 1		' Code 1
	goto tx_ir
tx_2:
	let b1 = 2		' Code 2
	goto tx_ir
tx_3:
	let b1 = 3		' Code 3
	goto tx_ir

'transmit code 10 times for increased reliability	
tx_ir:
	high 4		' visual LED on
	for b2 = 1 to 10	' send infrared code 10 times
	   infraout 1,b1
	   pause 45
	next b2	
	low 4			' LED off
	goto main

