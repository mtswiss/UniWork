symbol trig = 3 	' Define output pin for Trigger pulse
symbol echo = 7 	' Define input pin for Echo pulse
symbol range = w1 ' 16 bit word variable for range

main:
	pause 100 				' motor controller start-up pause
	let pins = %10100000 		' buggy forward
loop:
	pulsout trig,2 			' produce 20uS trigger pulse
	pulsin echo,1,range 		' measures the range in 10uS steps
	pause 10 				' SRF004 mandatory recharge period

' now convert range to cm (divide by 6.2)
' and stop if there is an object closer than 30 cm
	let range = range * 10 / 62 	' multiply by 10 then divide by 62
	if range < 10 then stop1
	goto loop 				' loop around if > 10

stop1:
	let pins = %00000000 		' stop
	goto stop1
