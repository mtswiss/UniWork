

main:
	let pins = %00111111	' digit 0
	pause 250		' wait 0.25 second
	let pins = %00000110	' digit 1
	pause 250		' wait 0.25 second
	let pins = %01011011	' digit 2
	pause 250		' wait 0.25 second
	let pins = %01001111	' digit 3
	pause 250		' wait 0.25 second
	let pins = %01100110	' digit 4
	pause 250		' wait 0.25 second
	let pins = %01101101	' digit 5
	pause 250		' wait 0.25 second
	let pins = %01111101	' digit 6
	pause 250		' wait 0.25 second
	let pins = %00000111	' digit 7
	pause 250		' wait 0.25 second
	let pins = %01111111	' digit 8
	pause 250		' wait 0.25 second
	let pins = %01101111	' digit 9
	pause 250		' wait 0.25 second
	goto main
