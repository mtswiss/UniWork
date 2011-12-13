'PROGRAM: DATALINK.BAS

'PBASIC program that allows data saved
'on the Datalogger module to be
'uploading to computer in CSV format.

'Connect the Datalogger module to the Stamp
'and then download this program to the Stamp.

'Then move the serial cable to the Datalogger 
'connector and run the Datalink utility.

symbol 	EE_CS	= 	4	'EEPROM chip select pin (output)
symbol 	EE_D_I	= 	pin5	'EEPROM data pin (when input)
symbol 	EE_D_O 	= 	5	'EEPROM data pin (when output)
symbol 	EE_CLK 	= 	6	'EEPROM clock pin (output)

symbol	S_OUT	= 	7	'serial output (output)
symbol	S_IN	= 	6	'serial input (input)

symbol	data	=	b4	'data byte
symbol	i	=	b5	'scratchpad counter
symbol 	ShifReg = 	w3	'scratchpad shift register

symbol  address = 	b8	'EEPROM address 
symbol	page	= 	b9	'EEPROM page
symbol 	clocks 	= 	b11	'scratchpad clock counter

'Define useful ASCII characters
symbol	COM	=	44	'comma
symbol	LF	=	10	'line feed

init:	let dirs = %10111011	'Pin 2,6 input, rest outputs. 
	let pins = %10000000
	pause 5

	serin S_IN,T2400,("G")	'Wait for GO signal

	output EE_CLK		'Make pin6 an output

	'print titles
	serout S_OUT,T2400,("Address",COM,"Sensor1",COM,"Sensor2",CR,LF)

main:	for address = 0 to 255		'Start a for..next loop.
	   let page = 0			'Move to page 0.
	   gosub eeread			'Read data from EEPROM.
	   serout S_OUT,T2400,(#address,COM,#data)
  	
	   let page = 1			'Move to page 1.
	   gosub eeread			'Read data from EEPROM.
	   serout S_OUT,T2400,(COM,#data,CR,LF)
	next address			'Next loop.
  		
	serout S_OUT,T2400,(0)		'Send null to end.
	
	end				'end 


'This sub-procedure reads a byte from the EEPROM.
'data' is read from 'address' on 'page' 

eeread:	
	let ShifReg = $C00		'Get the read opcode.
	let ShifReg = ShifReg | w4	'OR in the address bits.
	let clocks = 12			'Send 12 bits to EEPROM. 
	high EE_CS			'Chip select on. 
	gosub eeout			'Send the opcode/address. 
	gosub eein			'Receive the byte.
	low EE_CS			'Deselect the EEPROM. 
	return

' EEPROM sub-procedures

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
           let EE_D_I = ShifReg / $800 	'Get bit 12 of W1.
	   pulsout EE_CLK,10		'Output a brief clock pulse. 
	   let ShifReg = ShifReg * 2 	'Shift register to the left. 
	next i 				'Send another bit. 
	return

