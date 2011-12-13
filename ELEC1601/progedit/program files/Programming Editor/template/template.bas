'template.bas - UNIVERSAL TEMPLATE

'Higher Tech Studies Universal Template

'Template for a program listing that uses the
'serial ADC and/or datalogging modules.

'This template contains ALL the sub-procedures.
'In some case you may not need some of these sub-
'procedures, and so to reduce the program size the
'unnecessary sub-procedures could be deleted.

'**********************************
'symbol definitions - do not change
'**********************************

symbol	ADC_CS	=	0	'ADC chip select pin (output)
symbol	ADC_CLK	=	1	'ADC clock pin (output)
symbol	ADC_D_I	=	pin2	'ADC data pin (input)
symbol 	ADC_MPX	= 	3	'ADC multiplexer select pin (output)
symbol 	ADC_SW  = 	pin3	'ADC push switch (input)

symbol 	EE_CS	= 	4	'EEPROM chip select pin (output)
symbol 	EE_D_I	= 	pin5	'EEPROM data pin (when input)
symbol 	EE_D_O 	= 	5	'EEPROM data pin (when output)
symbol 	EE_CLK 	= 	6	'EEPROM clock pin (output)

symbol	S_OUT	= 	7	'serial output (output)

symbol	data	=	b4	'data byte
symbol	i	=	b5	'scratchpad counter
symbol 	ShifReg = 	w3	'scratchpad shift register

symbol  address = 	b8	'EEPROM address 
symbol	page	= 	b9	'EEPROM page
symbol 	clocks 	= 	b11	'scratchpad clock counter

'****************************
'init routine - do not change
'****************************

init:	let dirs = %11111011	' pin 2 input, rest outputs. 
	let pins = %10000001	' ADC_CS and S_OUT high

	pause 5				'Short pause
	serout S_OUT,T2400,(254,1) 	'Clear lcd
	pause 30			'Short pause.

'**************************************
'main program - this is where you type!
'**************************************

main:	








'******************************************************
'Standard ADC and EEPROM sub-procedures - do not change
'******************************************************

	end				'just in case!	

' This sub-procedure gets a reading from the serial ADC unit.
' Data is returned in byte variable 'data'

adcread:
	pause 30			'Short delay
	low ADC_CLK			'Put clock line in starting state. 
	low ADC_CS			'Select ADC. 
	pulsout ADC_CLK, 1		'10 us clock pulse. 
	let data = 0			'Clear data. 
	for i = 1 to 8			'Eight data bits. 
	   let data = data * 2		'Perform shift left. 
	   pulsout ADC_CLK, 1		'10 us clock pulse. 
	   let data = data + ADC_D_I	'Put bit in LSB of data. 
	next i				'Do it again. 
	high ADC_CS			'Deselect ADC when done. 
	return	

' This sub-procedure writes a byte to the EEPROM.
' 'Data' is written to 'address' on 'page' 

eewrite:
	gosub eenabl			'Enable.
	let ShifReg = $A00 		'Get the write opcode.  
	let ShifReg = ShifReg | w4	'OR in the address bits.
	let clocks = 12			'Send 12 bits to EEPROM. 
	high EE_CS			'Select EEPROM.
	gosub eeout			'Send the opcode/address. 
	let ShifReg = data * 16 	'Move bit 7 to bit 11. 
	let clocks = 8			'Eight data bits. 
	gosub eeout			'Send the data.
	low EE_CS			'Deselect EEPROM.
	gosub edisbl			'Write Protect.
	return

' This sub-procedure reads a byte from the EEPROM.
' 'Data' is read from 'address' on 'page' 

eeread:	
	let ShifReg = $C00		'Get the read opcode.
	let ShifReg = ShifReg | w4	'OR in the address bits.
	let clocks = 12			'Send 12 bits to EEPROM. 
	high EE_CS			'Chip select on. 
	gosub eeout			'Send the opcode/address. 
	gosub eein			'Receive the byte.
	low EE_CS			'Deselect the EEPROM. 
	return

' Internal EEPROM sub-procedures. Required by eeread and eewrite

eenabl:	let ShifReg = $980		'Get the write-enable opcode.
	high EE_CS			'Chip select on. 
	let clocks = 12			'Send 12 bits to EEPROM. 
	gosub eeout			'Send the opcode. 
	low EE_CS			'Deselect the EEPROM. 
	return

edisbl:	let ShifReg = $800		'Get the write-disable opcode. 
	high EE_CS			'Chip select on. 
	let clocks = 12			'Send 12 bits to EEPROM. 
	gosub eeout			'Send the opcode.
	low EE_CS			'Deselect the EEPROM.
	return

eein:	input EE_D_O			'Change the data line to input.
	let data = 0			'Clear data byte.
	for i = 1 to 8			'Prepare to get 8 bits. 
           let data = data * 2		'Shift EEdata to the left. 
           high EE_CLK			'Data valid on rising edge.
           let data = data + EE_D_I 	'Move data to lsb of variable. 
           low EE_CLK			'End of clock pulse. 
	next i				'Get another bit.
	output EE_D_O			'Restore data line to output. 
	return

eeout:	for i = 1 to clocks		'Number of bits to shift out. 
           let EE_D_I = ShifReg / $800 	'Get bit 12 of ShifReg.
	   pulsout EE_CLK,10		'Output a brief clock pulse. 
	   let ShifReg = ShifReg * 2 	'Shift register to the left. 
	next i 				'Send another bit. 
	return

