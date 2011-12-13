'PICAXE program that allows data saved
'on the AXE110 Datalogger module to be
'uploading to computer in CSV format.

'Make sure the cable is in the 'Run' socket
'then download this program.

'Move the cable to the 'Datalink' socket
'and then use the PICAXE menu > Datalink tool
'to upload the data
'(Options - 'Baud'-2400, 'Sensors'-2, 'Send G'-enabled)

'Define variables
symbol counter = b0
symbol address = b1
symbol data = b2

'Define useful ASCII characters
symbol	COM	=	44	'comma
symbol	LF	=	10	'line feed

:	serin 6,N2400,("G")	'Wait for G go signal from signal

	'upload titles
	serout 7,N2400,("Address",COM,"Sensor1",COM,"Sensor2",CR,LF)

main:	for counter = 0 to 127		'Start a for..next loop.

	   let address = counter
	   read address,data		
	   serout 7,N2400,(#address,COM,#data)
  	
	   let address = counter + 128
	   read address,data	
	   serout 7,N2400,(COM,#data,CR,LF)
	next counter			'Next loop.
  		
	serout 7,N2400,(0)		'Send null to end.
	
	end				'end 



