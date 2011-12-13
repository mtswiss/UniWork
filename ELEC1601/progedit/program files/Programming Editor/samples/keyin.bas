' Example to show how to convert computer 
' keyboard codes into ASCII values
' For PICAXE-18A or PICAXE-28X only.

' The ASCII values are preloaded into the data
' memory by use of the EEPROM command, When a
' key hit is detected, it's value is used as 
' the data memory address with the read command.
' This enables the correct ASCII value to be
' read back from the data memory into variable b1.


main:
'get the keyboard hit
	keyin

' convert key value from keyin command
' into an ASCII character in b1
	read keyvalue,b1

'display ASCII value on screen
	debug b1

	goto main



' load memory with lookup table
' of keyboard to ASCII conversion

EEPROM $00,("?9?5312C?A864?'?")	' Function keys
EEPROM $10,("?????Q1???ZSAW2?")	' Main keyboard keys
EEPROM $20,("?CXDE43?? VFTR5?")
EEPROM $30,("?NBHGY6???MJU78?")
EEPROM $40,("?,KIO09??./L;P-?")
EEPROM $50,("??'?[=?????]????")
EEPROM $60,("?????????1?47???")	' Numeric keypad keys
EEPROM $70,("0.2568??B+3-*9??")	' 


