' AXE104 Temperature Program
' Note requires PICAXE-18A microcontroller
' with DS18B20 temp sensor on input6

main:	if pin2 = 1 then temp	' test switch
	goto main

temp:	readtemp 6,b1		' read temperature value
	if b1 > 30 then temp30	' test for above 30 degrees
	if b1 > 25 then temp25	' test for 25-30 degrees
	if b1 > 20 then temp20	' test for 20-25 degrees
	if b1 > 15 then temp15	' test for 15-20 degrees

temp10:	let pins = %00000001	' light one LED - too cold
	sound 7,(100,100)	' make warning sound
	pause 1000
	goto main		' back to start

temp15:	let pins = %00000011	' light two LEDs
	pause 1000
	goto main		' back to start

temp20:	let pins = %00000111	' light three LEDs
	pause 1000
	goto main		' back to start

temp25:	let pins = %00001111	' light four LEDs
	pause 1000
	goto main		' back to start

temp30:	let pins = %00011111	' light five LEDs - too hot
	sound 7,(100,100)	' make warning sound
	pause 1000
	goto main		' back to start
