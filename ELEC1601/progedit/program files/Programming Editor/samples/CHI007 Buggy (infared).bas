
'Buggy Test Program For PICAXE-18A microcontroller
'using www.rev-ed.co.uk Buggy Kit (CHI007 or MOD001) v5
'fitted with the AXE040 infrared upgrade
'make sure piezo link LK3 is connected for sound to work on pin0!

'CPS May 2001

'output pin allocation (%76543210)
'76 = motor B
'54 = motor A
'3  = not used 
'2  = LED B
'1  = LED A
'0  = piezo sounder

'input pin allocation (v5)
'2  = sensor B
'7  = sensor A
'0  = infrared sensor


main:
	infrain				'wait for new infra command
	if infra = 2 then go_forward
	if infra = 8 then go_backward
	if infra = 4 then go_left
	if infra = 6 then go_right
	if infra = 5 then stop
	if infra = 1 then LED1_on
	if infra = 7 then LED1_off
	if infra = 3 then LED2_on
	if infra = 9 then LED2_off
	if infra >= 10 then beep 	'(any other button)
	goto main

go_forward:
	low 7
	high 6
	low 5
	high 4
	goto main
go_backward:
	high 7
	low 6
	high 5
	low 4
	goto main
go_left:
	high 7
	low 6
	low 5
	high 4
	goto main
go_right:
	low 7
	high 6
	high 5
	low 4
	goto main
stop:
	low 7
	low 6
	low 5
	low 4
	goto main
LED1_on:
	high 1
	goto main
LED1_off:
	low 1
	goto main
LED2_on:
	high 2
	goto main
LED2_off:
	low 2
	goto main
beep:
	sound 0,(50,100)
	goto main


	







