; Example of how to use DS1307 Time Clock (i2c device)
; Note the data is sent/received in BCD format.

symbol seconds = b0
symbol mins = b1
symbol hour = b2
symbol day = b3
symbol date = b4
symbol month = b5
symbol year = b6
symbol control = b7
symbol temp = b8

' set DS1307 slave address
	i2cslave %11010000, i2cslow, i2cbyte


' uncomment this line to update the clock time
' goto start_clock 


' read time and date and display on serial LCD module

main:
	readi2c 0,(seconds,mins,hour,day,date,month,year)
	
	' debug b0 '(optional debug computer to screen)

	serout 7,N2400,(254,128) 'start of first line	

	let temp = date & %0011000
	serout 7,N2400,(#temp)
	let temp = date & %00001111
	serout 7,N2400,(#temp,"/")

	let temp = month & %0001000 
	serout 7,N2400,(#temp)
	let temp = month & %00001111
	serout 7,N2400,(#temp,"/")

	let temp = year & %11110000
	serout 7,N2400,(#temp)
	let temp = year & %00001111
	serout 7,N2400,(#temp," ")

	let temp = hour & %00110000 
	serout 7,N2400,(#temp)
	let temp = hour & %00001111
	serout 7,N2400,(#temp,":")

	let temp = mins & %0111000 
	serout 7,N2400,(#temp)
	let temp = mins & %00001111
	serout 7,N2400,(#temp,":")

	let temp = seconds & %01110000
	serout 7,N2400,(#temp)
	let temp = seconds & %00001111
	serout 7,N2400,(#temp)

	pause 5000
	goto main



'write time and date e.g. to 11:59:00 on Thurs 25/12/03
start_clock:
	let seconds = $00	' 00 Note all BCD format
	let mins    = $59	' 59 Note all BCD format
	let hour    = $11	' 11 Note all BCD format
	let day     = $03	' 03 Note all BCD format
	let date    = $25	' 25 Note all BCD format
	let month   = $12	' 12 Note all BCD format
	let year    = $03	' 03 Note all BCD format
 	let control = %00010000 ' Enable output at 1Hz

	writei2c 0,(seconds,mins,hour,day,date,month,year,control)

	end





