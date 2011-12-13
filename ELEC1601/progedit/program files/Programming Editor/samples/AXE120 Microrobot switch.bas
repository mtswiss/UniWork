
'start going forwards
'testing switches as you go

main:
	let pins = %01010000
	if pin2 = 1 then left
	if pin6 = 1 then right
	goto main


'left switch hit
'so stop reverse, turn 

left:
	let pins =%10100000
	pause 2000
	let pins =%10010000
	pause 1500
	goto main

'right switch hit
'so  reverse, turn other way

right:
	let pins =%10100000
	pause 2000
	let pins =%01100000
	pause 1500
	goto main






	







