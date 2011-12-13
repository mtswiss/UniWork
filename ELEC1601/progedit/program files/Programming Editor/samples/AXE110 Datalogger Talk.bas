' Sample code for speech module SP03

symbol number =w0

symbol startpos = b2
symbol endpos = b3
symbol counter = b4
symbol nextbyte = b5
symbol loopcounter = b7


symbol mins = b8
symbol hour = b9
symbol day = b10
symbol date = b11
symbol month = b12
symbol year = b13

'small numbers (5 bytes)
eeprom  0,("  one")
eeprom  5,("  two")
eeprom 10,("three")
eeprom 15,(" four")
eeprom 20,(" five")
eeprom 25,("  six")
eeprom 30,("seven")
eeprom 35,("eight")
eeprom 40,(" nine")
eeprom 45,("  ten")

'low teens (6 bytes)
eeprom  50,("eleven")
eeprom  56,("twelve")
eeprom  62,("  thir")
eeprom  68,("  four")
eeprom  74,("   fif")

' Larger numbers (7 bytes)
eeprom  80,("twenty ")
eeprom  87,("thirty ")
eeprom  94,("fourty ")
eeprom 101,("fifty  ")
eeprom 108,("sixty  ")
eeprom 115,("seventy")
eeprom 122,("eighty ")
eeprom 129,("nine te") 

' Days (6 bytes)
eeprom 136,("   Mon")
eeprom 142,("  Tues")
eeprom 148,("  Weds")
eeprom 154,(" Thurs")
eeprom 160,("   Fri")
eeprom 166,(" Satur")
eeprom 172,("   Sun")

'Months (8 Bytes)
eeprom 178,(" January")
eeprom 186,("February")

'Months (6 Bytes)
eeprom 194,(" March")
eeprom 200,(" April")
eeprom 206,("   May")
eeprom 212,("  June")
eeprom 218,("  July")
eeprom 224,("August")

eeprom 230,("Septem")
eeprom 236,("  Octo")
eeprom 242,(" Novem")
eeprom 248,(" Decem")


main:
' Define i2c slave address for the DS1307 RTC
	i2cslave %11010000, i2cslow, i2cbyte
' Get Time and Date
' and correct BCD format 
	readi2c 1,(mins,hour,day,date,month,year)

	let number = mins / 16 * 10
	let mins = mins & %00001111 + number

	let number = hour / 16 * 10
	let hour = hour & %00001111 + number

	let number = date / 16 * 10
	let date = date & %00001111 + number

	let number = year / 16 * 10
	let year = year & %00001111 + number


' optional debug on screen
	'debug b1

' Define i2c slave address for the SPE030 Speech Module
	i2cslave $C4,i2cfast,i2cbyte



; *** Sub to speak a date and time ***

speak_date_time:

speak_time:
	writei2c 0,(0,0,5,1)		' set the volume pitch and speed
	writei2c 0,(0,"The time  is ")
	gosub say_it

	let number = hour
	gosub speak_number

	let number = mins
	gosub speak_number

speak_day:
	writei2c 0,(0,0,5,1)		' set the volume pitch and speed
	writei2c 0,(0,"The dayte is ")
	startpos = day - 1  * 6 + 136
	endpos = startpos + 5
	gosub loadbuffer 
	writei2c 0,(0,"day")
	gosub say_it

speak_date:
	let number = date
	gosub speak_number

speak_month:
	writei2c 0,(0,0,5,1)			' set the volume pitch and speed
	if month > 2 then speak_month2

speak_month1:
	startpos = month - 1 * 8 + 178
	endpos = startpos + 7
	gosub loadbuffer 
	goto speak_year

speak_month2:
	startpos = month - 3 * 6 + 194		
	endpos = startpos + 5
	gosub loadbuffer 
	if month < 9 then speak_year
	writei2c 0,(0,"ber")
	gosub say_it

speak_year:
	let number = year + 2000
	gosub speak_number


'wait then loop
	pause 1000
	goto main


; *** Sub to speak a number (in word variable 'number') ***

speak_number:
	writei2c 0,(0,0,5,1)		' set the volume pitch and speed

speak_loop:
	if number > 999 then speak_1000
	if number > 99 then speak_100
	if number > 19 then speak_20
	if number > 15 then speak_16
	if number > 12 then speak_13
	if number > 10 then speak_11

speak_1:
	startpos = number - 1 * 5
	endpos = startpos + 4
	goto load_and_say_it
speak_11:
	startpos = number - 11 * 6 + 50
	endpos = startpos + 5
	goto load_and_say_it
speak_13:
	startpos = number - 11 * 6 + 50
	endpos = startpos + 5
	goto speak_teen
speak_16:
	startpos = number - 11 * 5
	endpos = startpos + 4
speak_teen:
	gosub loadbuffer
	writei2c 0,(0,"teen")
	goto say_it
speak_20:
	startpos = number / 10 - 2 * 7 + 80 
	endpos = startpos + 6
	gosub loadbuffer 
        writei2c 0,(0," ")
	number = number // 10
	goto speak_1

speak_100:
	startpos = number / 100 - 1 * 5
	endpos = startpos + 4
	gosub loadbuffer
	writei2c 0,(0," hundred ")

	number = number // 100
	if number = 0 then say_it
        writei2c 0,(0,"and ")
	goto speak_loop

speak_1000:
	startpos = number / 1000 - 1 * 5
	endpos = startpos + 4
	gosub loadbuffer
	writei2c 0,(0," thousand ")

	number = number // 1000
	if number = 0 then say_it
	goto speak_loop







; *** Subs to load buffer and speak the text ***


' *** load buffer and then say text ****
load_and_say_it:
	gosub loadbuffer
say_it:
	writei2c 0,(0,0)	' send last null
	writei2c 0,(64)		' now say it

' *** now wait until SP03 has stopped talking ***
wait4shutup:
	readi2c 0,(counter)	' poll buffer
	if counter > 0 then wait4shutup	'loop
	return

' *** sub to load text from data memory ***
loadbuffer:
	for counter = startpos to endpos
	  read counter,nextbyte
	  writei2c 0,(0,nextbyte)
	next counter
	return
