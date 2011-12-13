' Sample code for speech module SP03

'*** setup i2c ***
' Define i2c slave address for the SP03 Speech Module
	i2cslave $C4,i2cfast,i2cbyte

' *** firmware ***
	' read firmware version into b1 and display on screen
	readi2c 1,(b1)
	debug b1

main:

' *** message playback ***
	'first play back a pre-recorded message (msg 1)
	'remember to use gosub to wait for message to stop
	writei2c 0,(1)
	gosub wait4shutup
	
' *** instant speech ***
	' now download text to instantly speak
	' first write text to speak to buffer (max 81 characters)
	' nop(0), volume(0), pitch(5), speed(1), "text", null(0)
	' note creative spelling makes picaxe sound better!

	writei2c 0,(0,0,5,1,"Hello pickacks user",0)

	' now actually say it 
	writei2c 0,(64)
	gosub wait4shutup

	'loop forever
	goto main

' *** sub to wait until SP03 has stopped talking ***
wait4shutup:
	readi2c 0,(b1)
	if b1 > 0 then wait4shutup
	return
