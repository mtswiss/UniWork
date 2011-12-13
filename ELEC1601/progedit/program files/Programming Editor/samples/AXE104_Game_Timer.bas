' AXE104 Timer Program
' Note use of a word variable (W3) as the pause times
' are greater than a byte value (255).

main:
	if pin2 = 1 then start	' test switch
	goto main

start:	readadc 0,b1		' read preset value
	if b1 > 150 then time10	' if bigger than 150 jump
	if b1 > 100 then time5	' if bigger than 100 jump

time1:	let w3 = 1000		' 1 second	
	goto flash

time5:	let w3 = 5000		' 5 second	
	goto flash

time10:	let w3 = 10000		' 10 second	
	goto flash

flash:	high 0			' light LEDs
	pause w3
	low 0
	high 1
	pause w3
	low 1
	high 2
	pause w3
	low 2
	high 3
	pause w3
	low 3
	high 4
	pause w3
	low 4
	sound 7,(50,50)		' beep
	goto main		' back to start		



