' AXE104 Quiz Program

main:	high 4			' use LED4 as power indicator
	if pin2 = 1 then team1	' test switch
	if pin6 = 1 then team2	' test switch
	if pin7 = 1 then team3	' test switch
	goto main

team1:				' team 1 LED
	high 1
	goto timer

team2:				' team 2 LED
	high 2
	goto timer

team3:				' team 3 LED
	high 3
	goto timer

timer:	sound 7,(100,100)	' make beep
	readadc 0,b1		' read preset value
	if b1 > 100 then time10	' if biiger than 100 jump

time5:	pause 5000		' 5 seconds
	low 1			' LEDs off
	low 2
	low 3	
	goto main		' back to start

time10:	pause 10000		' 10 seconds
	low 1			' LEDs off
	low 2
	low 3	
	goto main		' back to start		
